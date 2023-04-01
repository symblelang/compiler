#include <stdio.h>
#include <stdlib.h>
#include "../bison_out/parser.h"
#include "../flex_out/lexer.h"

extern FILE * yyin;
extern int yydebug;

FILE * open_if_exists(char * to_open) {
    FILE * out_file = fopen(to_open, "r");
    if (out_file == NULL) {
        fprintf(stderr, "Cannot open file %s for reading.\n", to_open);
        exit(EXIT_FAILURE);
    }
    else {
        return out_file;
    }
}

int parse_file(char * filename) {
    int ret;
    yyin = open_if_exists(filename);
    ret = yyparse();
    fclose(yyin);
    putchar('\n');
    return ret;
}

int main(int argc, char * argv[]) {
    /* Parse command line arguments */
    int filename_index = 0;
    int output_filename_index = 0;
    for (int arg_index = 1; arg_index < argc; ++arg_index) {
        if (argv[arg_index][0] == '-') {
            /* Option parsing */
            switch(argv[arg_index][1]) {
                case 'o':
                    /* Set the output filename index and skip it in the loop */
                    output_filename_index = arg_index + 1;
                    arg_index++;
                    break;
                case 'v':
                    yydebug = 1;
                    break;
                case '-':
                    /* Parse long options */
                    break;
                default:
                    fprintf(stderr, "erro: malformed option \"%s\"\n", argv[arg_index]);
            }
        }
        else {
            filename_index = arg_index;
        } 
    }
    if (output_filename_index) {
        /* File output isn't supported yet */
    }
    if (filename_index) {
        return parse_file(argv[filename_index]);
    }
}
