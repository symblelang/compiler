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

typedef struct TypeInfo {
    int num_args;
    int type_ids[16];
} TypeInfo;

Node * handle_variable_declaration(Type * type, char * id, Node * init, int line_num) {
    VarSymbol * var = malloc(sizeof(VarSymbol));
    var->name = id;
    var->type = type;
    var->declared_at = line_num;
    if (set_symbol(symbol_table, id, var)) {
        yyerror("Redeclaration of variable \"%s\" on line %d. \"%s\" already defined on line %d.",
                id, line_num, id, ((VarSymbol *)get_symbol_lexical_scope(symbol_table, id))->declared_at);
    }
    return add_var_dec_node(var->name, var->type, init);
}


/* Type checking should be done in a second pass over the syntax tree, since
 * operators and functions may not be in the symbol table until the end of the first pass */
Node * handle_binary_expr(Node * left, char * operator, Node * right) {
    /** Handles any kind of expression with a binary operator */
    return add_binary_expr_node(operator, left, right, NULL);
}

Node * handle_unary_expr(char * operator, Node * child) {
    /** Handles any kind of expression with a unary operator */
    return add_unary_expr_node(operator, child, NULL);
}

Node * handle_member_expr(char * member_expr, char * child_member, Node * child) {
   /** Accesses primary class to access index of array, or call function of a class*/ 
}

Node * handle_function_def(char * function_name, char ** args) {
    /* Add function type info to symbol table */
}

Node * handle_function_call(char * function_name, char ** args) {
    /* Check that provided arguments match function definition*/
    /* Print "call " + <function_name> */
}

int check_param_types(char * function_name, char ** args) {
    /* Query symbol table for correct types in original function definition */
    /* Check if correct number of arguments was provided */
    /* Check for type mismatch in provided arguments vs. defined arguments */
    /* Return 0 if correct number of arguments and correct types provided */
    /* Return 1 and or throw error if incorrect number of arguments or incorrect types provided */
}

Type * handle_base_type(BaseType base) {
    Type * type = malloc(sizeof(Type));
    type->tag = base;
    return type;
}

Type * handle_custom_type(char * type_name) {
    TypeSymbol * type_sym = get_symbol_lexical_scope(symbol_table, type_name);
    if (type_sym == NULL) {
        yyerror("Type \"%s\" has not been defined.", type_name);
    }
    return type_sym->type;
}

ArgTypes * create_type_list(Type * type) {
    ArgTypes * type_list = malloc(sizeof(ArgTypes));
    type_list->type = type;
    return type_list;
}

/* This implementation is hilariously inefficient, but nobody should be writing
 * functions with hundreds of arguments */
ArgTypes * add_to_type_list(ArgTypes * type_list, Type * type) {
    ArgTypes * where_to_add = type_list;
    while (where_to_add->next != NULL) {
        where_to_add = where_to_add->next;
    }
    where_to_add->next = malloc(sizeof(ArgTypes));
    where_to_add->next->type = type;
    return type_list;
}

Type * handle_fun_type(ArgTypes * type_list, Type * return_type) {
    Type * this_fun_type = malloc(sizeof(Type));
    this_fun_type->tag = fun_type;
    this_fun_type->op.fun.args = type_list;
    this_fun_type->op.fun.return_type = return_type;
    return this_fun_type;
}
