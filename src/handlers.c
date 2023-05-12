/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <stdio.h>
#include <string.h>

#include "symbol_table.h"
#include "syntax_tree.h"
#include "types.h"
#include "parser.h"

typedef struct TypeInfo {
    int num_args;
    int type_ids[16];
} TypeInfo;

Node * handle_var_declaration(Type * type, char * id, Node * init, int line_num) {
    Symbol * var = malloc(sizeof(Symbol));
    var->tag = var_symbol_type;
    var->op.var.name = id;
    var->op.var.type = type;
    var->op.var.declared_at = line_num;
    if (set_symbol(symbol_table, id, var)) {
        yyerror(NULL, "Redeclaration of variable \"%s\" on line %d. \"%s\" already defined on line %d.",
                id, line_num, id, ((Symbol *)get_symbol_lexical_scope(symbol_table, id))->op.var.declared_at);
    }
    return add_var_dec_node(id, type, var, init);
}

Node * handle_type_def(char * id, Type * type, int line_num) {
    Symbol * typevar = malloc(sizeof(Symbol));
    typevar->tag = type_symbol_type;
    typevar->op.var.name = id;
    typevar->op.var.type = type;
    typevar->op.var.declared_at = line_num;
    if (set_symbol(symbol_table, id, typevar)) {
        yyerror(NULL, "Redefinition of type \"%s\" on line %d. \"%s\" already defined on line %d.",
                id, line_num, id, ((Symbol *)get_symbol_lexical_scope(symbol_table, id))->op.var.declared_at);
    }
    return add_type_def_node(id, type, typevar);
}

