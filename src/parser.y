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

%code top {
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
}

%code requires {
#include "handlers.h"
#include "symbol_table.h"
#include "syntax_tree.h"
}

%{
extern char * yytext;
extern int yylval;
extern int yylineno;
extern int yylex();
extern FILE *  yyin;
%}

%code provides {
int yyerror(const char * const msg);
}

%code {
SymbolTable * symbol_table;
}

/* yyunion */
%union{
    struct Node * node;
    Type type;
    char * string;
    int integer;
}

/* TOKENS */

/* Various brackets and other simple tokens */
%token LBRACE RBRACE LPAREN RPAREN LSQB RSQB COMMA SEMICOLON DOT BACKSLASH BACKTICK ARROW
/* Arithmetic and bitwise operators */
%token PLUS_OP MULT_OP BIT_AND_OP BIT_OR_OP BIT_NOT_OP BIT_XOR_OP
%token RPLUS_OP RMULT_OP RBIT_AND_OP RBIT_OR_OP RBIT_XOR_OP
/* Logical operators */
%token AND NOT OR XOR
/* Assignment and comparison operators */
%token EQUALS_OP ASSIGN_OP COMPARE_OP
/* Keywords */
%token FUN IF ELIF ELSE FOR WHILE IMPORT CASE SWITCH TYPE RETURN BREAK CONTINUE
/* Types */
%token INT_TYPE STR_TYPE FLOAT_TYPE
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

%type<node> variable_declaration expr
%type<type> type
%type<string> ID STR_LIT
%type<integer> INT_LIT

%%


program:
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

/* TODO add more statement types */
statement:
    expr_statement
    | if_statement
    | function_def
    | control_statement
    | variable_declaration
    | while_loop
    | typedef
    ;

statement_block:
    LBRACE statement_list RBRACE
    ;


expr_statement:
    expr SEMICOLON
    ;

expr:
    assign_expr
    ;

assign_expr:
    logical_expr
    | ID ASSIGN_OP assign_expr
    | ID EQUALS_OP assign_expr
    ;

logical_expr:
    compare_expr
    | NOT logical_expr
    | logical_expr AND logical_expr
    | logical_expr OR logical_expr
    | logical_expr XOR logical_expr
    ;

compare_expr:
    bitwise_expr %prec BIT_AND_OP
    | compare_expr COMPARE_OP compare_expr
    ;

bitwise_expr:
    arithmetic_expr
    | bitwise_expr BIT_AND_OP bitwise_expr
    | bitwise_expr RBIT_AND_OP bitwise_expr
    | bitwise_expr BIT_OR_OP bitwise_expr
    | bitwise_expr RBIT_OR_OP bitwise_expr
    | bitwise_expr BIT_XOR_OP bitwise_expr
    | bitwise_expr RBIT_XOR_OP bitwise_expr
    | BIT_NOT_OP bitwise_expr
    | BIT_AND_OP bitwise_expr %prec RBIT_AND_OP
    | BIT_OR_OP bitwise_expr %prec RBIT_OR_OP
    | BIT_XOR_OP bitwise_expr %prec RBIT_XOR_OP
    | RBIT_AND_OP bitwise_expr
    | RBIT_OR_OP bitwise_expr
    | RBIT_XOR_OP bitwise_expr
    ;

arithmetic_expr:
    member_expr
    | arithmetic_expr POW_OP arithmetic_expr
    | arithmetic_expr MULT_OP arithmetic_expr
    | arithmetic_expr RMULT_OP arithmetic_expr
    | arithmetic_expr PLUS_OP arithmetic_expr
    | arithmetic_expr RPLUS_OP arithmetic_expr
    | PLUS_OP arithmetic_expr %prec RPLUS_OP
    | MULT_OP arithmetic_expr %prec RMULT_OP
    | RPLUS_OP arithmetic_expr
    | RMULT_OP arithmetic_expr
    ;

member_expr:
    primary_expr
    | member_expr DOT member_expr
    | member_expr LSQB expr RSQB
    ;

primary_expr:
    ID
    | literal
    | LPAREN expr RPAREN
    | function_call
    ;

function_call:
    member_expr LPAREN argument_list RPAREN
    ;

argument_list:
    expr
    | argument_list COMMA expr
    ;

function_def:
    FUN ID LPAREN argument_list_specifier RPAREN ARROW type LBRACE statement_list RBRACE
    | FUN BACKTICK user_operator BACKTICK LPAREN argument_list_specifier RPAREN ARROW type LBRACE statement_list RBRACE
    /* Function definition with generic parameters, have to define more grammar rules first */
    /* | FUN ID LSQB generic_parameters RSQB LPAREN argument_list_specifier_with_generic RPAREN ARROW type_specifier_with_generics LBRACE statement_list RBRACE */
    ;

argument_list_specifier:
    variable_specifier
    | argument_list_specifier COMMA variable_specifier
    ;

variable_specifier:
    type ID
    | type ID LSQB INT_LIT RSQB
    ;

/* TODO: add pointer (or some sort of reference type) supprt, perhaps with `ptr` keyword, and add tuples. */
type:
    ID { $$ = (Type)$1; }
    | function_type
    ;

typedef:
    TYPE type EQUALS_OP type SEMICOLON
    ;

function_type:
    FUN LPAREN type_list RPAREN ARROW type
    ;

type_list:
    type
    | type_list COMMA type
    ;

variable_declaration:
    type ID SEMICOLON { $$ = handle_variable_declaration($type, $ID, NULL, yylineno); }
    | type ID EQUALS_OP expr SEMICOLON { $$ = handle_variable_declaration($type, $ID, $expr, yylineno); }
    /* | type ID LSQB INT_LIT RSQB SEMICOLON */
    ;

/* TODO Add more literal types */
literal:
    INT_LIT
    | STR_LIT
    ;

user_operator:
    PLUS_OP | MULT_OP | BIT_AND_OP | BIT_OR_OP | BIT_NOT_OP | BIT_XOR_OP
    | RPLUS_OP | RMULT_OP | RBIT_AND_OP | RBIT_OR_OP | RBIT_XOR_OP
    | ASSIGN_OP | COMPARE_OP | EQUALS_OP
    ;

if_elif:
    IF LPAREN expr RPAREN statement_block %prec THEN
    | if_elif ELIF LPAREN expr RPAREN statement_block
    ;

if_statement:
    if_elif
    | if_elif ELSE statement_block
    ;

control_statement:
    RETURN expr SEMICOLON
    | BREAK expr SEMICOLON
    | CONTINUE expr SEMICOLON
    ;

while_loop:
    WHILE LPAREN expr RPAREN statement_block
    | WHILE LPAREN expr RPAREN SEMICOLON
    ;

%%

int yyerror(const char * const msg) {
    fprintf(stderr, "yyerror: %s\n", msg);
    return EXIT_FAILURE;
}

/* based on musl libc printf implementation */
/* int yyerror(const char * restrict fmt, ...) { */
/* 	va_list ap; */
/* 	va_start(ap, fmt); */
/* 	vfprintf(stderr, fmt, ap); */
/* 	va_end(ap); */
/* 	return EXIT_FAILURE; */
/* } */