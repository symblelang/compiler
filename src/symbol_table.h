/*
 * Author: Caden Parajuli - caden.parajuli@bc.edu
 */

/* Header guards */
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>

#include "hash_table.h"

typedef char * Type;
typedef struct SymbolTable SymbolTable;
typedef struct TableEntry TableEntry;
typedef struct VarSymbol VarSymbol;
typedef struct OpSymbol OpSymbol;
typedef struct FunSymbol FunSymbol;
typedef struct Argument Argument;

struct SymbolTable {
    HashTable * hash_table;
    SymbolTable * next;
};

struct VarSymbol {
    char * name;
    Type type;
    int declared_at;
};

struct OpSymbol {
    char * name;
    SymbolTable * symbol_table;
    Type return_type;
    Argument * args;
    int declared_at;
};

struct FunSymbol {
    char * name;
    SymbolTable * symbol_table;
    Type return_type;
    Argument * args;
    int declared_at;
};

struct Argument {
    /* Note that arg_name should be a key for the symbol table of the fun/op */
    char * arg_name;
    Argument * next;
};

SymbolTable * new_symbol_table(size_t size);
void free_table(SymbolTable * table);
void * get_symbol(SymbolTable * table, const char * key);
int set_symbol(SymbolTable * table, const char * key, void * value);
int unset_symbol(SymbolTable * table, const char * key);

#endif
