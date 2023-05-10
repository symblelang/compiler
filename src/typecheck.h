/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "syntax_tree.h"

/** Performs type checking on the AST and propogation of types through expressions */
int type_pass(Node * ast);

/** Recursively computes expression type, setting intermediate types as it goes. */
Type * set_expr_type(Node * expr);

/** Sets fun_call type and mangled_name, returning the return type of the call. */
Type * set_fun_call_type(Node * call);

/**  */
int block_type_pass(StatementBlock * block, Node * curr_loop);

#endif /* TYPECHECK_H */
