%{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "symble_handlers.h"
#include "symbol_table.h"
#include "symble.tab.h"

SymbolTable * symbol_table;
int line_no = 1;
extern int label_no;
extern LabelNo * true_label_no_stack;
extern LabelNo * false_label_no_stack;

int yywrap() {
    return 1;
}
%}

space [ \t]
ws {space}+
digit [0-9]
number {digit}+
identifier [a-zA-Z_][a-zA-Z_0-9]*

%%

{ws}
"\n" { ++line_no; }
boolean { yylval.type_id = BOOLEAN_TYPE; return BOOLEAN_TYPE; }
int1 { yylval.type_id = INT4_TYPE; return INT4_TYPE; }
uint1 { yylval.type_id = INT4_TYPE; return INT4_TYPE; }
int2 { yylval.type_id = INT4_TYPE; return INT4_TYPE; }
uint2 { yylval.type_id = INT4_TYPE; return INT4_TYPE; }
int4 { yylval.type_id = INT4_TYPE; return INT4_TYPE; }
uint4 { yylval.type_id = UINT4_TYPE; return UINT4_TYPE; }
int8 { yylval.type_id = INT8_TYPE; return INT8_TYPE; }
uint8 { yylval.type_id = INT8_TYPE; return INT8_TYPE; }
addrtype { yylval.type_id = ADDRESS_TYPE; return ADDRESS_TYPE; }
procedure { return PROCEDURE; }
function { return FUNCTION; }
run { return RUN; }
if { return IF; }
else { handle_else(); return ELSE; }
while { return WHILE; }
for { return FOR; }
from { return FROM; }
to { return TO; }
by { return BY; }
or { return OR; }
and { return AND; }
not { return NOT; }
return { return RETURN; }
{number} { strcpy(yylval.info.string, yytext); return NUMBER; }
{identifier} { handle_identifier_lexeme(&yylval.info, yytext); return IDENTIFIER; }
"<-" { return LARROW; }
"->" { return RARROW; }
\: { return COLON; }
\( { return LPAREN; }
\) { return RPAREN; }
\{ { return LBRACE; }
\} { return RBRACE; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return TIMES; }
"/" { return DIV; }
"%" { return MOD; }
"==" { return EQ; }
"~=" { return NE; }
"<" { return LT; }
"<=" { return LE; }
">=" { return GE; }
">" { return GT; }
"@" { return DEREFERENCE; }
\, { return COMMA; }
\. { return PERIOD; }

%%
#pragma GCC diagnostic pop
