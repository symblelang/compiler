/*
 * Author: Amittai Aviram - aviram@bc.edu
 */
#pragma once

#define INITIAL_CAPACITY 17
#define MAX_LOAD_FACTOR 0.7
#define MIN_LOAD_FACTOR 0.2
#define PRIME 109345121
#define KEY_SIZE 64
#define PRIMES { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, \
    31, 37, 41, 43, 47, 53, 59, 61, 67, 71, \
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, \
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173, \
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229, \
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281, \
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349, \
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409, \
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463, \
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541, \
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601, \
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659, \
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733, \
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809, \
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863, \
    877, 881, 883, 887, 907, 911, 919, 929, 937, 941, \
    947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, \
    1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, \
    1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, \
    1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223 }

typedef struct Entry {
    char key[KEY_SIZE];
    void * value;
    struct Entry * next;
} Entry;

typedef struct HashTable {
    Entry ** table;
    int scale;
    int shift;
    int capacity;
    int size;
    double load_factor;
} HashTable;

typedef enum Direction { UP, DOWN } Direction;

// PUBLIC INTERFACE
HashTable * new_hash_table();
void delete_hash_table(HashTable * this);
void * hash_table_get(HashTable * this, const char * const key);
void * hash_table_put(HashTable * this, const char * const key, void * const value);
void * hash_table_remove(HashTable * this, const char * const key);

// PRIVATE FUNCTIONS
Entry * hash_table_get_entry(HashTable * this, const char * const key, Entry ** pred, int * idx);
Entry * hash_table_new_entry(const char * const key, void * const value);
int hash_table_hash_code(const char * const key);
int hash_table_find_index(HashTable * this, const char * const key);
int hash_table_is_empty(HashTable * this);
void hash_table_copy_into_table(HashTable * this, Entry * old_entry, Entry ** new_table);
void hash_table_resize_table(HashTable * this, Direction direction);
