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
#include <llvm-c/Core.h>

#include "symbol_table.h"

typedef struct Type Type;
typedef struct Args Args;

typedef enum BaseType {
    int_type,
    str_type,
    float_type,
    void_type
} BaseType;

struct Type {
    enum {base_type, fun_type, array_type, ptr_type} tag;
    union {
        BaseType base;
        struct {
            Type * return_type;
            Args * args;
        } fun;
        struct {
            Type * elem_type;
            size_t size;
        } array;
        struct {
            Type * val_type;
        } ptr;
    } op;
};

/** \todo Add tests for all of these functions */
int check_types_equal(Type * type_1, Type * type_2);
char * mangle_fun_name(const char * const fun_name, const Args * const arg_types);
char * mangle_unary_op(const char * const op_name, const Type * const type);
char * mangle_binary_op(const char * const op_name, const Type * const type1, const Type * const type2);
LLVMTypeRef get_llvm_type(Type * type);

#endif
