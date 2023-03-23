
%language "C"

%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

extern char * yytext;
extern int yylval;
extern int yylex();
extern int line_num;
%}
%code provides {
int yyerror(const char * s);
}

/* Token definitions */
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON
%token PLUS_OP MULT_OP AND_OP OR_OP NOT_OP XOR_OP RPLUS_OP RMULT_OP RAND_OP ROR_OP RXOR_OP
%token AND NOT OR XOR
%token FUN IF ELIF ELSE FOR WHILE IMPORT CASE SWITCH TYPE
%token INT STR ID

/* if-elif-else parsing, lowest precedence */
%right THEN ELIF ELSE

/* Assignment operators */
%right ASSIGN_OP

/* Logical operators */
%right NOT
%left AND
%left OR XOR

/* binary operators */
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

statement_list:
    statement
    | statement_list statement
    ;

/* TODO add more statement types */
statement:
    expr_statement
    | if_statement
    ;

expr_statement:
    expr SEMICOLON
    ;

/* Precedence/conflicts within sub-expressionss should (if I did it right) be handled by the token precedences above */
expr:
    assign_expr
    | expr, assign_expr
    ;

assign_expr:
    logical_expr
    | unary_expr ASSIGN_OP assign_expr
    ;

logical_expr:
    bitwise_expr
    | logical_expr OR logical_expr
    | logical_expr AND logical_expr
    ;

/* I think these all need to be terminals for precedence to work, but feel free to correct it if not */
unary_expr:
    primary_expr
    | NOT logical_expr %prec UNARY
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

primary_expr:
    ID
    | constant
    | (expr)
    ;

/* TODO Add more constant types */
constant:
    INT
    ;

if_elif:
    IF LPAREN expr RPAREN LBRACE statement_list RBRACE %prec THEN
    | if_elif ELIF LPAREN expr RPAREN LBRACE statement_list RBRACE
    ;

if_statement:
    if_elif
    | if_elif ELSE LBRACE statement_list RBRACE
    ;

