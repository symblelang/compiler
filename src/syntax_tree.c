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
