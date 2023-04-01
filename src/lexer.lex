 /*
  * Author: Caden Parajuli - caden.parajuli@bc.edu
  */


 /* Remove unnecessary flex functions
  * Note that with these we don't need to include the flex library */
%option noinput
%option nounput
%option noyywrap

 /* Options for speed and functionality */
%option bison-bridge
%option stack
%option 8bit
%option yylineno
%option ecs
 /* %option align */
 /* %option full */

 /* include the bison-generated parser header, and forward declarations */
%{
#include "../bison_out/parser.h"
void string_format(char * str);
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
opchar              {plus_opchar}|{mult_opchar}|"&"|"|"|"!"|"^"
plus_op             {plus_opchar}{opchar}*
mult_op             {mult_opchar}{opchar}*
and_op              "&"{opchar}*
or_op               "|"{opchar}*
not_op              "!"{opchar}*
xor_op              "~"{opchar}*
assign_op           ("*"|"/"|"%"|"+"|"-")?"="
compare_op          (("=="|"<"|">")"="?)|"!="

 /* Right-associative Operators */
rplus_op            "^"{plus_opchar}{opchar}*
rmult_op            "^"{mult_opchar}{opchar}*
rand_op             "^&"{opchar}*
ror_op              "^|"{opchar}*
rxor_op             "^~"{opchar}*
pow_op              "^"|("^^"{opchar}*)
 /* Note some possible operators are not caught by this */

%x comment

%%

 /* Single-line comment */
"//".*

 /* Ignore whitespace */
{ws}

 /* Operators */
{mult_op}           return MULT_OP;
{plus_op}           return PLUS_OP;
{and_op}            return AND_OP;
{or_op}             return OR_OP;
{xor_op}            return XOR_OP;
{not_op}            return NOT_OP;
{assign_op}         return ASSIGN_OP;
{compare_op}        return COMPARE_OP;

 /* Right-associative Operators */
{rmult_op}          return RMULT_OP;
{rplus_op}          return RPLUS_OP;
{rand_op}           return RAND_OP;
{ror_op}            return ROR_OP;
{rxor_op}           return RXOR_OP;
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

 /* We want id to be returned only if a keyword isn't matched */
{id}                return ID;

 /* Numbers (TODO add floats, hex, octal, etc.) */
{integer}           {printf("%d ", *yylval); return INT_LIT;}


 /* String */
\"([^\\\"]|\\.)*\"  {
                    /* string_format(yytext); */
                    return STR_LIT;
                    }


 /* Comment */
"/*"                yy_push_state(comment);
<comment>{
[^*\n]*
"*"+[^*/\n]*
"\n"
"*"+"/"             yy_pop_state();
}

%%

 /* Used to edit yytext for escape sequences */
void string_format(char * str) {
    char * curr_pos = str;
    char * to_replace = str;
    while(curr_pos) {
        if (*curr_pos == '\\') {
            switch(*(curr_pos + 1)) {
                case 'n':
                    *to_replace = '\n';
                    break;
                case 'a':
                    *to_replace = '\a';
                    break;
                case 'b':
                    *to_replace = '\b';
                    break;
                case 'f':
                    *to_replace = '\f';
                    break;
                case 'r':
                    *to_replace = '\r';
                    break;
                case 't':
                    *to_replace = '\t';
                    break;
                case 'v':
                    *to_replace = '\v';
                    break;
                case '\\':
                    *to_replace = '\\';
                    break;
                case '\"':
                    *to_replace = '\"';
                    break;
                case '\'':
                    *to_replace = '\'';
                    break;
                default:
                    yyerror("Bad escape sequence");
            }
            curr_pos += 2;
            to_replace += 1;
            continue;
        }
        else {
            curr_pos++;
            to_replace++;
        }
    }
    *to_replace='\0';
}
