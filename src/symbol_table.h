/*
 * Author: Amittai Aviram - aviram@bc.edu
 */
#pragma once

#include "hash_table.h"

#define LEXEME_SIZE 256
#define SYMBOL_SIZE 8

typedef enum IdentifierType { NONE, VAR, FUNC, PROC } IdentifierType;

typedef struct SymbolTable {
    char name[LEXEME_SIZE];
    struct HashTable * hash_table;
    int reg_no;
    int mem_no;
    int param_no;
    int unit_started;
    struct SymbolTable * next;
} SymbolTable;

typedef struct IdentifierEntry {
    IdentifierType id_type;
    char lexeme[LEXEME_SIZE];
    char symbol[SYMBOL_SIZE];
    int type_id;
    int base_type_id;
    int line_num;
} IdentifierEntry;

typedef struct NumberEntry {
    char lexeme[LEXEME_SIZE];
    int type;
    long value;
} NumberEntry;

SymbolTable * new_symbol_table();
void delete_symbol_table(SymbolTable * this);
void push_symbol_table();
void pop_symbol_table();
void * symbol_table_get(SymbolTable * this, const char * const key);
void * symbol_table_put(SymbolTable * this, const char * const key, void * value);
IdentifierEntry * new_identifier_entry(
        const char * const lexeme, const int type_id, const int base_type_id, const int line_num
        );
NumberEntry * new_number_entry(const char * const lexeme, const int type_id);

