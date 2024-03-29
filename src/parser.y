 /*
  * Authors:
  *   Andrew Clark     - andrew.clark.6@bc.edu
  *   Alex Liu         - alex.liu@bc.edu
  *   Caden Parajuli   - caden.parajuli@bc.edu
  *   Micheal Lebreck  - michael.lebreck@bc.edu
  *   William Morrison - william.morrison.2@bc.edu
  */

%language "C"
%define parse.error detailed
%define api.pure full
%parse-param {Node ** ast}

%code top {
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "handlers.h"
#include "symbol_table.h"
#include "syntax_tree.h"
#include "types.h"
#include "parser.h"
}

%code requires {
#include "handlers.h"
#include "symbol_table.h"
#include "syntax_tree.h"
#include "types.h"
}

%code provides {
int yyerror(Node ** const ast, const char * restrict fmt, ...);
}

%code {
extern char * yytext;
extern int yylval;
extern int yylineno;
extern int yylex(YYSTYPE *lvalp);
extern FILE *  yyin;

SymbolTable * symbol_table;
SymbolTable * global_table;
}


/* yyunion */
%union{
    struct Node * node;
    Type * type;
    Args * args;
    CallArgs * call_args;
    StatementBlock * block;
    SymbolTable * table;
    char * string;
    /* int integer; */
}

/* TOKENS */

/* Various brackets and other simple tokens */
%token LBRACE RBRACE LPAREN RPAREN LSQB RSQB COMMA SEMICOLON DOT BACKSLASH BACKTICK ARROW
/* Arithmetic and bitwise operators */
%token PLUS_OP MULT_OP POW_OP BIT_AND_OP BIT_OR_OP BIT_NOT_OP BIT_XOR_OP
%token RPLUS_OP RMULT_OP RBIT_AND_OP RBIT_OR_OP RBIT_XOR_OP
/* Logical operators */
%token AND NOT OR XOR
/* Assignment and comparison operators */
%token EQUALS_OP ASSIGN_OP COMPARE_OP
/* Keywords */
%token CFUN FUN IF ELIF ELSE FOR WHILE CASE SWITCH TYPE RETURN BREAK CONTINUE IMPORT AS
/* Types */
%token INT_TYPE STR_TYPE FLOAT_TYPE PTR_TYPE VOID_TYPE
/* Literals */
%token INT_LIT STR_LIT ID


/* PRECEDENCE */

/* if-elif-else parsing, lowest precedence. Note that THEN is not an actual token */
%right THEN ELIF ELSE
/* Assignment operators */
%right EQUALS_OP ASSIGN_OP
/* Comparison operators */
%right COMPARE_OP
/* Logical operators */
%left OR XOR
%left AND
%right NOT
/* Arithmetic operators (except POW) */
%left PLUS_OP
%right RPLUS_OP
%left MULT_OP
%right RMULT_OP
%right ARITH_UNARY
%right POW_OP
/* Binary operators */
%right BIT_NOT_OP
%left BIT_AND_OP
%left BIT_OR_OP BIT_XOR_OP
%right RBIT_AND_OP
%right RBIT_OR_OP RBIT_XOR_OP
%right BIT_UNARY
/* General Unary operator precedence */
%right UNARY
/* Bracket-like precedence is highest */
%left LPAREN LSQB LBRACE
/* Arrow */
%left ARROW
/* Dot */
%left DOT

%type<node> expr assign_expr logical_expr compare_expr bitwise_expr arithmetic_expr member_expr primary_expr function_call literal if_elif
%type<node> program expr_statement if_statement function_def cfun_dec control_statement variable_declaration while_loop for_loop do typedef import_statement statement statement_block
%type<block> statement_list
%type<type> type fun_type
%type<args> argument_list_specifier type_list variable_specifier
%type<call_args> argument_list
%type<string> ID STR_LIT INT_LIT PLUS_OP MULT_OP BIT_AND_OP BIT_OR_OP BIT_NOT_OP BIT_XOR_OP RPLUS_OP RMULT_OP RBIT_AND_OP RBIT_OR_OP RBIT_XOR_OP AND NOT OR XOR EQUALS_OP ASSIGN_OP COMPARE_OP POW_OP user_operator
/* %type<integer> INT_LIT */


%%


program:
    { global_table = (symbol_table = new_global_symbol_table(HASH_TABLE_DEFAULT_SIZE)); }
    statement_list { $$ = create_block_node($statement_list); *ast = $$; }
    ;

statement_list:
    statement { $$ = create_block($1); }
    | statement_list statement { $$ = add_to_block($1, $2); }
    ;

/* TODO add more statement types */
statement:
    expr_statement { $$ = $1; }
    | if_statement { $$ = $1; }
    | function_def { $$ = $1; }
    | cfun_dec { $$ = $1; }
    | control_statement { $$ = $1; }
    | variable_declaration { $$ = $1; }
    | while_loop { $$ = $1; }
    | for_loop { $$ = $1; }
    | do { $$ = $1; }
    | typedef { $$ = $1; }
    | import_statement { $$ = $1; }
    ;

