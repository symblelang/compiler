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

#include <stdint.h>

#include "symbol_table.h"

typedef struct Type Type;
typedef struct ArgTypes ArgTypes;

/* TODO: add list/array  */

struct ArgTypes {
    Type * type;
    ArgTypes * next;
};

typedef enum BaseType {
    int_type,
    str_type,
    float_type
} BaseType;

struct Type {
    enum {base_type, fun_type, array_type} tag;
    union {
        BaseType base;
        struct {
            Type * return_type;
            ArgTypes * args;
        } fun;
        struct {
            Type * base_type;
            size_t size;
        } array;
    } op;
};

int check_types_equal(Type * type_1, Type * type_2);
char * mangle_fun_name(char * fun_name, const ArgTypes * const arg_types);

#endif
