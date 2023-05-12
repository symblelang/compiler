#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <stdio.h>

#include "code_gen.h"
#include "parser.h"
#include "syntax_tree.h"

int code_gen_pass(Node * ast, FILE * out_file) {
    (void)(out_file);
    LLVMModuleRef module = LLVMModuleCreateWithName("symble_module");
    LLVMBuilderRef builder = LLVMCreateBuilder();
    for(StatementBlock * block_pos = ast->op.block; block_pos != NULL; block_pos = block_pos->next) {
        Node * statement = block_pos->statement;
        code_gen_node(statement, module, builder);
    }

    /* Check that LLVM code was valid */
    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    LLVMDisposeMessage(error);
    LLVMDisposeBuilder(builder);
    return 0;
}

LLVMValueRef code_gen_node(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {
    switch(node->tag) {
        case var_dec_node:
            return code_gen_var_dec(node, module, builder);
            break;
        case type_def_node:
            break;
        case fun_def_node:
            break;
        case binary_expr_node:;
            return code_gen_binary_expr(node, module, builder);
        case unary_expr_node:
            break;
        case literal_node:
            break;
        case var_node:
            break;
        case while_loop_node:
            break;
        case do_loop_node:
            break;
        case for_loop_node:
            break;
        case control_node:
            break;
        case if_node:
            break;
        case fun_call_node:
            break;
        case block_node:
            break;
        case import_node:
            break;
        default:
            yyerror(node, "Unsupported node type. Ensure code_gen.c covers every node tag\n");
    }
    return NULL;
}

LLVMValueRef code_gen_binary_expr(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMValueRef left = code_gen_node(node->op.binary_expr.left, module, builder);
    LLVMValueRef right = code_gen_node(node->op.binary_expr.right, module, builder);
    switch (node->op.binary_expr.op_symbol->op.fun.builtin) {
        case non_builtin:;
            /** \todo Actually call function for operator */
            LLVMValueRef fun = LLVMGetNamedFunction(module, node->op.binary_expr.op_symbol->op.fun.name);
            return fun; /**< \todo implement the actual call  */
        case builtin_add_ints:
            return LLVMBuildAdd(builder, left, right, "add_tmp");
        case builtin_sub_ints:
            return LLVMBuildSub(builder, left, right, "sub_tmp");
        case builtin_mult_ints:
            return LLVMBuildMul(builder, left, right, "mult_tmp");
        case builtin_div_ints:
            return LLVMBuildSDiv(builder, left, right, "div_tmp");
        case builtin_mod_ints:
            return LLVMBuildSRem(builder, left, right, "mod_tmp");
        case builtin_pow_ints:
            yyerror(node, "Power operation for integers not yet implemented\n");
        case builtin_bin_and:
            return LLVMBuildAnd(builder, left, right, "bin_and_tmp");
        case builtin_bin_or:
            return LLVMBuildOr(builder, left, right, "bin_or_tmp");
        case builtin_bin_xor:
            return LLVMBuildXor(builder, left, right, "bin_xor_tmp");
        case builtin_equal_ints:
            return LLVMBuildICmp(builder, LLVMIntEQ, left, right, "eq_tmp");
        case builtin_less_ints:
            return LLVMBuildICmp(builder, LLVMIntSLT, left, right, "bin_xor_tmp");
        case builtin_greater_ints:
            return LLVMBuildICmp(builder, LLVMIntSGT, left, right, "bin_xor_tmp");
        case builtin_leq_ints:
            return LLVMBuildICmp(builder, LLVMIntSLE, left, right, "bin_xor_tmp");
        case builtin_geq_ints:
            return LLVMBuildICmp(builder, LLVMIntSGE, left, right, "bin_xor_tmp");
        case builtin_neq_ints:
            return LLVMBuildICmp(builder, LLVMIntEQ, LLVMBuildICmp(builder, LLVMIntEQ, left, right, "eq_tmp"), LLVMConstNull(LLVMInt1Type()), "eq_tmp");
        default:
            yyerror(node, "Unsupported operator type. Ensure code_gen.c covers all builtin binary operators\n");
            return left;
    }
}

named_value *named_values = NULL;

LLVMValueRef code_gen_var_dec(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {
    named_value *val = NULL;
    // TODO Add to symbol table
    /* Naive Implementation
     * If new scope, create new symbol table
     *     SymbolTable *table = new_symbol_table(size?); this calls malloc via hashtable.c
     *     push_symbol_table();
     *     set_symbol(table, key?, Node->name);
     *     push_symbol_table();
     * If existing scope, get current symbol table (How do we want to pass this in?) 
     *     get current symbol table (How do we want to pass this in?)
     *     set_symbol(table, key?, Node);
     *    
     */
    if(val != NULL) {
        return val -> value;
    } else {
        return NULL;
    }
}
