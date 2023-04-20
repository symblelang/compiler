# Symble Compiler

## Language Changes

Here are a few changes to the grammar or language specification that have been made in the course of writing the parser. We can always rework these later.

- Semicolons are now used to end statements
- `^` is used for exponentiation, and `~` is used instead for bitwise xor.
- Function *types* now also start with the keyword `fun`, such as `fun (int, int) -> int`. 

## To Do List

### Syntax / Grammar (higher priority)
- for loops (not sure what sort of syntax we want)
- More types, esp. tuples, lists, probably some sort of aggregate like a struct
- Function declarations with generic types (this might be a little ambitious for type checking so maybe wait on this)
- Probably various other things I'm forgetting about
- Possibly add anonymous functions via "lambda" or similar keyword

### Lexer
- Add more literals such as float literals, specifying int literals by octal/hexadecimal, array literals, etc.
- Improve string processing (current implementation is untested as far as I know)

### Semantic Analysis
- Symbol table creation
  - I'm currently working on this and added a branch for it on GitHub, and it should be complete before the end of the week
- Syntax tree generation (like in PA 2)
  - The symbol table is almost functional enough to support this
  - This will probably take a fair amount of work from multiple people
