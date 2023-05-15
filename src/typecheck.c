/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <stdio.h>

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
    if (ast->tag == block_node) {
        return block_type_pass(ast->op.block, NULL);
    }
    else {
        yyerror(&ast, "Bad syntax tree\n");
        return 1;
    }
}

int block_type_pass(StatementBlock * block, Node * curr_loop) {
    for(StatementBlock * block_pos = block; block_pos != NULL; block_pos = block_pos->next) {
        Node * statement = block_pos->statement;
        /* This should cover every possible node type that a statement could be */
        switch(statement->tag) {
            case var_dec_node: /* Completed! */
                /* Symbol was created with type in first pass. Check initialization expression */
                if (statement->op.var_dec.init) {
                    set_expr_type(statement->op.var_dec.init);
                }
                break;
            case type_def_node: /* Completed! */
                /* Nothing to check in this pass */
                break;
            case fun_def_node:
                /* run pass on function body if it's not a cfun */
                if (! statement->op.fun_def.block) {
                    continue;
                }
                else if (block_type_pass(statement->op.fun_def.block->op.block, curr_loop)) {
                    return 1;
                }
                break;
            case binary_expr_node: /* Completed! */
                set_expr_type(statement);
                break;
            case unary_expr_node:  /* Completed! */
                set_expr_type(statement);
                break;
            case literal_node:     /* Completed! */
                yyerror(&statement, "Statement consists of just a literal\n");
                break;
            case var_node:         /* Completed! */
                yyerror(&statement, "Statement consists of just a variable\n");
                break;
            case while_loop_node:  /* Completed */
                /* Propogate types in the test expression */
                set_expr_type(statement->op.while_loop.test);
                /* Call block_type_pass with curr_loop */
                if (block_type_pass(statement->op.while_loop.block->op.block, statement)) {
                    return 1;
                }
                break;
            case do_loop_node:     /* Completed */
                /* Propogate types in the test expression */
                set_expr_type(statement->op.while_loop.test);
                /* Call block_type_pass with curr_loop */
                if (block_type_pass(statement->op.do_loop.block->op.block, statement)) {
                    return 1;
                }
                break;
            case for_loop_node:
                yyerror(&statement, "For loops aren't supported yet.\n");
                break;
            case control_node:
                /* Make sure we're in a loop (only for non-return) */
                if ((curr_loop == NULL) && (statement->op.control.expr == NULL)) {
                    yyerror(&statement, "Break and continue can only be used in a loop.\n");
                }
                else if (statement->op.control.expr) {
                    set_expr_type(statement->op.control.expr);
                }
                break;
            case if_node:
                /** \todo check elif and else as well */
                if (block_type_pass(statement->op.if_statement.block->op.block, curr_loop)) {
                    return 1;
                }
                break;
            case fun_call_node: /* Completed */
                /* We don't actually need the type, but we must typecheck the arguments */
                set_fun_call_type(statement);
                break;
            case block_node:    /* Completed */
                yyerror(&statement, "A block cannot stand on its own. There is an error with the Bison grammar\n");
                break;
            case import_node:
                yyerror(&statement, "Importing isn't supported yet.\n");
                break;
            default:            /* Completed */
                yyerror(&statement, "Unsupported statement type. Ensure typecheck.c covers every statement node tag\n");
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
    Symbol * op_symbol;
    switch(expr->tag) {
        case unary_expr_node:
            if (expr->op.unary_expr.type != NULL) {
                return expr->op.unary_expr.type;
            }
            arg1_type = set_expr_type(expr->op.unary_expr.child);
            mangled_op_name = mangle_unary_op(expr->op.unary_expr.op, arg1_type);
            if ((op_symbol = get_symbol_lexical_scope(symbol_table, mangled_op_name))) {
                expr->op.unary_expr.type = op_symbol->op.fun.type;
            }
            free(mangled_op_name);
            return expr->op.unary_expr.type;
            
        case binary_expr_node:
            if (expr->op.binary_expr.type != NULL) {
                return expr->op.binary_expr.type;
            }
            arg1_type = set_expr_type(expr->op.binary_expr.left);
            Type * arg2_type = set_expr_type(expr->op.binary_expr.right);
            mangled_op_name = mangle_binary_op(expr->op.binary_expr.op, arg1_type, arg2_type);
            if ((op_symbol = get_symbol_lexical_scope(symbol_table, mangled_op_name))) {
                expr->op.binary_expr.op_symbol = op_symbol;
                expr->op.binary_expr.type = op_symbol->op.fun.type;
            }
            else {
                yyerror(&expr, "Operator %s with correct argument types (%s) not found\n", expr->op.binary_expr.op, mangled_op_name);
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
            yyerror(&expr, "Internal compiler function set_expr_type got unsupported node. Check typecheck.c\n");
            return NULL;
    }
}

/** \brief Sets fun_call type and mangled_name, returning the return type of the call.
 *  \todo For efficiency purposes this should reimpliment mangle_fun_name with CallArgs,
 *  but that's a significant amount of work for something this small and late
 */
Type * set_fun_call_type(Node * call) {
    char * mangled_fun_name;
    Symbol * fun_symbol;
    Args * args = NULL;
    Args * curr_arg = args;
    CallArgs * call_args = call->op.fun_call.args;
    
    /* Create Args from CallArgs by propogating types */
    if (call_args != NULL) {
        args = malloc(sizeof(Args));
        curr_arg = args;
        curr_arg->type = set_expr_type(call_args->expr);
        call_args = call_args->next;
        for (; call_args != NULL; call_args = call_args->next) {
            curr_arg->next = malloc(sizeof(Args));
            curr_arg = curr_arg->next;
            curr_arg->type = set_expr_type(call_args->expr);
        }
        curr_arg->next = NULL;
    }
    mangled_fun_name = mangle_fun_name(call->op.fun_call.name, args);

    /* Get symbol from symbol table */
    if ((fun_symbol = get_symbol_lexical_scope(symbol_table, mangled_fun_name))) {
        call->op.fun_call.type = fun_symbol->op.fun.type;
        call->op.fun_call.mangled_name = fun_symbol->op.fun.name;
    }
    else if ((fun_symbol = get_symbol_lexical_scope(symbol_table, call->op.fun_call.name))) {
        /* C function */
        call->op.fun_call.type = fun_symbol->op.fun.type;
        call->op.fun_call.mangled_name = fun_symbol->op.fun.name;
    }
    else {
        yyerror(&call, "Function %s with correct argument types not found\n", call->op.fun_call.name);
    }

    /* Free allocated memory */
    for (Args * past = args; past != NULL; past = args) {
        args = args->next;
        free(past);
    }
    free(mangled_fun_name);
    return call->op.fun_call.type;
}
