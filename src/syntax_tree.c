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

Node * add_var_dec_node(char * name, Type * type, Symbol * symbol, Node * init) {
    Node * new = malloc(sizeof(Node));
    new->tag = var_dec_node;
    new->op.var_dec.name = name;
    new->op.var_dec.type = type;
    new->op.var_dec.symbol = symbol;
    new->op.var_dec.init = init;
    return new;
}

Node * add_type_def_node(char * name, Type * type, Symbol * symbol) {
    Node * new = malloc(sizeof(Node));
    new->tag = type_def_node;
    new->op.type_def.name = name;
    new->op.type_def.type = type;
    new->op.type_def.symbol = symbol;
    return new;
}

Node * add_binary_expr_node(char * op, Node * left, Node * right, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = binary_expr_node;
    new->op.binary_expr.op = op;
    new->op.binary_expr.op_symbol = NULL;
    new->op.binary_expr.left = left;
    new->op.binary_expr.right = right;
    new->op.binary_expr.type = type;
    return new;
}

Node * add_unary_expr_node(char * op, Node * child, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = unary_expr_node;
    new->op.unary_expr.op = op;
    new->op.unary_expr.op_symbol = NULL;
    new->op.unary_expr.child = child;
    new->op.unary_expr.type = type;
    return new;
}

Node * add_lit_node(char * key, Type * type) {
    Node * new = malloc(sizeof(Node));
    new->tag = literal_node;
    new->op.literal.type = type;
    new->op.literal.name = key;
    return new;
}

Node * add_var_node(char * key, Type * type, Symbol * symbol) {
    Node * new = malloc(sizeof(Node));
    new->tag = var_node;
    new->op.var.type = type;
    new->op.var.name = key;
    new->op.var.symbol = symbol;
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
    type_list->next = NULL;
    return type_list;
}

/** This implementation is hilariously inefficient, but nobody should be writing
 *  functions with hundreds of arguments.
 *  better would be to store static pointers to the first and last args, and
 *  check if type_list is the same as the static first and if so use the static last */
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
    /** \todo Compute mangled_name for fun calls in second pass */
    new->op.fun_call.mangled_name = NULL;
    new->op.fun_call.symbol = NULL;
    new->op.fun_call.line_num = line_num;
    return new;
}

Node * add_fun_def_node(char * fun_name, Args * args, Type * return_type, SymbolTable * table, Node * block, Symbol * symbol, int line_num) {
    Node * new = malloc(sizeof(Node));
    new->tag = fun_def_node;
    new->op.fun_def.name = fun_name;
    new->op.fun_def.args = args;
    new->op.fun_def.type = return_type;
    new->op.fun_def.block = block;
    new->op.fun_def.table = table;
    new->op.fun_def.symbol = symbol;
    new->op.fun_def.line_num = line_num;
    return new;
}

Node * add_import_node(char * module, char * namespace, int line_num) {
    Node * new = malloc(sizeof(Node));
    new->tag = import_node;
    new->op.import.module = module;
    new->op.import.namespace = namespace;
    new->op.import.line_num = line_num;
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

Args * create_arg(Type * type, char * name) {
    Args * arg_list = malloc(sizeof(Args));
    arg_list->type = type;
    arg_list->name = name;
    arg_list->next = NULL;
    return arg_list;
}

/* This implementation is again very inefficient, like add_to_type_list */
Args * add_to_arg_list(Args * type_list, Args * to_add) {
    Args * where_to_add = type_list;
    while (where_to_add->next != NULL) {
        where_to_add = where_to_add->next;
    }
    where_to_add = (where_to_add->next = to_add);
    return type_list;
}

char * get_tag_str(NodeType tag) {
    char * str;
    switch (tag) {
        case var_dec_node:
            str = "var_dec";
            break;
        case type_def_node:
            str = "type_def";
            break;
        case fun_def_node:
            str = "fun_def";
            break;
        case binary_expr_node:;
            str = "binary_expr";
            break;
        case unary_expr_node:
            str = "unary_exp";
            break;
        case literal_node:
            str = "literal";
            break;
        case var_node:
            str = "var";
            break;
        case while_loop_node:
            str = "while_loop";
            break;
        case do_loop_node:
            str = "do_loop";
            break;
        case for_loop_node:
            str = "for_loop";
            break;
        case control_node:
            str = "control";
            break;
        case if_node:
            str = "if";
            break;
        case fun_call_node:
            str = "fun_call";
            break;
        case block_node:
            str = "block";
            break;
        case import_node:
            str = "import";
            break;
        default:
            str = "undefined";
    }
    return strdup(str);
}