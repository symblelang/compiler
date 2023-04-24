/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

/* Header guards */
#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include "symbol_table.h"

typedef struct Node Node;

typedef enum {
        var_dec_node,
        type_def_node,
        binary_expr_node,
        unary_expr_node
} NodeType;

struct Node {
    NodeType tag;
    
    union {
        struct {
            Type * type;
            char * name;
            Node * init;
        } varDec;
        
        struct {
            Type * type;
            char * name;
        } typeDef;

        struct {
            Type * type;
            char * op;
            Node * left;
            Node * right;
        } binaryExpr;

        struct {
            Type * type;
            char * op;
            Node * child;
        } unaryExpr;
    } op;
};

Node * add_var_dec_node(char * name, Type * type, Node * init);
Node * add_type_def_node(char * name, Type * type);
Node * add_binary_expr_node(char * op, Node * left, Node * right, Type * type);
Node * add_unary_expr_node(char * op, Node * child, Type * type);

#endif
