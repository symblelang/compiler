/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <stdint.h>
#include <string.h>

#include "types.h"

/* Forward declarations for internal functions */
size_t mangle_type_len(const Type * const type);
size_t mangle_args_len(const Args * const arg_types);
char * mangle_type(const Type * const type, char * pos);
char * mangle_fun_name(char * fun_name, const Args * const arg_types);

int check_types_equal(Type * type_1, Type * type_2) {
    if (! (type_1->tag == type_2->tag)) {
        return 0;
    }
    switch (type_1->tag) {
        case base_type:
            return type_1->op.base == type_2->op.base;
        case fun_type:
            if (type_2->tag != fun_type) {
                return 0;
            }
            Args * curr_arg_1 = type_1->op.fun.args;
            Args * curr_arg_2 = type_2->op.fun.args;;
            while (curr_arg_1) {
                if (! (check_types_equal(curr_arg_1->type, curr_arg_2->type))) {
                    return 0;
                }
                curr_arg_1 = curr_arg_1->next;
                curr_arg_2 = curr_arg_2->next;
            }
            return type_1->op.fun.return_type == type_2->op.fun.return_type;
        case array_type:
            if (type_2->tag != array_type) {
                return 0;
            }
            return check_types_equal(type_1->op.array.elem_type, type_2->op.array.elem_type);
        case ptr_type:
            if (type_2->tag != ptr_type) {
                return 0;
            }
            /** Returns 1 if one of the pointers is a void type */
            if ((type_1->op.ptr.val_type->tag == base_type) && (type_2->op.ptr.val_type->tag == base_type)) {
                BaseType elem_base_1 = type_1->op.ptr.val_type->tag;
                BaseType elem_base_2 = type_2->op.ptr.val_type->tag;
                if ((elem_base_1 == elem_base_2) || (elem_base_1 == void_type) || (elem_base_2 == void_type)) {
                    return 1;
                }
            }
            return check_types_equal(type_1->op.ptr.val_type, type_2->op.ptr.val_type);
        default:
            return 0;
    }
}

size_t mangle_type_len(const Type * const type) {
    /** Get the length a type would be if mangled. helper function for mangle_fun_name */
    size_t len = 0;
    switch (type->tag) {
        case base_type:
            len += 1;
            break;
        case array_type:
            len += 2;
            len += mangle_type_len(type->op.array.elem_type);
            /* number of bytes needed to represent the length */
            len += (size_t)(63 - __builtin_clzll((uint64_t)type->op.array.size)) >> 3;
            break;
        case ptr_type:
            len += 1;
            len += mangle_type_len(type->op.ptr.val_type);
            break;
        case fun_type:
            len += 3; /* f-> */
            len += mangle_args_len(type->op.fun.args);
            len += mangle_type_len(type->op.fun.return_type);
            break;
    }
    return len;
}

size_t mangle_args_len(const Args * const arg_types) {
    size_t len = 0;
    const Args * curr_arg = (const Args *)arg_types;
    while (curr_arg) {
        len += mangle_type_len(curr_arg->type);
        curr_arg = curr_arg->next;
    }
    return len;
}

char * mangle_type(const Type * const type, char * pos) {
    /** Adds type to mangled name in-place at pos, and returns pointer to null-terminator */
    switch (type->tag) {
        case base_type:
            switch (type->op.base) {
                case int_type:
                    *pos = 'i';
                    break;
                case str_type:
                    *pos = 's';
                    break;
                case float_type:
                    *pos = 'f';
                    break;
                default:
                    /* If this shows up in mangled names, there's a type issue */
                    *pos = 'x';
                    break;
            }
            pos[1] = '\0';
            return pos + 1;
        case array_type:
            pos = mangle_type(type->op.array.elem_type, pos);
            pos[0] = '[';
            /* Convert to base-256. Currently this could cause issues with null termination
             * if size is a multiple of 256 */
            for (uint64_t shifted = type->op.array.size; shifted; shifted >>= 7) {
                *(++pos) = (shifted & 1111111) + 1;
            }
            *(++pos) = '\0';
            return pos;
        case ptr_type:
            pos = mangle_type(type->op.array.elem_type, pos);
            *(pos++) = 'p';
            return pos;

        case fun_type:
            *(pos++) = 'f';
            Args * arg = type->op.fun.args;
            while (arg) {
                pos = mangle_type(arg->type, pos);
                arg = arg->next;
            }
            *(++pos) = '-';
            *(++pos) = '>';
            *(++pos) = '\0';
            return pos;
    }
}

char * mangle_fun_name(char * fun_name, const Args * const args) {
    /** Mangles the name of a function with given argument types. Note that the return
      * value is malloc'd, but after syntax tree gen, the original name is not needed.
      * Mangling example:
      *     fun name(ptr string x, int a[266], int y, fun (int) -> void) -> string
      *     turns into:
      *         name_psi['10''3']fi->v
      *         where 'a' is the character with ascii code a.
      *         The characters are computed by converting the size to base 128,
      *         adding 1 to each character (to prevent null-termination issues),
      *         and ordering bytes in big-endian order
      */
    size_t name_len = strlen(fun_name);
    size_t mangled_len = name_len + 1 + mangle_args_len(args);
    char * mangled_name = malloc(mangled_len + 1);
    char * pos = mangled_name + name_len;
    Args * arg = (Args *)args;

    memcpy(mangled_name, fun_name, name_len + 1);
    
    while (arg) {
        pos = mangle_type(arg->type, pos);
        arg = arg->next;
    }
    return mangled_name;
}
