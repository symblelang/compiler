/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <string.h>

#include "syntax_tree.h"
#include "symbol_table.h"

Node * add_var_dec_node(char * name, Type * type, Node * init) {
    Node * new = malloc(sizeof(Node));
    new->tag = var_dec_node;
    new->op.varDec.name = name;
    new->op.varDec.type = type;
    new->op.varDec.init = init;
    return new;
}

Node * add_type_def_node(char * name, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = type_def_node;
    new->op.typeDef.name = name;
    new->op.typeDef.type = type;
    return new;
}

Node * add_binary_expr_node(char * op, Node * left, Node * right, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = binary_expr_node;
    new->op.binaryExpr.op = op;
    new->op.binaryExpr.left = left;
    new->op.binaryExpr.right = right;
    new->op.binaryExpr.type = type;
    return new;
}

Node * add_unary_expr_node(char * op, Node * child, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = unary_expr_node;
    new->op.unaryExpr.op = op;
    new->op.unaryExpr.child = child;
    new->op.unaryExpr.type = type;
    return new;
}

Node * add_lit_node(char * key, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = literal_node;
    new->op.literal.type = type;
    new->op.literal.name = key;
    return new;
}

Node * add_var_node(char * key, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = var_node;
    new->op.var.type = type;
    new->op.var.name = key;
    return new;
}

Node * add_do_loop_node(Node * test, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = do_loop_node;
    new->op.do_loop.test = test;
    new->op.do_loop.block = block;
    return new;
}

Node * add_while_loop_node(Node * test, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = while_loop_node;
    new->op.while_loop.test = test;
    new->op.while_loop.block = block;
    return new;
}

Node * add_for_loop_node(Node * init, Node * test, Node * inc, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = for_loop_node;
    new->op.for_loop.init = init;
    new->op.for_loop.test = test;
    new->op.for_loop.inc = inc;
    new->op.for_loop.block = block;
    return new;
}

Node * add_control_node(Node * expr, ControlType tag) {
    Node * new = malloc(sizeof(Node));
    new->tag = control_node;
    new->op.control.expr = expr;
    new->op.control.tag = tag;
    return new;
}

Node * add_if_node(Node * test, Node * block, Node * next) {
    Node * new = malloc(sizeof(Node));
    new->tag = if_node;
    new->op.if_statement.test = test;
    new->op.if_statement.block = block;
    new->op.if_statement.next = next;
    return new;
}


Args * create_type_list(Type * type) {
    Args * type_list = malloc(sizeof(Args));
    type_list->type = type;
    type_list->name = NULL;
    return type_list;
}

/* This implementation is hilariously inefficient, but nobody should be writing
 * functions with hundreds of arguments
 * better would be to store a pointer to the first and last args. */
Args * add_to_type_list(Args * type_list, Type * type) {
    Args * where_to_add = type_list;
    while (where_to_add->next != NULL) {
        where_to_add = where_to_add->next;
    }
    where_to_add = (where_to_add->next = malloc(sizeof(Args)));
    where_to_add->type = type;
    where_to_add->name = NULL;
    where_to_add->next = NULL;
    return type_list;
}

CallArgs * create_call_args(Node * expr) {
    CallArgs * arg_list = malloc(sizeof(CallArgs));
    arg_list->expr = expr;
    arg_list->next = NULL;
    return arg_list;
}

/* This implementation is again very inefficient, like add_to_type_list */
CallArgs * add_to_call_args(CallArgs * arg_list, Node * expr) {
    CallArgs * where_to_add = arg_list;
    while (where_to_add->next != NULL) {
        where_to_add = where_to_add->next;
    }
    where_to_add = (where_to_add->next = malloc(sizeof(CallArgs)));
    where_to_add->expr = expr;
    where_to_add->next = NULL;
    return arg_list;
}

Node * add_fun_call_node(char * fun_name, CallArgs * args, Type * return_type, int line_num) {
    Node * new = malloc(sizeof(Node));
    new->tag = fun_call_node;
    new->op.fun_call.name = fun_name;
    new->op.fun_call.args = args;
    new->op.fun_call.type = return_type;
    new->op.fun_call.line_num = line_num;
    return new;
}

Node * add_fun_def_node(char * fun_name, Args * args, Type * return_type, SymbolTable * table, Node * block, int line_num) {
    Node * new = malloc(sizeof(Node));
    new->tag = fun_def_node;
    new->op.fun_def.name = fun_name;
    new->op.fun_def.args = args;
    new->op.fun_def.type = return_type;
    new->op.fun_def.block = block;
    new->op.fun_def.table = table;
    new->op.fun_def.line_num = line_num;
    return new;
}

StatementBlock * create_block(Node * statement) {
    StatementBlock * block = malloc(sizeof(StatementBlock));
    block->statement = statement;
    block->next = NULL;
    return block;
}

StatementBlock * add_to_block(StatementBlock * block, Node * statement) {
    StatementBlock * where_to_add = block;
    while (where_to_add->next != NULL) {
        where_to_add = where_to_add->next;
    }
    where_to_add = (where_to_add->next = malloc(sizeof(StatementBlock)));
    where_to_add->statement = statement;
    where_to_add->next = NULL;
    return block;
}
