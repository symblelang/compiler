/*
 * Authors:
 *   Andrew Clark     - andrew.clark.6@bc.edu
 *   Alex Liu         - alex.liu@bc.edu
 *   Caden Parajuli   - caden.parajuli@bc.edu
 *   Micheal Lebreck  - michael.lebreck@bc.edu
 *   William Morrison - william.morrison.2@bc.edu
 */

#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>

#include <stdio.h>

#include "code_gen.h"
#include "parser.h"
#include "syntax_tree.h"
#include "types.h"

named_value * named_values = NULL;

LLVMValueRef code_gen_var_dec(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {
    return LLVMBuildAlloca(builder, get_llvm_type(node->op.var_dec.type), node->op.var_dec.name);
}

int code_gen_pass(Node * ast, char * in_filename, char * out_filename) {
    LLVMModuleRef module = LLVMModuleCreateWithName(in_filename);
    LLVMBuilderRef builder = LLVMCreateBuilder();
    for (StatementBlock * block_pos = ast->op.block; block_pos != NULL; block_pos = block_pos->next) {
        Node * statement = block_pos->statement;
        code_gen_node(statement, module, builder);
    }

    /* Check that LLVM code was valid */
    char * error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);
    if (*error) {
        fprintf(stderr, "LLVM error: %s\n", error);
    }
    LLVMDisposeMessage(error);
    LLVMDisposeBuilder(builder);
    
    
    /* Initialize target */
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmParser();
    LLVMInitializeNativeAsmPrinter();
    LLVMTargetRef target = LLVMGetFirstTarget();
    LLVMTargetMachineRef target_machine = LLVMCreateTargetMachine(target,
                                                                  LLVMGetDefaultTargetTriple(), LLVMGetHostCPUName(), LLVMGetHostCPUFeatures(),
                                                                  LLVMCodeGenLevelNone , LLVMRelocDefault, LLVMCodeModelDefault);
    

    /* Write ASM */
    LLVMTargetMachineEmitToFile(target_machine, module, out_filename, LLVMAssemblyFile, &error);
    LLVMWriteBitcodeToFile(module, "build/test.bc");
    LLVMDisposeMessage(error);
    return 0;
}

LLVMValueRef code_gen_while_loop(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {
    LLVMBasicBlockRef loop_header = LLVMAppendBasicBlockInContext(LLVMGetModuleContext(module), LLVMGetBasicBlockParent(LLVMGetInsertBlock(builder)), "loop_header");
    LLVMBasicBlockRef loop_body = LLVMAppendBasicBlockInContext(LLVMGetModuleContext(module), LLVMGetBasicBlockParent(LLVMGetInsertBlock(builder)), "loop_body");
    LLVMBasicBlockRef loop_end = LLVMAppendBasicBlockInContext(LLVMGetModuleContext(module), LLVMGetBasicBlockParent(LLVMGetInsertBlock(builder)), "loop_end");

    LLVMPositionBuilderAtEnd(builder, loop_header);
    LLVMValueRef loop_condition = code_gen_node(node->op.while_loop.test, module, builder);
    LLVMBuildCondBr(builder, loop_condition, loop_body, loop_end);

    LLVMPositionBuilderAtEnd(builder, loop_body);
    code_gen_node(node->op.while_loop.block, module, builder);
    LLVMBuildBr(builder, loop_header);

    LLVMPositionBuilderAtEnd(builder, loop_end);

    return NULL;
}

// doesn't work with elifs yet
LLVMValueRef code_gen_if(Node * node, LLVMModuleRef module, LLVMBuilderRef builder) {    
    // Generate the condition.
    LLVMValueRef condition = code_gen_node(node->op.if_statement.test, module, builder);

    if (condition == NULL) {
        return NULL; 
    }

    // Convert condition to bool.
    LLVMValueRef zero = LLVMConstReal(LLVMDoubleType(), 0);
    condition = LLVMBuildFCmp(builder, LLVMRealONE, condition, zero, "ifcond");

    // Retrieve function.
    LLVMValueRef func = LLVMGetBasicBlockParent(LLVMGetInsertBlock(builder));
    
    // Generate expr and merge
    LLVMBasicBlockRef then_block = LLVMAppendBasicBlock(func, "then");
    LLVMBasicBlockRef else_block = LLVMAppendBasicBlock(func, "else");
    LLVMBasicBlockRef merge_block = LLVMAppendBasicBlock(func, "ifcont");
    
    LLVMBuildCondBr(builder, condition, then_block, else_block);

    // Generate 'then' block.
    LLVMPositionBuilderAtEnd(builder, then_block);
    LLVMValueRef then_value = code_gen_node(node->op.if_statement.block, module, builder);
    if(then_value == NULL) {
        return NULL;
    }
    
    LLVMBuildBr(builder, merge_block);
    then_block = LLVMGetInsertBlock(builder);

    // Check for else
    Node *else_node = node->op.if_statement.next; 
    if (else_node == NULL) {
        return NULL; // not sure what to do if there's no else 
    }

    // Generate 'else' block.
    LLVMPositionBuilderAtEnd(builder, else_block);
    LLVMValueRef else_value = code_gen_node(else_node->op.if_statement.block, module, builder);
    if(else_value == NULL) {
        return NULL;
    }
    LLVMBuildBr(builder, merge_block);
    else_block = LLVMGetInsertBlock(builder);

    LLVMPositionBuilderAtEnd(builder, merge_block);
    LLVMValueRef phi = LLVMBuildPhi(builder, LLVMDoubleType (), "");
    LLVMAddIncoming(phi, &then_value, &then_block, 1);
    LLVMAddIncoming(phi, &else_value, &else_block, 1);
    
    return phi;
}

LLVMValueRef code_gen_node(Node *node, LLVMModuleRef module, LLVMBuilderRef builder) {
    switch (node->tag) {
        case var_dec_node:
            return code_gen_var_dec(node, module, builder);
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
            return code_gen_while_loop(node, module, builder);
        case do_loop_node:
            break;
        case for_loop_node:
            break;
        case control_node:
            break;
        case if_node:
            return code_gen_if(node, module, builder);
        case fun_call_node:
            break;
        case block_node:
            break;
        case import_node:
            break;
        default:
            yyerror(&node, "Unsupported node type. Ensure code_gen.c covers every node tag\n");
    }
    return NULL;
}

LLVMValueRef code_gen_binary_expr(Node *node, LLVMModuleRef module, LLVMBuilderRef builder) {
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
            yyerror(&node, "Power operation for integers not yet implemented\n");
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
            yyerror(&node, "Unsupported operator type. Ensure code_gen.c covers all builtin binary operators\n");
            return left;
    }
}
