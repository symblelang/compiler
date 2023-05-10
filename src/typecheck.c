/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include "parser.h"
#include "symbol_table.h"
#include "syntax_tree.h"
#include "typecheck.h"
#include "types.h"

/** \brief Performs type checking on the AST and propogation of types through expressions
 *  Performs the second pass over the syntax tree (the first pass after tree generation).
 *  This pass consists of propogating types up through expressions, and checking types for operators,
 *  function calls, etc.
 */
int type_pass(Node * ast) {
    return block_type_pass(ast->op.block, NULL);
}

int block_type_pass(StatementBlock * block, Node * curr_loop) {
    for(StatementBlock * block_pos = block; block_pos != NULL; block_pos = block_pos->next) {
        Node * statement = block_pos->statement;
        /* This should cover every possible node type that a statement could be */
        switch(statement->tag) {
            case var_dec_node: /* Completed! */
                /* Symbol was created with type in first pass. Check initialization expression */
                set_expr_type(statement->op.var_dec.init);
                break;
            case type_def_node: /* Completed! */
                /* Nothing to check in this pass */
                break;
            case fun_def_node:
                break;
            case binary_expr_node: /* Completed! */
                set_expr_type(statement);
                break;
            case unary_expr_node:  /* Completed! */
                set_expr_type(statement);
                break;
            case literal_node:     /* Completed! */
                yyerror(statement, "Statement consists of just a literal\n");
                break;
            case var_node:         /* Completed! */
                yyerror(statement, "Statement consists of just a variable\n");
                break;
            case while_loop_node:  /* Completed */
                /* Propogate types in the test expression */
                set_expr_type(statement->op.while_loop.test);
                /* Call block_type_pass with curr_loop */
                block_type_pass(statement->op.while_loop.block->op.block, statement);
                break;
            case do_loop_node:     /* Completed */
                /* Propogate types in the test expression */
                set_expr_type(statement->op.while_loop.test);
                /* Call block_type_pass with curr_loop */
                block_type_pass(statement->op.while_loop.block->op.block, statement);
                break;
            case for_loop_node:
                break;
            case control_node:
                /* Make sure we're in a loop (only for non-return) */
                if (curr_loop == NULL) {
                }
                break;
            case if_node:
                break;
            case fun_call_node:
                /* We don't actually need the type, but we must typecheck the arguments */
                set_fun_call_type(statement);
                break;
            case block_node:
                yyerror(statement, "A block cannot stand on its own. There is an error with the Bison grammar\n");
                break;
            case import_node:
                break;
            default:
                yyerror(statement, "Unsupported statement type. Ensure typecheck.c covers every statement node tag\n");
                return 1;
        }
    }
    return 0;
}

/** \brief Recursively computes and sets expression type, setting intermediate types as it goes.
 *  Recursively calls itself to propogate type information through an expression.
 *  Also sets the type of intermediate nodes such as literal_node and var_node */
Type * set_expr_type(Node * expr) {
    Type * arg1_type;
    char * mangled_op_name;
    FunSymbol * op_symbol;
    switch(expr->tag) {
        case unary_expr_node:;
            arg1_type = set_expr_type(expr->op.unary_expr.child);
            mangled_op_name = mangle_unary_op(expr->op.unary_expr.op, arg1_type);
            if ((op_symbol = get_symbol_lexical_scope(symbol_table, mangled_op_name))) {
                expr->op.unary_expr.type = op_symbol->type;
            }
            free(mangled_op_name);
            return expr->op.unary_expr.type;
            
        case binary_expr_node:
            arg1_type = set_expr_type(expr->op.binary_expr.left);
            Type * arg2_type = set_expr_type(expr->op.binary_expr.right);
            mangled_op_name = mangle_binary_op(expr->op.binary_expr.op, arg1_type, arg2_type);
            if ((op_symbol = get_symbol_lexical_scope(symbol_table, mangled_op_name))) {
                expr->op.binary_expr.type = op_symbol->type;
            }
            else {
                yyerror(expr, "Operator %s with correct argument types not found\n", expr->op.binary_expr.op);
            }
            free(mangled_op_name);
            return expr->op.binary_expr.type;
            
        case literal_node:
            /* Literal types were set in first pass */
            return expr->op.literal.type;

        case var_node:
            /* var types were set in first pass */
            return expr->op.var.type;
        /** \todo Add cases for function_call etc. */
        case fun_call_node:
            return set_fun_call_type(expr);
            
        default:
            yyerror(expr, "Internal compiler function set_expr_type got unsupported node. Check typecheck.c\n");
            return NULL;
    }
}

/** \brief Sets fun_call type and mangled_name, returning the return type of the call.
 *  \todo For efficiency purposes this should reimpliment mangle_fun_name with CallArgs,
 *  but that's a significant amount of work for something this small and late
 */
Type * set_fun_call_type(Node * call) {
    char * mangled_fun_name;
    FunSymbol * fun_symbol;
    Args * args = malloc(sizeof(Args));
    Args * curr_arg = args;
    
    /* Create Args from CallArgs by propogating types */
    for (CallArgs * call_args = call->op.fun_call.args; call_args != NULL; call_args = call_args->next) {
        curr_arg = (curr_arg->next = malloc(sizeof(Args)));
        curr_arg->type = set_expr_type(call_args->expr);
    }
    curr_arg->next = NULL;
    mangled_fun_name = mangle_fun_name(call->op.fun_call.name, args);

    /* Get symbol from symbol table */
    if ((fun_symbol = get_symbol_lexical_scope(symbol_table, mangled_fun_name))) {
        call->op.fun_call.type = fun_symbol->type;
        call->op.fun_call.mangled_name = fun_symbol->name;
    }
    else {
        yyerror(call, "Function %s with correct argument types not found\n", call->op.fun_call.name);
    }

    /* Free allocated memory */
    free(mangled_fun_name);
    for (; args != NULL; args = args->next) {
        free(args);
    }
    return call->op.fun_call.type;
}
