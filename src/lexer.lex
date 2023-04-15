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
{mult_op}           return MULT_OP;
{plus_op}           return PLUS_OP;
{and_op}            return BIT_AND_OP;
{or_op}             return BIT_OR_OP;
{xor_op}            return BIT_XOR_OP;
{not_op}            return BIT_NOT_OP;
{assign_op}         return ASSIGN_OP;
{equals_op}         return EQUALS_OP;
{compare_op}        return COMPARE_OP;

 /* Right-associative Operators */
{rmult_op}          return RMULT_OP;
{rplus_op}          return RPLUS_OP;
{rand_op}           return RBIT_AND_OP;
{ror_op}            return RBIT_OR_OP;
{rxor_op}           return RBIT_XOR_OP;
{pow_op}            return POW_OP;

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
"if"/{non_id}       return IF;
"elif"/{non_id}     return ELIF;
"else"/{non_id}     return ELSE;
"for"/{non_id}      return FOR;
"while"/{non_id}    return WHILE;
"import"/{non_id}   return IMPORT;
"switch"/{non_id}   return SWITCH;
"case"/{non_id}     return CASE;
"type"/{non_id}     return TYPE;
"return"/{non_id}   return RETURN;
"break"/{non_id}    return BREAK;
"continue"/{non_id} return CONTINUE;

 /* We want id to be returned only if a keyword isn't matched */
{id}                return ID;

 /* Numbers (TODO add floats, hex, octal, etc.) */
{integer}           {
                         yylval->integer = atoi(yytext);
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


 /* Strings with escape sequences */


%%

