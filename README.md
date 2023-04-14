# Symble Compiler

## Language Changes

Here are a few changes to the grammar or language specification that have been made in the course of writing the parser. We can always rework these later.

- Semicolons are now used to end statements
- `^` is used for exponentiation, and `~` is used instead for bitwise xor.
- Function *types* now also start with the keyword `fun`, such as `fun (int, int) -> int`. 