/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include "types.h"

int check_types_equal(Type * type_1, Type * type_2) {
    if (! (type_1->tag == type_2->tag)) {
        return 0;
    }
    Args * curr_arg;
    switch (type_1->tag) {
        case base_type:
            return type_1->op.base == type_2->op.base;
        case fun_type:
            curr_arg = type_1->op.fun.args;
            while (curr_arg) {
                if (! (check_types_equal(type_1, type_2))) {
                    return 0;
                }
                curr_arg = curr_arg->next;
            }
        default:
            return 0;
    }
}
