# Symble Compiler

## Language Changes

Here are a few changes to the grammar or language specification that have been made in the course of writing the parser. We can always rework these later.

- Semicolons are now used to end statements
- `^` is used for exponentiation, and `~` is used instead for bitwise xor.
- Function *types* now also start with the keyword `fun`, such as `fun (int, int) -> int`. 

## Notes

Some (hopefully) helpful notes:

- The array member operator (e.g. `array[2]`) is treated as "[]" in the symbol table. 
- `ArgTypes` is used for function types (e.g. when functions are passed as arguments), while `Args` is used for function calls and defs

## To Do List

### Semantic Analysis (focus)
1. By tomorrow night (April 26th) - Have `handle_x` function definitions for all rules in our bison (`parser.y`) file.
2. By this weekend (April 29th-ish) - Have bodies for `handle_x` functions completed and creating nodes with syntax_tree.c For each rule:
   - If necessary, add a struct and tag to the `struct Node` in `syntax_tree.h`, and optionally add a helper function to `syntax_tree.c` for creating a node of this type. See examples in the files. Note that not everything actually needs a node in the syntax tree, for example see the `handle_custom_type` function in `handlers.c`
   - Populate the handler function in `handlers.c` with code for creating the node.
3. By the end of classes (May 4th) - Have syntax tree working and able to generate a complete representation of our program
4. By the end of study days (May 8th) - Have intermediate code generation to pseudo-code completed
5. Consult with Aviram regarding our work so far and what he wants in regards to additional functionality
6. From start of exams until May 15 - Work on Aviram's requirements, create testing script, add additional features, data structures, etc.
7. Done!

### Things for Later / Optional

#### Syntax / Grammar
- More types, esp. tuples, lists, probably some sort of aggregate like a struct
- Function declarations with generic types (this might be a little ambitious for type checking so maybe wait on this)
- Probably various other things I'm forgetting about
- Possibly add anonymous functions via "lambda" or similar keyword

#### Lexer
- Add more literals such as float literals, specifying int literals by octal/hexadecimal, array literals, etc.
- Improve string processing (current implementation is untested as far as I know)
