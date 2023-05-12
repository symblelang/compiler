#ifndef CODE_GEN_H
#define CODE_GEN_H

#include <llvm-c/Core.h>

#include <stdio.h>

#include "syntax_tree.h"

#include "uthash/uthash.h"

typedef struct named_value
{
    const char *name;
    LLVMValueRef value;
    UT_hash_handle hh;
} named_value;

int code_gen_pass(Node *ast, FILE *out_file);
LLVMValueRef code_gen_node(Node *node, LLVMModuleRef module, LLVMBuilderRef builder);
LLVMValueRef code_gen_binary_expr(Node *node, LLVMModuleRef module, LLVMBuilderRef builder);

#endif /* CODE_GEN_H */
