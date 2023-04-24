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
#include "parser.h"

extern SymbolTable * symbol_table;

Node * handle_variable_declaration(Type type, char * id, Node * init, int line_num);
Node * handle_binary_expr(char * operator, Node * left, Node * right);
Node * handle_unary_expr(char * operator, Node * child);

#endif
