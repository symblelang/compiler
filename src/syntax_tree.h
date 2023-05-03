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
        fun_def_node,
        binary_expr_node,
        unary_expr_node,
        literal_node,
        var_node,
        while_loop_node,
        do_loop_node,
        for_loop_node,
        return_node,
        if_node
} NodeType;


struct Node {
    NodeType tag;
    
    union {
        struct {
            Type * type;
            char * name;
        } var;
        
        struct {
            Type * type;
            char * name;
            Node * init;
        } varDec;

        struct {
            Type * type;
            char * name;
            Node * block;
        } funDef;

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
        
        struct {
            Type * type;
            char * name;
        } literal;
        
        struct {
            Node * test;
            Node * block;
        } while_loop;

        struct {
            Node * test;
            Node * block;
        } do_loop;

        struct {
            Node * init;
            Node * test;
            Node * inc;
            Node * block;
        } for_loop;

        struct {
            Node * expr;
        } ret;

        struct {
            Node * test;
            Node * block;
            Node * next;
        } if_statement;
    } op;
};

Node * add_var_dec_node(char * name, Type * type, Node * init);
Node * add_type_def_node(char * name, Type * type);
Node * add_binary_expr_node(char * op, Node * left, Node * right, Type * type);
Node * add_unary_expr_node(char * op, Node * child, Type * type);
Node * add_lit_node(char * key, Type * type);
Node * add_var_node(char * key, Type * type);
Node * add_while_loop_node(Node * test, Node * block);
Node * add_do_loop_node(Node * test, Node * block);
Node * add_for_loop_node(Node * init, Node * test, Node * inc, Node * block);
Node * add_return_node(Node * expr);
Node * add_if_node(Node * test, Node * block, Node * next);

#endif
