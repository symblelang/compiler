SRC=src
BIN=bin
FLEX_OUT=flex_out
BISON_OUT=bison_out

CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic-errors -Wno-unused-but-set-variable -Wno-unused-function -iquote $(FLEX_OUT) -iquote $(BISON_OUT)

PARSER_NAME=parser
PARSER_SRC=$(SRC)/$(PARSER_NAME).y
PARSER_C=$(BISON_OUT)/$(PARSER_NAME).c
PARSER_HEADER=$(BISON_OUT)/$(PARSER_NAME).h
PARSER_O=$(BISON_OUT)/$(PARSER_NAME).o
BISON=bison
BISON_FLAGS=

LEXER_NAME=lexer
LEXER_SRC=$(SRC)/$(LEXER_NAME).lex
LEXER_C=$(FLEX_OUT)/$(LEXER_NAME).c
LEXER_HEADER=$(FLEX_OUT)/$(LEXER_NAME).h
LEXER_O=$(FLEX_OUT)/$(LEXER_NAME).o
FLEX=flex
FLEX_FLAGS=--never-interactive

PROGRAM=$(BIN)/symble
MAIN_SRC=$(SRC)/main.c

.PHONY: all test clean

all: $(PROGRAM)

$(PROGRAM): $(LEXER_O) $(PARSER_O) $(LEXER_HEADER) $(PARSER_HEADER) $(MAIN_SRC)
	@mkdir -p $(@D)
	$(CC) $(MAIN_SRC) $(PARSER_C) $(LEXER_C) -o $(PROGRAM) $(CFLAGS) -DYYERROR_VERBOSE -DYYDEBUG=1 -ly -ll 

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(PARSER_C) $(PARSER_HEADER): $(PARSER_SRC)
	@mkdir -p $(@D)
	$(BISON) $(BISON_FLAGS) --defines=$(PARSER_HEADER) --output=$(PARSER_C) $(PARSER_SRC)

$(LEXER_C) $(LEXER_HEADER): $(LEXER_SRC) $(PARSER_HEADER) # Run bison first so we have the generated header
	@mkdir -p $(@D)
	$(FLEX) -o $(LEXER_C) --header-file=$(LEXER_HEADER) $(LEXER_SRC)

test: all
	$(PROGRAM) -v tests/expr_test.sy
	$(PROGRAM) -v tests/function_test.sy

clean:
	@rm -f $(FLEX_OUT)/* $(BISON_OUT)/* $(BIN)/* $(PROGRAM)
