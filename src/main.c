/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <stdio.h>
#include <stdlib.h>

#include "arch.h" /* Error out if unsupported architecture */
#include "code_gen.h"
#include "parser.h"
#include "lexer.h" /* Must be included after parser.h */
#include "symbol_table.h"
#include "syntax_tree.h"
#include "typecheck.h"

extern FILE * yyin;
extern int yydebug;

FILE * fopen_checked(const char * const to_open, const char * mode) {
    FILE * out_file = fopen(to_open, mode);
    if (out_file == NULL) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }
    else {
        return out_file;
    }
}

int compile_file(char * filename, char * output_filename) {
    int yy_ret;
    int type_pass_ret;
    Node * ast = NULL;
    
    /* First pass: Parse file, store syntax tree in ast out-param */
    yyin = fopen_checked(filename, "r");
    /* yydebug = 1; */
    yy_ret = yyparse(&ast);
    if (yy_ret == 1) {
        yyerror(&ast, "yyparse failed because input is invalid and error recovery is impossible.\n");
        return EXIT_FAILURE;
    }
    else if (yy_ret == 2) {
        yyerror(&ast, "yyparse failed because the compiler ran out of memory.\n");
    }
    fclose(yyin);

    printf("first pass complete!\n");

    /* Maybe convert for to while before type checking */

    /* Second pass: Type propogation and checking */
    type_pass_ret = type_pass(ast);
    if (type_pass_ret) {
        yyerror(&ast, "Typechecking failed.\n");
    }

    printf("second pass complete!\n");

    /* Possible third pass for desugaring: function lifting, closure conversion, for to while, etc. */
    
    /* Final pass: code generation */
    code_gen_pass(ast, filename, output_filename);

    printf("final pass complete!\n");

    putchar('\n');
    return yy_ret;
}

void check_parameter(int argc, int param_loc, char * option) {
    if (argc < param_loc + 1) {
        fprintf(stderr, "error: command-line option %s requires file name parameter\n", option);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[]) {
    /** Command line interface */
    /* Parse command line arguments */
    int filename_index = 0;
    int output_filename_index = 0;
    int dot_filename_index = 0;
    char * opt_char;
    char * output_filename = NULL;
    for (int arg_index = 1; arg_index < argc; ++arg_index) {
        opt_char = argv[arg_index];
        if (opt_char[0] == '-') {
            opt_char++;
            /* Option parsing */
            switch(*opt_char) {
                case 'o':
                    /* Set the output filename index and skip it in the loop */
                    output_filename_index = arg_index + 1;
                    arg_index++;
                    break;
                case 'v':
                    yydebug = 1;
                    break;
                case '-':;
                    /* Parse long options */
                    opt_char++;
                    if (! strncmp(opt_char, "dot", 4)) {
                        dot_filename_index = arg_index + 1;
                        check_parameter(argc, dot_filename_index, "--dot");
                        arg_index++;
                    }
                    break;
                default:
                    fprintf(stderr, "error: malformed option \"%s\"\n", argv[arg_index]);
            }
        }
        else {
            if (filename_index) {
                fprintf(stderr, "error: multiple input files given!\n");
            }
            filename_index = arg_index;
        } 
    }

    if (dot_filename_index) {
        /** \todo Implement Graphviz dot generation for the syntax tree */
    }
    
    if (output_filename_index) {
        if (argc < filename_index + 1) {
            fprintf(stderr, "error: command-line option -o requires file name parameter\n");
            return EXIT_FAILURE;
        }
        output_filename = argv[output_filename_index];
    }
    else {
        output_filename = "a.s";
    }
    
    if (filename_index) {
        return compile_file(argv[filename_index], output_filename);
    }
    else {
        fprintf(stderr, "error: no input file given\n");
    }
}
