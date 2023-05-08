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
typedef struct CallArgs CallArgs;
typedef struct StatementBlock StatementBlock;

struct CallArgs {
    Node * expr;
    CallArgs * next;
};

struct StatementBlock {
    /** Used for both statement_list and statement_block */
    Node * statement;
    StatementBlock * next;
};

typedef enum {return_tag, break_tag, continue_tag} ControlType;

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
        control_node,
        if_node,
        fun_call_node,
        block_node
} NodeType;

/** \todo Fix naming scheme */
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
            /** if type is not return, expr should be NULL */
            Node * expr;
            ControlType tag;
        } control;

        struct {
            Node * test;
            Node * block;
            Node * next;
        } if_statement;

        struct {
            char * name;
            Type * type; /* return type */
            CallArgs * args;
            int line_num;
        } fun_call;

        struct {
            /** Some of these fields may be redundant since they're in the FunSymbol */
            char * name; /* This should be mangled */
            Type * type; /* return type */
            Args * args;
            SymbolTable * table;
            Node * block;
            int line_num;
        } fun_def;
        
        StatementBlock * block;
        
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
Node * add_control_node(Node * expr, ControlType tag);
Node * add_if_node(Node * test, Node * block, Node * next);
Node * add_fun_call_node(char * fun_name, CallArgs * args, Type * return_type, int line_num);
CallArgs * create_call_args(Node * expr);
CallArgs * add_to_call_args(CallArgs * arg_list, Node * expr);
Node * add_fun_def_node(char * fun_name, Args * args, Type * return_type, SymbolTable * table, Node * block, int line_num);
StatementBlock * create_block(Node * statement);
StatementBlock * add_to_block(StatementBlock * block, Node * statement);

#endif
