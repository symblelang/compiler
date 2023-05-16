# Symble

## Authors: 

* Andrew Clark     - andrew.clark.6@bc.edu
*   Alex Liu         - alex.liu@bc.edu
*   Caden Parajuli   - caden.parajuli@bc.edu
*   Micheal Lebreck  - michael.lebreck@bc.edu
*   William Morrison - william.morrison.2@bc.edu

# Introduction

Symble is a general-purpose programming language with a strong static type system. Symble follows the following language paradigms: 
* Imperative
* Compiled 
* Procedural

# Language Tutorial

Symble requires Flex, Bison, and LLVM to build and execute. 

Example Program: 

```
fun test_func(int x, int y) -> int { 
    return x + y;
}
```

# Language Reference Manual 
## Lexical Conventions

### **1. Comments**

Comments in Symble are represented identically to comments in C. Multiline comments open with a backslash then asterisk, and close with the opposite. Single-line comments begin with two backslashes.  

```
/* Multiline 
Comment  */

// Single-line comment
```

### **2. Identifiers**

Identifers in Symble can be represented as a combination of letters, digits, and underscores; however, identifers must start with a character or an underscore. 
```
id_char             (?ix: [a-z_])
id                  {id_char}({id_char}|{digit})*
```
### **3. Keywords**

Symble uses the following reserved keywords:

`and, not, or, xor, fun, cfun, if, elif, else, for, import, as, switch, case, type, return, break, continue, int, float, str, ptr, void`

### **4. Data Types**

The following table shows the valid data types in Symble. 

| Type | Description | Size |
| - | - | - |
| `char` | Character | 1 byte |
| `int` | Integer | 4 bytes |
| `string` | String | 8 bytes | 
| `array` | Array | user-defined |
| `list` | List (resizable arrray) | variable |
| `(type, type, ...)` | Tuple | user-defined |
| `(type, type, ...) -> (type)` | Function type | N/A

### **5. Operators**

The following table shows the built-in operators in  Symble. 

| Operator | Description |
| - | - |
| `+, -, *, /` | Basic arithmetic | 
| `%` | Modular division |
| `**` | Exponentiation | 
| `&, \|, !` | Bitwise operators |
| `and, or, xor, not` | Logical operators |
| `==, <=, >=, !=` | Comparison |
| `+` | String concatenation |

Additionally, Symble supports user defined infix and prefix operators. 
New operators can be defined by the user, just like a function
```
fun `*&`(int x, int y) -> int
```

Associativity and precedence in new operators inherit the associativty and precedence of the first operator specified. In this example, type `*&` inherits the associtivty and precendence of the multiplication operator. 

## Grammar 

### **1. Types**

The following types (as shown below) are included in Symble, user-created types, primitive types, void types, function types, and pointer types. 

```
type:
    ID
    | INT_TYPE
    | FLOAT_TYPE 
    | STR_TYPE
    | VOID_TYPE
    | fun_type
    | PTR_TYPE type
    ;
```
```
fun_type:
    FUN LPAREN type_list RPAREN ARROW type
    ;
```
### **2. Parameters**

Parameters consist of variable specifiers and are shown by the productions below. Parameters are used in function definitions as well as `cfun` declarations. 

```
argument_list_specifier:
    variable_specifier
    | argument_list_specifier COMMA variable_specifier 
    ;

variable_specifier:
    type ID
    | type ID LSQB INT_LIT RSQB 
    ;
```

### **3. Arguments**

Arguments consist of expressions (which will be shown later in the section) and are used in function calls. 
```
argument_list:
    expr
    | argument_list COMMA expr
    ;
```
### **4. Program Structure**

Program is the top-level production in the grammar and hence the top level node in the syntax tree. This where the symbol table is first created. 
```
program:
    statement_list
    ;
```

All programs in Symble are represented by a `statement_list` which is comprised by a series of `statement`(s). Possible statements are shown in the following production: 

```
statement:
    expr_statement 
    | if_statement
    | function_def
    | cfun_dec
    | control_statement
    | variable_declaration
    | while_loop
    | for_loop
    | do
    | typedef
    | import_statement 
    ;
```

### **5. Declarations**

Function declarations are represented by the following production:  

```

cfun_dec:
    CFUN ID LPAREN argument_list_specifier RPAREN ARROW 
    type SEMICOLON
    ;
```

In code, an example declaration can be expressed as: 
```
cfun calloc(int nitems, int size) -> ptr void; 
```

### **6. Statements**

Here are the following statements accepted under Symble's grammar. 

**6.1 If statements**

The code within an `if` statement is executed if the condition evaluates to true, otherwise the code within the `else` statement runs, or the next `elif` statement is evaluated (just like an `if` statement). 
```
if_elif:
    IF LPAREN expr RPAREN statement_block %prec THEN 
    | if_elif ELIF LPAREN expr RPAREN statement_block 
    ;

if_statement:
    if_elif { $$ = $1; }
    | if_elif ELSE statement_block
    ;
```
**6.2 Function definitions**

