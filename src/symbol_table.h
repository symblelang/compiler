/*
 * Author: Caden Parajuli - caden.parajuli@bc.edu
 */

/* Header guards */
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>

#include "types.h"
#include "hash_table.h"

/* Forward typedef to resolve cyclic header inclusions */
typedef struct Type Type;

typedef struct Args Args;
typedef struct SymbolTable SymbolTable;
typedef struct TableEntry TableEntry;
typedef struct VarSymbol VarSymbol;
typedef struct TypeSymbol TypeSymbol;
typedef struct FunSymbol FunSymbol;
typedef struct Symbol Symbol;

typedef enum {
    var_symbol_type,
    type_symbol_type,
    fun_symbol_type,
    op_symbol_type
} SymbolType;

typedef enum {
    non_builtin = 0,  /**< Used for user-defined operations */
    builtin_add_ints,
    builtin_sub_ints,
    builtin_mult_ints,
    builtin_div_ints,
    builtin_mod_ints,
    builtin_pow_ints,
    builtin_neg_int,
    builtin_bin_not,
    builtin_bin_and,
    builtin_bin_or,
    builtin_bin_xor,
    builtin_equal_ints,
    builtin_less_ints,
    builtin_greater_ints,
    builtin_leq_ints,
    builtin_geq_ints,
    builtin_neq_ints
} BuiltinOp;


struct SymbolTable {
    HashTable * hash_table;
    SymbolTable * next;
};

/** \todo Put symbols in a tagged union. This is important for a few reasons:
 *  1. We can tell var/type or fun/op apart if necessary
 *  2. Certain nodes (especially var_node) could point to either a var or a fun
 */

/** Used to store variables and types */
struct VarSymbol {
    char * name;
    Type * type;
    int declared_at;
};

/** Used to store functions and operators */
struct FunSymbol {
    char * name;
    Type * type;
    SymbolTable * symbol_table;
    Args * args;
    int closure; /**< closure is -1 if not closure, 0 if not determined yet, 1 if is closure. Not sure if necessary */
    int declared_at;
    BuiltinOp builtin; /**< \todo compute in second pass */
};

struct Symbol {
    SymbolType tag;
    union {
        VarSymbol var;
        FunSymbol fun;
    } op;
};

/** Stores the name and type of arguments to a function
 * name should be a key for the symbol table of the fun/op
 * If Args is used in the type specifier of a function, name should be NULL
 * If Args is used in a function call, type could be NULL
 */
struct Args {
    Type * type;
    Args * next;
    char * name;
};

SymbolTable * new_symbol_table(size_t size);
void free_table(SymbolTable * table);
SymbolTable * push_symbol_table(void);
void pop_symbol_table(void);

/** Returns NULL if key is not found in current table */
void * get_symbol_current_table(SymbolTable * table, const char * key);

/** Returns NULL if key is not found in scope */
void * get_symbol_lexical_scope(SymbolTable * table, const char * key);

int set_symbol(SymbolTable * table, const char * key, void * value);
int unset_symbol(SymbolTable * table, const char * key);

#endif
