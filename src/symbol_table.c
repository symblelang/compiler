/*
 * Author: Caden Parajuli - caden.parajuli@bc.edu
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

static size_t max_psl;

static uint64_t fnv_hash_64(const char * key) {
    uint64_t hash = FNV_BASIS_64;
    for (const uint8_t * curr_loc = (const unsigned char *)key; *curr_loc; curr_loc++) {
        hash ^= *curr_loc;
        hash *= FNV_PRIME_64;
    }
    return hash;
}

SymbolTable * new_table() {
    /* Allocate table space */
    SymbolTable * table = malloc(sizeof(SymbolTable));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    /* Allocate entry space */
    table->entries = calloc(table->capacity, sizeof(TableEntry *));
    if (*table->entries == NULL) {
        free(table); // error, free table before we return!
        return NULL;
    }
    return table;
}

void free_table(SymbolTable * table) {
    /* Free entry keys */
    for (size_t i = 0; i < table->capacity; i++) {
        free((void *)table->entries[i].key);
    }
    /* Free entries and table */
    free(table->entries);
    free(table);
}

void * get_symbol(SymbolTable * table, const char * key) {
    /* Returns NULL if key is not in table */
    uint64_t hash = fnv_hash_64(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));
    size_t psl = 0;

    /* Loop until there's an empty entry or max_psl times, whichever comes sooner */
    while (table->entries[index].key != NULL) {
        if (psl > max_psl) {
            return NULL;
        }
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }
        /* Wrong key, probe */
        psl++;
        index++;
        if (index >= table->capacity) {
            /* Wrap */
            index = 0;
        }
    }
    return NULL;
}

int set_symbol(SymbolTable * table, const char * key, void * value) {
    /* Returns nonzero on error */
    uint64_t hash = fnv_hash_64(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));
    size_t psl = 0;
    
    /* Check if resize is required */
     if (table->length >= table->capacity / 2) {
        if (expand_table(table)) {
            return 1;
        }
    }
     
    /* Loop until there's an empty entry */
    while (table->entries[index].key != NULL) {
        if (psl > max_psl) {
            /* Update max_psl */
            max_psl = psl;
        }
        if (strcmp(key, table->entries[index].key) == 0) {
            /* Key found, update value. */
            table->entries[index].value = value;
            return 0;
        }
        if (psl > table->entries[index].psl) {
            /* Robin Hood swap */
            char * temp_key = (char *)table->entries[index].key;
            void * temp_value = table->entries[index].value;
            size_t temp_psl = table->entries[index].psl;
            table->entries[index].key = strdup(key);
            table->entries[index].value = value;
            table->entries[index].psl = psl;
            key = temp_key;
            value = temp_value;
            psl = temp_psl;
        }
        /* Index is taken, probe */
        psl++;
        index++;
        if (index >= table->capacity) {
            /* Wrap */
            index = 0;
        }
    }
    
    /* Set empty entry */
    table->entries[index].key = key;
    table->entries[index].value = value;
    table->entries[index].psl = psl;
    table->length++;
    return 0;
}

int expand_table(SymbolTable * table) {
    return 0;
}