statement_block:
    LBRACE statement_list RBRACE { $$ = create_block_node($2); }
    ;


expr_statement:
    expr SEMICOLON { $$ = $1; }
    ;

expr:
    assign_expr { $$ = $1; }
    ;

assign_expr:
    logical_expr { $$ = $1; }
    | member_expr ASSIGN_OP assign_expr { $$ = handle_binary_expr($1, $2, $3); }
    | member_expr EQUALS_OP assign_expr { $$ = handle_binary_expr($1, $2, $3); }
    ;

logical_expr:
    compare_expr { $$ = $1; }
    | NOT logical_expr { $$ = handle_unary_expr($1, $2); }
    | logical_expr AND logical_expr { $$ = handle_binary_expr($1, $2, $3); }
    | logical_expr OR logical_expr { $$ = handle_binary_expr($1, $2, $3); }
    | logical_expr XOR logical_expr { $$ = handle_binary_expr($1, $2, $3); }
    ;

compare_expr:
    bitwise_expr %prec BIT_AND_OP { $$ = $1; }
    | compare_expr COMPARE_OP compare_expr { $$ = handle_binary_expr($1, $2, $3); }
    ;

bitwise_expr:
    arithmetic_expr { $$ = $1; }
    | bitwise_expr BIT_AND_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | bitwise_expr RBIT_AND_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | bitwise_expr BIT_OR_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | bitwise_expr RBIT_OR_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | bitwise_expr BIT_XOR_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | bitwise_expr RBIT_XOR_OP bitwise_expr { $$ = handle_binary_expr($1, $2, $3); }
    | BIT_NOT_OP bitwise_expr { $$ = handle_unary_expr($1, $2); }
    | BIT_AND_OP bitwise_expr %prec RBIT_AND_OP { $$ = handle_unary_expr($1, $2); }
    | BIT_OR_OP bitwise_expr %prec RBIT_OR_OP { $$ = handle_unary_expr($1, $2); }
    | BIT_XOR_OP bitwise_expr %prec RBIT_XOR_OP { $$ = handle_unary_expr($1, $2); }
    | RBIT_AND_OP bitwise_expr { $$ = handle_unary_expr($1, $2); }
    | RBIT_OR_OP bitwise_expr { $$ = handle_unary_expr($1, $2); }
    | RBIT_XOR_OP bitwise_expr { $$ = handle_unary_expr($1, $2); }
    ;

arithmetic_expr:
    member_expr { $$ = $1; }
    | arithmetic_expr POW_OP arithmetic_expr { $$ = handle_binary_expr($1, $2, $3); }
    | arithmetic_expr MULT_OP arithmetic_expr { $$ = handle_binary_expr($1, $2, $3); }
    | arithmetic_expr RMULT_OP arithmetic_expr { $$ = handle_binary_expr($1, $2, $3); }
    | arithmetic_expr PLUS_OP arithmetic_expr { $$ = handle_binary_expr($1, $2, $3); }
    | arithmetic_expr RPLUS_OP arithmetic_expr { $$ = handle_binary_expr($1, $2, $3); }
    | PLUS_OP arithmetic_expr %prec RPLUS_OP { $$ = handle_unary_expr($1, $2); }
    | MULT_OP arithmetic_expr %prec RMULT_OP { $$ = handle_unary_expr($1, $2); }
    | RPLUS_OP arithmetic_expr { $$ = handle_unary_expr($1, $2); }
    | RMULT_OP arithmetic_expr { $$ = handle_unary_expr($1, $2); }
    ;

/* This one should actually have some checking in it to make sure you
 * don't write something dumb like 4[1] or 15."foo" */
member_expr:
    primary_expr { $$ = $1; }
    | member_expr DOT member_expr { $$ = handle_member_expr($1, $3, 1); }
    | member_expr LSQB expr RSQB { $$ = handle_member_expr($1, $3, 0); }
    ;

