
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
%token ID
%token INT STR
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON
%token PLUS_OP MULT_OP AND_OP OR_OP NOT_OP XOR_OP RPLUS_OP RMULT_OP RAND_OP ROR_OP RXOR_OP
%token AND NOT OR XOR FUN IF ELIF ELSE FOR WHILE IMPORT CASE SWITCH TYPE

/* binary operators */
%left NOT_OP
%left AND_OP
%left OR_OP XOR_OP
%right RAND_OP ROR_OP RNOT_OP RXOR_OP

/* Arithmetic operators */
%left PLUS_OP MULT_OP
%right RPLUS_OP RMULT_OP

/* Logical operators */
%left AND NOT OR XOR


/* if-elif-else parsing */
%right "then" ELIF ELSE

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

/* Do we want semicolons? */
expr_statement:
    expr SEMICOLON
    ;

expr:
    assign_expr /* assignment has lowest precedence after comma */
    | expr, assign_expr
    ;

assign_expr:
    
    ;

if_elif:
      IF LPAREN expr RPAREN LBRACE statement_list RBRACE %prec "then"
    | if_elif ELIF LPAREN expr RPAREN LBRACE statement_list RBRACE
    ;

if_statement:
    if_elif
    | if_elif ELSE LBRACE statement_list RBRACE
    ;

