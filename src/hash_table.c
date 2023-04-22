/*
 * Author: Amittai Aviram - aviram@bc.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static int primes[] = PRIMES;

HashTable * new_hash_table() {
    HashTable * table = malloc(sizeof(HashTable));
    srand(1);
    table->scale = arc4random_uniform(PRIME - 1) + 1;
    table->shift = arc4random_uniform(PRIME);
    table->capacity = INITIAL_CAPACITY;
    table->table = calloc(table->capacity, sizeof(Entry *));
    table->size = 0;
    table->load_factor = 0.0;
    return table;
}

void delete_hash_table(HashTable * this) {
    for (int i = 0; i < this->capacity; ++i) {
        if (this->table[i]) {
            Entry * entry = this->table[i];
            Entry * previous = NULL;
            while (entry) {
                previous = entry;
                entry = entry->next;
                previous->next = NULL;
                free(previous);
            }
            this->table[i] = NULL;
        }
    }
    free(this->table);
    free(this);
}

void * hash_table_put(HashTable * this, const char * const key, void * const value) {
    int index = hash_table_find_index(this, key);
    if (!this->table[index]) {
        this->table[index] = hash_table_new_entry(key, value);
    } else {
        Entry * entry = this->table[index];
        Entry * previous = NULL;
        while (entry) {
            if (!strcmp(entry->key, key)) {
                char * old_value = entry->value;
                entry->value = value;
                return old_value;
            }
            previous = entry;
            entry = entry->next;
        }
        previous->next = hash_table_new_entry(key, value);
    }
    ++this->size;
    this->load_factor = (double) this->size / (double) this->capacity;
    if (this->load_factor > MAX_LOAD_FACTOR) {
        hash_table_resize_table(this, UP);
    }
    return NULL;
}

void * hash_table_get(HashTable * this, const char * const key) {
    Entry * entry = hash_table_get_entry(this, key, NULL, NULL);
    if (entry) {
        return entry->value;
    }
    return NULL;
}

void * hash_table_remove(HashTable * this, const char * const key) {
    Entry * previous = NULL;
    int index;
    Entry * entry = hash_table_get_entry(this, key, &previous, &index);
    if (!entry) {
        return NULL;
    }
    if (previous) {
        previous->next = entry->next;
    } else {
        this->table[index] = NULL;
    }
    void * answer = entry->value;
    entry->next = NULL;
    free(entry);
    --this->size;
    this->load_factor = (double) this->size / (double) this->capacity;
    if (this->load_factor < MIN_LOAD_FACTOR) {
        hash_table_resize_table(this, DOWN);
    }
    return answer;
}

Entry * hash_table_get_entry(HashTable * this, const char * const key, Entry ** pred, int * idx) {
    if (hash_table_is_empty(this)) {
        return NULL;
    }
    int index = hash_table_find_index(this, key);
    if (idx) {
        *idx = index;
    }
    if (!this->table[index]) {
        return NULL;
    }
    Entry * entry = this->table[index];
    while (entry) {
        if (!strcmp(entry->key, key)) {
            return entry;
        }
        if (pred) {
            *pred = entry;
        }
        entry = entry->next;
    }
    return NULL;
}

int hash_table_is_empty(HashTable * this) {
    return this->size == 0;
}

Entry * hash_table_new_entry(const char * const key, void * const value) {
    Entry * entry = malloc(sizeof(Entry));
    if (!entry) {
        perror("New Entry");
        exit(EXIT_FAILURE);
    }
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

int hash_table_hash_code(const char * const key) {
    const char * key_addr = key;
    int code = 0;
    while (*key_addr) {
        code += (int)*key_addr++;
    }
    return code;
}

int hash_table_find_index(HashTable * this, const char * const key) {
    return (abs((int)hash_table_hash_code(key) * this->scale + this->shift) % PRIME) % this->capacity;
}

void hash_table_copy_into_table(HashTable * this, Entry * old_entry, Entry ** new_table) {
    int index = hash_table_find_index(this, old_entry->key);
    if (!new_table[index]) {
        new_table[index] = old_entry;
        old_entry->next = NULL;
    } else {
        Entry * entry = new_table[index];
        while (entry->next) {
            entry = entry->next;
        }
        entry->next = old_entry;
        ++this->size;
        this->load_factor = (double) this->size / (double) this->capacity;
    }
}

void hash_table_resize_table(HashTable * this, Direction direction) {
    int new_capacity = this->capacity;
    if (direction == UP) {
        new_capacity *= 2;
    } else if (this->capacity > 2) {
        new_capacity /= 2;
    }
    int prime_index = 0;
    int primes_size = sizeof(primes) / sizeof(primes[0]);
    while (prime_index < primes_size && primes[prime_index] <= new_capacity) {
        ++prime_index;
    }
    new_capacity = primes[prime_index];
    Entry ** new_table = calloc(new_capacity, sizeof(Entry *));
    int old_capacity = this->capacity;
    this->capacity = new_capacity;
    this->size = 0;
    for (int i = 0; i < old_capacity; ++i) {
        if (this->table[i]) {
            Entry * entry = this->table[i];
            while (entry) {
                hash_table_copy_into_table(this, entry, new_table);
                entry = entry->next;
            }
        }
    }
    free(this->table);
    this->table = new_table;
}

