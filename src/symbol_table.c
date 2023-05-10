/*
 * Author: Caden Parajuli - caden.parajuli@bc.edu
 */

#include "hash_table.h"
#include "symbol_table.h"

extern SymbolTable * symbol_table;

SymbolTable * new_symbol_table(size_t size) {
    SymbolTable * new_table = malloc(sizeof(SymbolTable));
    new_table->hash_table = new_hash_table(size);
    new_table->next = NULL;
    return new_table;
}

void free_symbol_table(SymbolTable * table) {
    if (table) {
        free_hash_table(table->hash_table);
        table->next = NULL;
        free(table);
    }
}

SymbolTable * push_symbol_table() {
    SymbolTable * new_table = new_symbol_table(HASH_TABLE_DEFAULT_SIZE);
    new_table->next = symbol_table;
    return symbol_table = new_table;
}

void pop_symbol_table() {
    if (symbol_table) {
        symbol_table = symbol_table->next;
    }
}

void * get_symbol_current_table(SymbolTable * table, const char * key) {
    /** Get symbol in current table only. Returns NULL if key is not found */
    return get_entry(table->hash_table, key);
}

void * get_symbol_lexical_scope(SymbolTable * table, const char * key) {
    /** Get symbol in any scope accessible using lexical scoping rules. Returns NULL if key is not found */
    SymbolTable * scope = table;
    while (scope) {
        void * potential = get_entry(scope->hash_table, key);
        if (potential) {
            return potential;
        }
        scope = scope->next;
    }
    return NULL;
}

/* TODO implement name mangling for this */
/* void * get_fun_with_type(SymbolTable * table, const char * key, Args * args_types) { */
/* } */


int set_symbol(SymbolTable * table, const char * key, void * value) {
    return set_entry(table->hash_table, key, value);
}

int unset_symbol(SymbolTable * table, const char * key) {
    return unset_entry(table->hash_table, key);
}

