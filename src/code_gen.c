#include <stdio.h>

#include "syntax_tree.h"

int code_gen_pass(Node * ast, FILE * out_file) {
        for(StatementBlock * block_pos = ast->op.block; block_pos != NULL; block_pos = block_pos->next) {
        Node * statement = block_pos->statement;
        /* This should cover every possible node type that a statement could be */
        switch(statement->tag) {
            case var_dec_node:
                break;
            case type_def_node:
                break;
            case fun_def_node:
                break;
            case binary_expr_node:
                break;
            case unary_expr_node:
                break;
            case literal_node:
                break;
            case var_node:
                break;
            case while_loop_node:
                break;
            case do_loop_node:
                break;
            case for_loop_node:
                break;
            case control_node:
                break;
            case if_node:
                break;
            case fun_call_node:
                break;
            case block_node:
                break;
            case import_node:
                break;
            default:
                return 1;
        }
    }
    return 0;

}
