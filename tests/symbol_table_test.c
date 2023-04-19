#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "symbol_table.h"

#define INITIAL 128
#define TEST_KEY_SIZE 20
#define TEST_VAL_SIZE 20
#define NUM_ELEMENTS 130

static void rand_string(char * str, size_t size)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
}

/* ERROR TODO Currently something is creating null values */
int main() {
    SymbolTable * table = new_table(INITIAL);
    char test_key[TEST_KEY_SIZE];
    char test_val[TEST_VAL_SIZE];
    char * key_array[NUM_ELEMENTS];
    char * val_array[NUM_ELEMENTS];
    srand(time(0));
    printf("Setting...\n");
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        rand_string(test_key, rand() % (TEST_KEY_SIZE - 2) + 2);
        while (get_symbol(table, test_key) != NULL) {
            rand_string(test_key, rand() % (TEST_KEY_SIZE - 2) + 2);
        }
        rand_string(test_val, rand() % (TEST_VAL_SIZE - 2) + 2);
        key_array[i] = strdup(test_key);
        val_array[i] = strdup(test_val);
        if (set_symbol(table, test_key, val_array[i]) || get_symbol(table, test_key) == NULL) {
            fprintf(stderr, "failure setting table[%s] = %s\n", test_key, test_val);
        }
        /* printf("table[%s] = %s\n", test_key, test_val); */
    }
    printf("Checking...\n\n");
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        char * gotten = get_symbol(table, key_array[i]);
        if (gotten != val_array[i]) {
            fprintf(stderr, "ERROR!\ntable[%s] = %s\n Should be: %s\n", key_array[i], gotten, val_array[i]);
        }
        free(key_array[i]);
        free(val_array[i]);
    }
    printf("Done!\n");
    free_table(table);
}