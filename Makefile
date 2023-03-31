CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic-errors -Wno-unused-but-set-variable -Wno-unused-function

SRC=src
BIN=bin

PARSER=$(SRC)/parser
PARSER_SRC=$(PARSER).y
PARSER_C=$(PARSER).c
PARSER_HEADER=$(PARSER).h
BISON=bison
BISON_FLAGS=

LEXER=$(SRC)/lexer
LEXER_SRC=$(LEXER).lex
LEXER_C=$(LEXER).c
LEXER_HEADER=$(LEXER).h
FLEX=flex
FLEX_FLAGS=--never-interactive --batch

PROGRAM=$(BIN)/symble
MAIN_SRC=$(SRC)/main.c

all: $(PROGRAM)

$(PROGRAM): $(LEXER_C) $(PARSER_C) $(LEXER_HEADER) $(PARSER_HEADER) $(MAIN_SRC)
	$(CC) $(CFLAGS) $(MAIN_SRC) $(PARSER_C) $(LEXER_C) -o $(PROGRAM) -DYYERROR_VERBOSE -DYYDEBUG=1 -ly -ll

$(PARSER): $(LEXER_C) $(PARSER_C) $(PARSER_HEADER)
	$(CC) $(CFLAGS) $(PARSER_C) $(SCANNER_C) -o $(PARSER) -DYYERROR_VERBOSE -ly -ll

$(PARSER_C) $(PARSER_HEADER): $(PARSER_SRC)
	$(BISON) $(BISON_FLAGS) --defines=$(PARSER_HEADER) --output=$(PARSER_C) $(PARSER_SRC)

$(LEXER_C) $(LEXER_HEADER): $(LEXER_SRC) $(PARSER_HEADER) # Run bison first so we have the generated header
	$(FLEX) -o $(LEXER_C) --header-file=$(LEXER_HEADER) $(LEXER_SRC)

test: all
	./$(PROGRAM) tests/expr_test.sy

clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(LEXER_HEADER) $(PARSER_HEADER) $(PROGRAM)
