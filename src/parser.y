
%language "C"
%define parse.error detailed

%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

extern char * yytext;
extern int yylval;
extern int line_num;
extern int yylex();
extern FILE *  yyin;
%}

%code provides {
void yyerror(const char * s);
}

/* TODO: Change bitwise operator names to someting sensible like BIT_NOT etc. Also have to change lexer */

/* TOKENS */

/* Various brackets and other simple tokens */
%token LBRACE RBRACE LPAREN RPAREN LSQB RSQB COMMA SEMICOLON DOT BACKSLASH BACKTICK ARROW
/* Arithmetic and bitwise operators */
%token PLUS_OP MULT_OP AND_OP OR_OP NOT_OP XOR_OP RPLUS_OP RMULT_OP RAND_OP ROR_OP RXOR_OP
/* Logical operators */
%token AND NOT OR XOR
/* Assignment and comparison operators */
%token ASSIGN_OP COMPARE_OP
/* Keywords */
%token FUN IF ELIF ELSE FOR WHILE IMPORT CASE SWITCH TYPE RETURN
/* Literals */
%token INT_LIT STR_LIT ID


/* PRECEDENCE */

/* if-elif-else parsing, lowest precedence */
%right THEN ELIF ELSE
/* dots */
%left DOT
/* Assignment operators */
%right ASSIGN_OP
/* Logical operators */
%right NOT
%left AND
%left OR XOR
/* Comparison operators */
%right COMPARE_OP
/* Binary operators */
%right NOT_OP
%left AND_OP
%left OR_OP XOR_OP
%right RAND_OP
%right ROR_OP RXOR_OP
/* Arithmetic operators */
%left PLUS_OP
%right RPLUS_OP
%left MULT_OP
%right RMULT_OP

%left UNARY

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
    ;

expr_statement:
    expr SEMICOLON       {printf("statement!\n");}
    ;

/* Precedence/conflicts within sub-expressions should (if I did it right) be handled by the token precedences above */
expr:
    assign_expr
    | expr assign_expr
    ;

assign_expr:
    logical_expr
    | ID ASSIGN_OP assign_expr
    ;

/* Note that the logical not precedence is still very low */
logical_expr:
    compare_expr
    | NOT logical_expr
    | logical_expr AND logical_expr
    | logical_expr OR logical_expr
    | logical_expr XOR logical_expr
    ;

compare_expr:
    bitwise_expr
    | bitwise_expr COMPARE_OP bitwise_expr
    ;

bitwise_expr:
    arithmetic_expr
    | bitwise_expr AND_OP bitwise_expr
    | bitwise_expr RAND_OP bitwise_expr
    | bitwise_expr OR_OP bitwise_expr
    | bitwise_expr ROR_OP bitwise_expr
    | bitwise_expr XOR_OP bitwise_expr
    | bitwise_expr RXOR_OP bitwise_expr
    ;

arithmetic_expr:
    unary_expr
    | arithmetic_expr MULT_OP arithmetic_expr
    | arithmetic_expr RMULT_OP arithmetic_expr
    | arithmetic_expr PLUS_OP arithmetic_expr
    | arithmetic_expr RPLUS_OP arithmetic_expr
    ;

/* NOTE I think these all need to be terminals for precedence to work, but feel free to simplify it if not */
unary_expr:
    member_expr
    | PLUS_OP logical_expr %prec UNARY
    | MULT_OP logical_expr %prec UNARY
    | AND_OP logical_expr %prec UNARY
    | OR_OP logical_expr %prec UNARY
    | NOT_OP logical_expr %prec UNARY
    | XOR_OP logical_expr %prec UNARY
    | RPLUS_OP logical_expr %prec UNARY
    | RMULT_OP logical_expr %prec UNARY
    | RAND_OP logical_expr %prec UNARY
    | ROR_OP logical_expr %prec UNARY
    | RXOR_OP logical_expr %prec UNARY
    ;

member_expr:
    primary_expr
    | member_expr DOT primary_expr
    | member_expr LSQB expr RSQB
    ;

primary_expr:
    ID
    | constant
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
    /* Function definition with generic parameters, have to define more grammar rules first */
    /* | FUN ID LSQB generic_parameters RSQB LPAREN argument_list_specifier_with_generic RPAREN ARROW type_specifier_with_generics LBRACE statement_list RBRACE */
    ;

argument_list_specifier:
    argument_specifier
    | argument_list_specifier COMMA argument_specifier
    ;

argument_specifier:
    type ID
    ;

/* TODO: add pointer supprt, perhaps with `ptr` keyword */
type:
    ID
    | ID LSQB INT_LIT RSQB
    ;

/* TODO Add more constant types */
constant:
    INT_LIT
    | STR_LIT
    ;

if_elif:
    IF LPAREN expr RPAREN LBRACE statement_list RBRACE %prec THEN
    | if_elif ELIF LPAREN expr RPAREN LBRACE statement_list RBRACE
    ;

if_statement:
    if_elif
    | if_elif ELSE LBRACE statement_list RBRACE
    ;

control_statement:
    RETURN expr SEMICOLON
    ;


%%

void yyerror(const char * s) {
  fprintf (stderr, "yyerror: %s\n", s);
}