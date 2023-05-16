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

```
variable_declaration:
    type ID SEMICOLON
    | type ID EQUALS_OP expr SEMICOLON
    | type ID LSQB INT_LIT RSQB SEMICOLON 
    | type ID LSQB INT_LIT RSQB EQUALS_OP expr SEMICOLON
    ;
```

**6.5 While loop:**

```
while_loop:
    WHILE LPAREN expr RPAREN statement_block 
    | WHILE LPAREN expr RPAREN SEMICOLON 
    ;
```

**6.6 For loop**

```
for_loop:
    FOR LPAREN expr SEMICOLON expr SEMICOLON expr 
    RPAREN statement_block
    | FOR LPAREN variable_declaration expr SEMICOLON expr 
    RPAREN statement_block
    ;
```

**6.7 Do while loops**
```
do:
    statement_block WHILE LPAREN expr RPAREN SEMICOLON
    ;
```

**6.8 Typedef**

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

# Design 

# Testing 

# Contributions

# In the Future
