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

Identifers in Symble can be represented as a combination of letters, digits, and underscores; however, identifers must start with characters. 
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

### **2. Parameters**

### **3. Arguments**

### **4. Program Structure**

### **5. Declarations**

### **6. Statements**

### **7. Expressions**

### **8. Context Free Grammar**

The entire grammar can be found in `parser.y` under `src`. 

# Project Plan 

# Design 

# Testing 

# Contributions

# In the Future
