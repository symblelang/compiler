/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

/* Header guards */
#ifndef HANDLERS_H
#define HANDLERS_H

#include "symbol_table.h"
#include "syntax_tree.h"
#include "types.h"
#include "parser.h"

extern SymbolTable * symbol_table;

Node * handle_variable_declaration(Type * type, char * id, Node * init, int line_num);
Node * handle_binary_expr(Node * left, char * operator, Node * right);
Node * handle_unary_expr(char * operator, Node * child);
Node * handle_member_expr(Node * base, Node * child, int is_dot);
Node * handle_var(char * name);
Node * handle_literal(char * value, BaseType lit_type);
Node * handle_function_def(char * name, Args * args, Type * return_type, Node * block, int line_num);
Type * handle_base_type(BaseType base);
Type * handle_custom_type(char * type_name);
ArgTypes * create_type_list(Type * type);
ArgTypes * add_to_type_list(ArgTypes * type_list, Type * type);
Type * handle_fun_type(ArgTypes * type_list, Type * return_type);
Node * handle_member_expr(Node * base, Node * child, int is_dot);
Node * handle_function_call(char * function_name, Node * args, int line_num);
Node * handle_if(Node * test, Node * block, Node * next);
Node * handle_while(Node * test, Node * block);
Node * handle_for(Node * init, Node * test, Node * inc, Node * block);
Node * handle_do(Node * test, Node * block);
Node * handle_return(Node * expr);
Node * handle_typedef(char * name, Type * type);
Node * handle_create_array();

#endif