primary_expr:
    ID { $$ = handle_var($1); }
    | literal { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    | function_call { $$ = $1; }
    ;

function_call:
    ID LPAREN argument_list RPAREN { $$ = handle_function_call($1, $3, yylineno); }
    /* member_expr LPAREN argument_list RPAREN { handle_function_call($1, $3, yylineno); } */
    ;

argument_list:
    expr { $$ = create_call_args($1); }
    | argument_list COMMA expr { $$ = add_to_call_args($1, $3); }
    ;

function_def:
    FUN ID LPAREN argument_list_specifier RPAREN ARROW type <table>{
        $$ = push_symbol_table();
        handle_fun_def_args($ID, $$, $argument_list_specifier, yylineno);
    }
    statement_block {
        $$ = handle_function_def($ID, $argument_list_specifier, $type, $8, $statement_block, yylineno);
        pop_symbol_table();
    }
    
    | FUN BACKTICK user_operator BACKTICK LPAREN argument_list_specifier RPAREN ARROW type <table>{
        $$ = push_symbol_table();
    }
    statement_block {
        $$ = handle_function_def($user_operator, $argument_list_specifier, $type, $10, $statement_block, yylineno);
        pop_symbol_table();
    }
    ;

cfun_dec:
    CFUN ID LPAREN argument_list_specifier RPAREN ARROW type SEMICOLON { $$ = handle_cfun_dec($ID, $argument_list_specifier, $type, yylineno); }
    ;

argument_list_specifier:
    variable_specifier { $$ = $1; }
    | argument_list_specifier COMMA variable_specifier { $$ = add_to_arg_list($1, $3); }
    ;

/** \todo edit type info for array argument */
variable_specifier:
    type ID { $$ = create_arg($type, $ID); }
    | type ID LSQB INT_LIT RSQB { yyerror(NULL, "Array arguments not supported yet\n"); }
    ;

type:
    ID { $$ = handle_custom_type($ID); }
    | INT_TYPE { $$ = handle_base_type(int_type); }
    | FLOAT_TYPE { $$ = handle_base_type(float_type); }
    | STR_TYPE { $$ = handle_base_type(str_type); }
    | VOID_TYPE { $$ = handle_base_type(void_type); }
    | fun_type { $$ = $1; }
    | PTR_TYPE type { $$ = handle_ptr_type($2); }
    ;

typedef:
    TYPE ID EQUALS_OP type SEMICOLON { $$ = handle_type_def($2, $4, yylineno); }
    ;

fun_type:
    FUN LPAREN type_list RPAREN ARROW type { $$ = handle_fun_type($type_list, $type); }
    ;

type_list:
    type { $$ = create_type_list($1); }
    | type_list COMMA type { $$ = add_to_type_list($1, $3); }
    ;

variable_declaration:
    type ID SEMICOLON { $$ = handle_var_declaration($type, $ID, NULL, yylineno); }
    | type ID EQUALS_OP expr SEMICOLON { $$ = handle_var_declaration($type, $ID, $expr, yylineno); }
    | type ID LSQB INT_LIT RSQB SEMICOLON { $$ = handle_array_declaration($type, $ID, $INT_LIT, NULL, yylineno); }
    | type ID LSQB INT_LIT RSQB EQUALS_OP expr SEMICOLON { $$ = handle_array_declaration($type, $ID, $INT_LIT, $expr, yylineno); }
    ;

/* TODO Add more literal types */
literal:
    INT_LIT { $$ = handle_literal($1, int_type); }
    | STR_LIT { $$ = handle_literal($1, str_type); }
    ;

user_operator:
    PLUS_OP | MULT_OP | BIT_AND_OP | BIT_OR_OP | BIT_NOT_OP | BIT_XOR_OP
    | RPLUS_OP | RMULT_OP | RBIT_AND_OP | RBIT_OR_OP | RBIT_XOR_OP
    | ASSIGN_OP | COMPARE_OP | EQUALS_OP
    ;

if_elif:
    IF LPAREN expr RPAREN statement_block %prec THEN { $$ = handle_if($expr, $statement_block, NULL); }
    | if_elif ELIF LPAREN expr RPAREN statement_block { $$ = handle_elif($1, $expr, $statement_block, NULL); }
    ;

if_statement:
    if_elif { $$ = $1; }
    | if_elif ELSE statement_block { $$ = handle_elif($1, NULL, $statement_block, NULL); }
    ;

control_statement:
    RETURN expr SEMICOLON { $$ = handle_return($expr); }
    | BREAK SEMICOLON { $$ = handle_break(); }
    | CONTINUE SEMICOLON { $$ = handle_break(); }
    ;

for_loop:
    FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN statement_block { $$ = handle_for($3, $5, $7, $9); }
    | FOR LPAREN variable_declaration expr SEMICOLON expr RPAREN statement_block { $$ = handle_for($3, $4, $6, $8); }
    ;

do:
    statement_block WHILE LPAREN expr RPAREN SEMICOLON { $$ = handle_do($expr, $statement_block); }
    ;

while_loop:
    WHILE LPAREN expr RPAREN statement_block { $$ = handle_while($expr, $statement_block); }
    | WHILE LPAREN expr RPAREN SEMICOLON { $$ = handle_while($expr, NULL); }
    ;

import_statement:
    IMPORT ID SEMICOLON { $$ = handle_import($2, $2, yylineno); }
    | IMPORT ID AS ID SEMICOLON { $$ = handle_import($2, $4, yylineno); }
    ;

%%


/* based on musl libc printf implementation */
int yyerror(Node ** const ast, const char * restrict fmt, ...) {
    (void)(ast);
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    return EXIT_FAILURE;
}
