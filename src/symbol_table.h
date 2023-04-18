/*
 * Author: Caden Parajuli - caden.parajuli@bc.edu
 */

/* Header guards */
#ifndef FNV_HASH_H
#define FNV_HASH_H

#define FNV_PRIME_64 0x100000001B3
#define FNV_BASIS_64 0xCBF29CE484222325
#define INITIAL_CAPACITY 128

#include <stdint.h>
#include <stdlib.h>

typedef struct TableEntry {
    const char * key;
    void * value;
    uint64_t hash;
    size_t psl;
} TableEntry;

typedef struct SymbolTable {
    TableEntry * entries;
    size_t capacity;
    size_t length;
} SymbolTable;

SymbolTable * new_table();
void free_table(SymbolTable * table);
void * get_symbol(SymbolTable * table, const char * key);
int set_symbol(SymbolTable * table, const char * key, void * value);
int expand_table(SymbolTable * table);

#endif