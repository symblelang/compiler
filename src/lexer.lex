 /*
  * Authors:
  *   Andrew Clark     - andrew.clark.6@bc.edu
  *   Alex Liu         - alex.liu@bc.edu
  *   Caden Parajuli   - caden.parajuli@bc.edu
  *   Micheal Lebreck  - michael.lebreck@bc.edu
  *   William Morrison - william.morrison.2@bc.edu
  */


 /* Remove unnecessary flex functions for non-interactive scanner */
%option noinput
%option nounput
%option noyywrap

 /* bison-compatible reentrant mode */
%option bison-bridge

 /* Keep track of line numbers */
%option yylineno

 /* Enable start condition stack */
%option stack

 /* Use 8 bits per character (default for most modes) */
%option 8bit

 /* Speed */
%option ecs
%option batch
%option full

 /* include the bison-generated parser header, and forward declarations */
%{
#include "parser.h"
#include "symbol_table.h"
#include "syntax_tree.h"

void set_string_val(YYSTYPE * val, char * text, int length);
%}

 /* Whitespace, IDs, and Integers */
ws_chars            [ \t\n]
ws                  {ws_chars}+
digit               [0-9]
integer             {digit}+
non_id              [^{id_char}]
id_char             (?ix: [a-z_])
id                  {id_char}({id_char}|{digit})*

 /* Operators (not sure what direction we should go with user-defined assign/compare operators) */
plus_opchar         "+"|"-"|"±"|"⊕"|"⊖"|"⊞"|"⊟"|"∪"|"∨"|"⊔"
mult_opchar         "*"|"/"|"%"|"∙"|"∘"|"×"|"★"|"⊗"|"⊘"|"⊙"|"⊛"|"⊠"|"⊡"|"∩"|"∧"|"⊓"
opchar              {plus_opchar}|{mult_opchar}|"&"|"|"|"!"|"~"|"^"
plus_op             {plus_opchar}{opchar}*
mult_op             {mult_opchar}{opchar}*
and_op              "&"{opchar}*
or_op               "|"{opchar}*
not_op              "!"{opchar}*
xor_op              "~"{opchar}*
equals_op           "="
assign_op           ("*"|"/"|"%"|"+"|"-")"="
compare_op          (("=="|"<"|">")"="?)|"!="

 /* Right-associative Operators */
rplus_op            "^"{plus_opchar}{opchar}*
rmult_op            "^"{mult_opchar}{opchar}*
rand_op             "^&"{opchar}*
ror_op              "^|"{opchar}*
rxor_op             "^~"{opchar}*
pow_op              "^"|("^^"{opchar}*)
 /* Note some possible operators might not be caught */

%x comment
%x str


%%


 /* Single-line comment */
"//".*

 /* Mult-line comment */
"/*"          { BEGIN(comment); }
<comment>"*/" { BEGIN(INITIAL); }
<comment>\n   { }
<comment>.    { }

 /* Ignore whitespace */
{ws}                {}

 /* Operators */
{mult_op}           { set_string_val(yylval, yytext, yyleng); return MULT_OP; }
{plus_op}           { set_string_val(yylval, yytext, yyleng); return PLUS_OP; }
{and_op}            { set_string_val(yylval, yytext, yyleng); return BIT_AND_OP; }
{or_op}             { set_string_val(yylval, yytext, yyleng); return BIT_OR_OP; }
{xor_op}            { set_string_val(yylval, yytext, yyleng); return BIT_XOR_OP; }
{not_op}            { set_string_val(yylval, yytext, yyleng); return BIT_NOT_OP; }
{assign_op}         { set_string_val(yylval, yytext, yyleng); return ASSIGN_OP; }
{equals_op}         { set_string_val(yylval, yytext, yyleng); return EQUALS_OP; }
{compare_op}        { set_string_val(yylval, yytext, yyleng); return COMPARE_OP; }

 /* Right-associative Operators */
{rmult_op}          { set_string_val(yylval, yytext, yyleng); return RMULT_OP; }
{rplus_op}          { set_string_val(yylval, yytext, yyleng); return RPLUS_OP; }
{rand_op}           { set_string_val(yylval, yytext, yyleng); return RBIT_AND_OP; }
{ror_op}            { set_string_val(yylval, yytext, yyleng); return RBIT_OR_OP; }
{rxor_op}           { set_string_val(yylval, yytext, yyleng); return RBIT_XOR_OP; }
{pow_op}            { set_string_val(yylval, yytext, yyleng); return POW_OP; }

"("                 return LPAREN;
")"                 return RPAREN;
"["                 return LSQB;
"]"                 return RSQB;
"{"                 return LBRACE;
"}"                 return RBRACE;
","                 return COMMA;
";"                 return SEMICOLON;
"."                 return DOT;
"\\"                return BACKSLASH;
"`"                 return BACKTICK;
"->"                return ARROW;

 /* Keywords */
"and"/{non_id}      return AND;
"not"/{non_id}      return NOT;
"or"/{non_id}       return OR;
"xor"/{non_id}      return XOR;
"fun"/{non_id}      return FUN;
"cfun"/{non_id}     return CFUN;
"if"/{non_id}       return IF;
"elif"/{non_id}     return ELIF;
"else"/{non_id}     return ELSE;
"for"/{non_id}      return FOR;
"while"/{non_id}    return WHILE;
"import"/{non_id}   return IMPORT;
"as"/{non_id}       return AS;
"switch"/{non_id}   return SWITCH;
"case"/{non_id}     return CASE;
"type"/{non_id}     return TYPE;
"return"/{non_id}   return RETURN;
"break"/{non_id}    return BREAK;
"continue"/{non_id} return CONTINUE;
"int"/{non_id}      return INT_TYPE;
"float"/{non_id}    return FLOAT_TYPE;
"str"/{non_id}      return STR_TYPE;
"ptr"/{non_id}      return PTR_TYPE;
"void"/{non_id}     return VOID_TYPE;


 /* We want id to be returned only if a keyword isn't matched */
{id}                {
                         set_string_val(yylval, yytext, yyleng);
                         return ID;
                    }

 /* Numbers (TODO add floats, hex, octal, etc.) */
{integer}           {
                         /* yylval->integer = atoi(yytext); */
                         yylval->string = strndup(yytext, yyleng);
                         return INT_LIT;
                    }


 /* String lexing */
 /* TODO make this more efficient by keeping a variable for the length instead of strcat */

 /* String with no escape sequences */
\"[^"\\]*\"         {
                        yylval->string = strndup(yytext + 1, yyleng - 2);
                        return STR_LIT;
                    }
 /* Enter string state for other strings */
\"[^"\\]*           {
                        yylval->string = strndup(yytext + 1, yyleng - 1);
                        yy_push_state(str);
                        /* No return, so the lexer will continue in the str state */
                    }
<str>{
    [^"\\]+         { strncat(yylval->string, yytext, yyleng); }
    \\n             { strncat(yylval->string, "\n", 1); }
    \\t             { strncat(yylval->string, "\t", 1); }
    \\[\\"]         { strncat(yylval->string, yytext + 1, 1); }
    \\\n            { /* A backslash at the end of the line. Do nothing */ }
    \"              { yy_pop_state(); return STR_LIT; }
}


%%

/* In the future, this can be made more memory-efficient with a token hashtable */
void set_string_val(YYSTYPE * val, char * text, int length) {
    val->string = strndup(text, length);
}