Node * handle_array_declaration(Type * elem_type, char * id, char * size, Node * init, int line_num) {
    Symbol * var = malloc(sizeof(Symbol));
    Type * type = malloc(sizeof(Type));
    type->tag = array_type;
    type->op.array.elem_type = elem_type;
    type->op.array.size = (size_t)atoll(size);
    var->tag = var_symbol_type;
    var->op.var.name = id;
    var->op.var.type = type;
    var->op.var.declared_at = line_num;
    if (set_symbol(symbol_table, id, var)) {
        yyerror(NULL, "Redeclaration of variable \"%s\" on line %d. \"%s\" already defined on line %d.",
                id, line_num, id, ((Symbol *)get_symbol_lexical_scope(symbol_table, id))->op.var.declared_at);
    }
    return add_var_dec_node(id, type, var, init);
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

Node * handle_member_expr(Node * base, Node * child, int is_dot) {
    /** Member expressions require additional checking for validity.
      * This will also need checking in the second pass to ensure indexes are of type int */
    if (is_dot) {
        if ((base->tag == literal_node) || (child->tag == literal_node)) {
            yyerror(NULL, "Invalid membership syntax: Dot expression contained a literal.");
        }
        return add_binary_expr_node(".", base, child, child->op.binary_expr.type);
    }
    else {
        if (base->tag == literal_node) {
            yyerror(NULL, "Invalid membership syntax: Index expression contained a literal for the base.");
        }
        return add_binary_expr_node("[]", base, child, child->op.binary_expr.type);
    }
}

Node * handle_var(char * name) {
    /** Adds var_node. Note that the variable must already be in the symbol table. */
    Symbol * var_sym = get_symbol_lexical_scope(symbol_table, name);
    if (var_sym == NULL) {
        yyerror(NULL, "Variable \"%s\" not declared!", name);
        return NULL;
    }
    else {
        return add_var_node(name, var_sym->op.var.type, var_sym);
    }
}

Node * handle_literal(char * value, BaseType lit_type) {
    Type * type = malloc(sizeof(Type));
    type->tag = base_type;
    type->op.base = lit_type;
    return add_lit_node(value, type);
}

Type * handle_base_type(BaseType base) {
    Type * type = malloc(sizeof(Type));
    type->tag = base;
    return type;
}

Type * handle_ptr_type(Type * val_type) {
    Type * type = malloc(sizeof(Type));
    type->tag = ptr_type;
    type->op.ptr.val_type = val_type;
    return type;
}

Type * handle_custom_type(char * type_name) {
    Symbol * type_sym = get_symbol_lexical_scope(symbol_table, type_name);
    if (type_sym == NULL) {
        yyerror(NULL, "Type \"%s\" has not been defined.", type_name);
    }
    return type_sym->op.var.type;
}

Type * handle_fun_type(Args * type_list, Type * return_type) {
    Type * this_fun_type = malloc(sizeof(Type));
    this_fun_type->tag = fun_type;
    this_fun_type->op.fun.args = type_list;
    this_fun_type->op.fun.return_type = return_type;
    return this_fun_type;
}

/** \todo in second pass, we'll need to collect the arguments in higher scopes  */
Node * handle_function_def(char * name, Args * args, Type * return_type, SymbolTable * table, Node * block, int line_num) {
    /** Adds function and type info to symbol table */
    Symbol * fun = malloc(sizeof(Symbol));
    char * mangled_name;
    if (strcmp(name, "main")) {
        mangled_name = mangle_fun_name(name, args);
    }
    else {
        mangled_name = name;
    }
    fun->op.fun.name = mangled_name;
    fun->op.fun.type = return_type;
    fun->op.fun.symbol_table = table;
    
    Args * curr_arg = args;
    while (curr_arg) {
        Symbol * curr_var = malloc(sizeof(Symbol));
        curr_var->tag = var_symbol_type;
        curr_var->op.var.name = curr_arg->name;
        curr_var->op.var.type = curr_arg->type;
        curr_var->op.var.declared_at = line_num;
        set_symbol(table, curr_arg->name, curr_var);
        curr_arg = curr_arg->next;
    }
    fun->op.fun.args = args;
    fun->op.fun.declared_at = line_num;
    /** \todo add fun with mangled name to symbol table */
    return add_fun_def_node(mangled_name, args, return_type, table, block, fun, line_num);
}

/** \todo might need to add additional information (or a different symbol/node struct),
 *  for the purpose of parameter passing. This code is somewhat temporary
 */
Node * handle_cfun_dec(char * name, Args * args, Type * return_type, int line_num) {
    Symbol * fun = malloc(sizeof(Symbol));
    fun->op.fun.name = name;
    fun->op.fun.type = return_type;
    fun->op.fun.args = args;
    fun->op.fun.declared_at = line_num;
    /** \todo add fun to symbol table */
    return add_fun_def_node(name, args, return_type, NULL, NULL, fun, line_num);
}


/* Needs implementation */

Node * handle_function_call(char * fun_name, CallArgs * args, int line_num) {
    return add_fun_call_node(fun_name, args, NULL, line_num);
}


Node * handle_if(Node * test, Node * block, Node * next) {
    return add_if_node(test, block, next);
}

Node * handle_elif(Node * previous, Node * test, Node * block, Node * next) {
    Node * new = add_if_node(test, block, next);
    previous->op.if_statement.next = new;
    return new;
}

/* Might be able to incorporate into handle_while */
Node * handle_do(Node * test, Node * block) {
    return add_do_loop_node(test, block);
}

Node * handle_while(Node * test, Node * block) {
    return add_while_loop_node(test, block);
}

/* Needs a case for when init is a variable declaration to edit symbol table */
Node * handle_for(Node * init, Node * test, Node * inc, Node * block) {
    return add_for_loop_node(init, test, inc, block);
}

Node * handle_return(Node * expr) {
    return add_control_node(expr, return_tag);
}

Node * handle_break(void) {
    return add_control_node(NULL, break_tag);
}

Node * handle_continue(void) {
    return add_control_node(NULL, continue_tag);
}

Node * create_block_node(StatementBlock * block) {
    Node * new = malloc(sizeof(Node));
    new->tag = block_node;
    new->op.block = block;
    return new;
}

Node * handle_import(char * module, char * namespace, int line_num) {
    return add_import_node(module, namespace, line_num);
}