Each function has an identifer followed by a list of parameters enclosed within parentheses. Then an arrow (`->`) is used to denote the return type of the function. Code within the function is enclosed in curly braces. 

For user-defined types involving functions, backticks are used to enclose the special type which is listed before the list of parameters. 
```
function_def:
    FUN ID LPAREN argument_list_specifier RPAREN ARROW 
    type statement_block
    
    | FUN BACKTICK user_operator BACKTICK 
    LPAREN argument_list_specifier RPAREN ARROW type
    statement_block 
    ;
```

**6.3 Control statement:**

Control statement allow change in the control flow. The keywords `return, break, continue ` are all used similarly to how they would be in any other language

```
control_statement:
    RETURN expr SEMICOLON { $$ = handle_return($expr); }
    | BREAK SEMICOLON { $$ = handle_break(); }
    | CONTINUE SEMICOLON { $$ = handle_break(); }
    ;
```

**6.4 Variable declarations**

Variable declarations are the same in Symble as they are in practically any other language. 
```
variable_declaration:
    type ID SEMICOLON
    | type ID EQUALS_OP expr SEMICOLON
    | type ID LSQB INT_LIT RSQB SEMICOLON 
    | type ID LSQB INT_LIT RSQB EQUALS_OP expr SEMICOLON
    ;
```

**6.5 While loops:**

Code within while loops in Symble will execute over and over again until the condition no longer evaluates to True.  

```
while_loop:
    WHILE LPAREN expr RPAREN statement_block 
    | WHILE LPAREN expr RPAREN SEMICOLON 
    ;
```

**6.6 For loops**

For loops in Symble use a counter to keep track of the number of iterations. The code within the while loop is continuously executed until the counter reaches a certain state. However, its possible for for loops to be used alternatively. 

```
for_loop:
    FOR LPAREN expr SEMICOLON expr SEMICOLON expr 
    RPAREN statement_block
    | FOR LPAREN variable_declaration expr SEMICOLON expr 
    RPAREN statement_block
    ;
```

**6.7 Do while loops**

Do while loops are similar to regular while loops except that the condition is checked at the bottom at the loop. 
```
do:
    statement_block WHILE LPAREN expr RPAREN SEMICOLON
    ;
```

**6.8 Typedef**

Typedefs in Symbol are used to create additional names for preexisting data types in Symble. 
```
typedef:
    TYPE ID EQUALS_OP type SEMICOLON
    ;
```
**6.8 Import statements**

```
import_statement:
    IMPORT ID SEMICOLON
    | IMPORT ID AS ID SEMICOLON 
    ;
```
### **7. Expressions**

There are many different types of expressions in Symble, they can all be found in `parser.y`. 

Assignment expressions, comparison expression, bitwise expression, and arithmetic expressions are some of the most common expressions found in Symble. 

### **8. Context Free Grammar**

The entire grammar can be found in `parser.y` under `src`. 

# Project Plan 

1. By tomorrow night (April 26th) - Have `handle_x` function definitions for all rules in our bison (`parser.y`) file.
2. By this weekend (April 29th-ish) - Have bodies for `handle_x` functions completed and creating nodes with syntax_tree.c For each rule:
   - If necessary, add a struct and tag to the `struct Node` in `syntax_tree.h`, and optionally add a helper function to `syntax_tree.c` for creating a node of this type. See examples in the files. Note that not everything actually needs a node in the syntax tree, for example see the `handle_custom_type` function in `handlers.c`
   - Populate the handler function in `handlers.c` with code for creating the node.
3. By the end of classes (May 4th) - Have syntax tree working and able to generate a complete representation of our program
4. By the end of study days (May 8th) - Have intermediate code generation to pseudo-code completed
5. Consult with Aviram regarding our work so far and what he wants in regards to additional functionality
6. From start of exams until May 15 - Work on Aviram's requirements, create testing script, add additional features, data structures, etc.

# Design 

**Lexical Analyzer:**

Flex was used to parse the source file and generate lexemes. Flex was also used to generate tokens and create literal values. 

**Syntax Analyzer:**

Bison was used to parse the tokens generated by Flex. In the semantic actions, nodes were added to the abstract syntax tree, and the symbol table was populated. 

**Code Generation** 

The LLVM-C-API was used to take care of code-generation. 

# Testing 

Tests were written for comments, expression, functions, if statements, and while loops. Additionally, a program meant to run the Sieve of Erastothenes was written. See all tests under `\tests`. 

# Contributions

Roles within the group were not strict whatsoever. Every teammember contributed whenever they could to the repository. 

# In the Future

See `TODO.md`