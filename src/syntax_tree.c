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

Node * add_fun_def_node(char * name, Type * type, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = fun_def_node;
    new->op.funDef.name = name;
    new->op.funDef.type = type;
    new->op.funDef.block = block;
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

Node * add_while_loop_node(Node * test, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = while_loop_node;
    new->op.while_loop.test = test;
    new->op.while_loop.block = block;
    return new;
}
Node * add_do_loop_node(Node * test, Node * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = do_loop_node;
    new->op.while_loop.test = test;
    new->op.while_loop.block = block;
    return new;
}
Node * add_return_node(Node * expr) {
    Node * new = malloc(sizeof(Node));
    new->tag = return_node;
    new->op.ret.expr = expr;
    return new;
}
Node * add_if_node(Node * test, Node * block, Node * next) {
    Node * new = malloc(sizeof(Node));
    new->op.if_statement.test = test;
    new->op.if_statement.block = block;
    new->op.if_statement.next = next;
    return new;
}