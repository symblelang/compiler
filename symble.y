%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"
#include "symble_handlers.h"
#include "symbol_table.h"
#include "symble.tab.h"

int yylex();
int yyerror(const char * msg);

extern FILE * yyin;
extern SymbolTable * symbol_table;
extern int line_no;
int label_no;
LabelNo * true_label_no_stack;
LabelNo * false_label_no_stack;

%}

%union {
    Info info;
    char string[LEXEME_SIZE];
    int type_id;
}

%code provides {
    int yylex();
    int yyerror(const char * msg);
}

%token PROCEDURE FUNCTION RUN IF ELSE WHILE FOR FROM TO BY RETURN
%token PERIOD COLON LPAREN RPAREN LBRACE RBRACE LARROW RARROW COMMA DEREFERENCE
%token PLUS TIMES DIV MOD EQ NE LT LE GE GT AND OR NOT
%token <type_id> BOOLEAN_TYPE INT1_TYPE UINT1_TYPE INT2_TYPE UINT2_TYPE
%token <type_id> INT4_TYPE UINT4_TYPE INT8_TYPE UINT8_TYPE ADDRESS_TYPE
%token <info> IDENTIFIER NUMBER MINUS
%type <type_id> type_expression
%type <info> expression arithmetic_expression relational_expression logical_expression
%type <info> function_call_expression dereference_expression procedure_id function_id 
%type <info> variable_declaration param arg

%left OR
%left AND
%left EQ NE
%left LT LE GT GE
%left PLUS MINUS
%left TIMES DIV MOD
%right DEREFERENCE UMINUS NOT
%%

program : unit_definitions { puts("Done."); }

unit_definitions : unit_definitions unit_definition
                 | unit_definition
                 ;

unit_definition : procedure_definition { printf("ret\n\n"); }
       | function_definition { putchar('\n'); }
       ;

procedure_definition : procedure_head block
                     ;

function_definition : function_head block
                    ;

procedure_head : procedure_id params_list
               ;

function_head : function_id params_list RARROW type_expression
              ;

procedure_id : PROCEDURE IDENTIFIER { handle_unit_id(&$2); }
             ;

function_id : FUNCTION IDENTIFIER { handle_unit_id(&$2); }
            ;

params_list : LPAREN params RPAREN
            ;

block : block_start block_rest
      ;

block_start : LBRACE {
    if (symbol_table->unit_started) {
        symbol_table->unit_started = 0;
    } else {
        push_symbol_table();
    }
}
            ;

block_rest : statements RBRACE { pop_symbol_table(); }
           ;



params : params COMMA param
       | param
       |
       ;

param : variable_declaration { handle_param(&$$, &$1); }
      ;


type_expression : INT1_TYPE { $$ = $1; }
                | UINT1_TYPE { $$ = $1; }
                | INT2_TYPE { $$ = $1; }
                | UINT2_TYPE { $$ = $1; }
                | INT4_TYPE { $$ = $1; }
                | UINT4_TYPE { $$ = $1; }
                | INT8_TYPE { $$ = $1; }
                | UINT8_TYPE { $$ = $1; }
                | ADDRESS_TYPE LPAREN type_expression RPAREN { $$ = $1; }
                ;

statements : statements statement
           | statement
           ;

statement : initialized_variable_declaration_statement
          | variable_declaration_statement
          | assignment_statement
          | procedure_call_statement
          | conditional_statement
          | iteration_statement
          | return_statement
          | block
          ;

initialized_variable_declaration_statement : variable_declaration LARROW expression PERIOD
    { handle_initialization(&$1, &$3); }
                                           ;

variable_declaration_statement : variable_declaration PERIOD
                     ;
                               ;
assignment_statement : IDENTIFIER LARROW expression PERIOD { handle_assignment(NULL, &$3, &$1); }
                     | expression RARROW IDENTIFIER PERIOD { handle_assignment(NULL, &$1, &$3); }
                     ;

procedure_call_statement : RUN IDENTIFIER LPAREN args RPAREN PERIOD
                         ;

conditional_statement : condition_head block ELSE block { handle_condition(1); }
                      | condition_head block { handle_condition(0); }
                      ;

condition_head : IF LPAREN expression RPAREN { handle_condition_head(&$3); }
               ;

iteration_statement : WHILE LPAREN expression RPAREN LBRACE expression RBRACE
                    | FOR LPAREN variable_declaration FROM expression TO expression BY expression 
                       LBRACE statements RBRACE
                    ;

return_statement : RETURN expression PERIOD { printf("mov %s, $ret\n", $2.string); printf("ret\n"); }

variable_declaration : IDENTIFIER COLON type_expression { handle_variable_declaration( &$$, &$1, $3); }
                     ;

expression : arithmetic_expression
           | relational_expression
           | logical_expression
           | function_call_expression
           | dereference_expression
           | MINUS expression %prec UMINUS { handle_unary_minus_expression(&$$, &$2); }
           | NUMBER { handle_number(&$$, &$1); }
           | IDENTIFIER { handle_identifier(&$$, &$1); }
           | LPAREN expression RPAREN { $$ = $2; }
           ;

arithmetic_expression : expression PLUS expression { handle_arithmetic_expression(&$$, PLUS, &$1, &$3); }
        | expression MINUS expression { handle_arithmetic_expression(&$$, MINUS, &$1, &$3); }
        | expression TIMES expression { handle_arithmetic_expression(&$$, TIMES, &$1, &$3); }
        | expression DIV expression { handle_arithmetic_expression(&$$, DIV, &$1, &$3); }
        | expression MOD expression { handle_arithmetic_expression(&$$, MOD, &$1, &$3); }
        ;

relational_expression : expression EQ expression { handle_relational_expression(&$$, EQ, &$1, &$3); }
        | expression NE expression { handle_relational_expression(&$$, NE, &$1, &$3); }
        | expression LT expression { handle_relational_expression(&$$, LT, &$1, &$3); }
        | expression LE expression { handle_relational_expression(&$$, LE, &$1, &$3); }
        | expression GE expression { handle_relational_expression(&$$, GE, &$1, &$3); }
        | expression GT expression { handle_relational_expression(&$$, GT, &$1, &$3); }
        ;

logical_expression : expression AND expression { handle_logical_expression(&$$, AND, &$1, &$3); }
        | expression OR expression { handle_logical_expression(&$$, OR, &$1, &$3); }
        | NOT expression { handle_logical_expression(&$$, NOT, &$2, NULL); }
        ;

function_call_expression : IDENTIFIER LPAREN args RPAREN {
    strcpy($$.string, "$ret");
    printf("call _%s\n", $1.string);
}
                         ;

dereference_expression : DEREFERENCE IDENTIFIER {
    get_new_register($$.string);
    printf("%s = address %s\n", $$.string, $2.string);
}
                       | DEREFERENCE LPAREN expression RPAREN
                           { get_new_register($$.string); printf("%s = address %s\n", $$.string, $3.string); }
                       ;


args : args COMMA expression
     | arg
     ;

arg : expression { handle_arg(&$$, &$1); }
     ;

%%

int yyerror(const char * msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

FILE * fopen_checked(const char * const file_name, const char * const mode) {
    FILE * fp = fopen(file_name, mode);
    if (!fp) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

int main(int argc, char ** argv) {
    if (argc > 1) {
        yyin = fopen_checked(argv[1], "r");
    }
    push_symbol_table();
    yyparse();
    if (argc > 1) {
        fclose(yyin);
    }
    pop_symbol_table();
    return EXIT_SUCCESS;
}

