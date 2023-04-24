/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <stdio.h>

#include "symbol_table.h"
#include "syntax_tree.h"
#include "types.h"
#include "parser.h"

Node * handle_variable_declaration(Type * type, char * id, Node * init, int line_num) {
    VarSymbol * var = malloc(sizeof(VarSymbol));
    var->name = id;
    var->type = type;
    var->declared_at = line_num;
    if (set_symbol(symbol_table, id, var)) {
        fprintf(stderr, "Redeclaration of variable \"%s\" on line %d. \"%s\" already defined on line %d.",
                id, line_num, id, ((VarSymbol *)get_symbol_lexical_scope(symbol_table, id))->declared_at);
    }
    return add_var_dec_node(var->name, var->type, init);
}

Node * handle_binary_expr(char * operator, Node * left, Node * right) {
    /** Handles any kind of expression with a binary operator */
    /* Get operator from symbol table. In future implement function to find one with correct type,
     * and if not found check for a pre-defined one like + */
    FunSymbol * op_sym = get_symbol_lexical_scope(symbol_table, operator);
    if (op_sym == NULL) {
        fprintf(stderr, "Operator `%s` not defined.", operator);
    }
    /* Check types. This implementation is very rudimentary. */
    /* Note that the C standard allows us to access the type field using
     * binaryExpr even if the node is a unaryExpr */
    if (! ((left->op.binaryExpr.type == get_symbol_lexical_scope(op_sym->symbol_table, op_sym->args->name)) &&
            right->op.binaryExpr.type == get_symbol_lexical_scope(op_sym->symbol_table, op_sym->args->next->name))) {
        fprintf(stderr, "Type of operator `%s` does not match types of arguments.", operator);
    }
    return add_binary_expr_node(operator, left, right, op_sym->type->op.fun.return_type);
}

Node * handle_unary_expr(char * operator, Node * child) {
    /** Handles any kind of expression with a unary operator */
    /* Get operator from symbol table */
    FunSymbol * op_sym = get_symbol_lexical_scope(symbol_table, operator);
    if (op_sym == NULL) {
        fprintf(stderr, "Operator `%s` not defined.", operator);
    }
    /* Check types. This implementation is very rudimentary. */
    /* Note that the C standard allows us to access the type field using
     * binaryExpr even if the node is a binaryExpr */
    if ((op_sym->args->next != NULL) || ! (child->op.unaryExpr.type == get_symbol_lexical_scope(op_sym->symbol_table, op_sym->args->name))) {
        fprintf(stderr, "Type of operator `%s` does not match types of arguments.", operator);
    }
    return add_unary_expr_node(operator, child, op_sym->type->op.fun.return_type);
}

Type * handle_base_type(BaseType base) {
    Type * type = malloc(sizeof(Type));
    type->tag = base;
    return type;
}

Type * handle_custom_type(char * type_name) {
    TypeSymbol * type_sym = get_symbol_lexical_scope(symbol_table, type_name);
    if (type_sym == NULL) {
        fprintf(stderr, "Type \"%s\" has not been defined.", type_name);
    }
    return type_sym->type;
}
