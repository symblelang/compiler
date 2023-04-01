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

int main(int argc, char * argv[]) {
    yydebug = 1;
    if (argc > 1) {
        char * filename =  argv[1];
        int ret;
        yyin = open_if_exists(filename);
        printf("Opened file %s\n", filename);
        ret = yyparse();
        fclose(yyin);
        return ret;
    }
    else {
        fprintf(stderr, "error: no input file!\n");
        return EXIT_FAILURE;
    }
}
