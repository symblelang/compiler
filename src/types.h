/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

/* Header guards */
#ifndef TYPES_H
#define TYPES_H

#include "symbol_table.h"

typedef struct Type Type;
typedef struct Args Args;

/* TODO: add list/array  */

struct Args {
    /* name should be a key for the symbol table of the fun/op */
    char * name;
    Args * next;
};

typedef enum BaseType {
    int_type,
    str_type,
    float_type
} BaseType;

struct Type {
    enum {base_type, fun_type} tag;
    union {
        BaseType base;
        struct {
            Type * return_type;
            Args * args;
        } fun;
    } op;
};

int check_types_equal(Type * type_1, Type * type_2);
Type * match_base_type(char * str);

#endif
