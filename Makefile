SRC=src
BIN=bin
BUILD=build
TEST=tests
TEST_BIN=bin/tests
FLEX_OUT=flex_out
BISON_OUT=bison_out

CC=clang
CXX=clang++
LLVM_CC_FLAGS=`llvm-config --cflags`
LLVM_LINK_FLAGS=`llvm-config --libs --cflags --ldflags core analysis executionengine native`
CFLAGS=$(LLVM_CC_FLAGS) -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-function -Wno-sign-compare -Wno-unused-parameter -DYYERROR_VERBOSE -DYYDEBUG=1  -iquote $(SRC) -iquote $(FLEX_OUT) -iquote $(BISON_OUT)
CXXFLAGS=$(LLVM_LINK_FLAGS) -Wall -Wextra -Werror -iquote $(SRC) -iquote $(FLEX_OUT) -iquote $(BISON_OUT)

PARSER_NAME=parser
PARSER_SRC=$(SRC)/$(PARSER_NAME).y
PARSER_C=$(BISON_OUT)/$(PARSER_NAME).c
PARSER_HEADER=$(BISON_OUT)/$(PARSER_NAME).h
PARSER_O=$(BISON_OUT)/$(PARSER_NAME).o
BISON=bison
BISON_FLAGS=
# BISON_FLAGS=-Wcounterexamples

LEXER_NAME=lexer
LEXER_SRC=$(SRC)/$(LEXER_NAME).lex
LEXER_C=$(FLEX_OUT)/$(LEXER_NAME).c
LEXER_HEADER=$(FLEX_OUT)/$(LEXER_NAME).h
LEXER_O=$(FLEX_OUT)/$(LEXER_NAME).o
FLEX=flex
FLEX_FLAGS=--never-interactive

C_SRCS=$(wildcard $(SRC)/*.c)
C_OBJECTS=$(C_SRCS:$(SRC)/%.c=$(BUILD)/%.o)

PROGRAM=$(BIN)/symble

.PHONY: all test clean

all: $(PROGRAM)

$(PROGRAM): $(LEXER_O) $(PARSER_O) $(LEXER_HEADER) $(PARSER_HEADER) $(C_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(C_OBJECTS) $(PARSER_O) $(LEXER_O) -o $(PROGRAM) $(CXXFLAGS)

$(C_OBJECTS): $(C_SRCS)
	@mkdir -p $(@D)
	$(CC) -c $(patsubst $(BUILD)/%.o,$(SRC)/%.c,$@) -o $@ $(CFLAGS)

$(PARSER_C) $(PARSER_HEADER): $(PARSER_SRC)
	@mkdir -p $(@D)
	$(BISON) $(BISON_FLAGS) --defines=$(PARSER_HEADER) --output=$(PARSER_C) $(PARSER_SRC)

$(LEXER_C) $(LEXER_HEADER): $(LEXER_SRC) $(PARSER_HEADER) # Run bison first so we have the generated header
	@mkdir -p $(@D)
	$(FLEX) -o $(LEXER_C) --header-file=$(LEXER_HEADER) $(LEXER_SRC)

test: all $(TEST)/expr_test.sy $(TEST)/function_test.sy
	$(PROGRAM) -v $(TEST)/expr_test.sy
	$(PROGRAM) -v $(TEST)/function_test.sy

test_table: $(TEST_BIN)/symbol_table_test
	$(TEST_BIN)/symbol_table_test # valgrind -s --tool=memcheck --leak-check=full --track-origins=yes $(TEST_BIN)/symbol_table_test

$(TEST_BIN)/symbol_table_test: $(TEST)/symbol_table_test.c $(SRC)/symbol_table.c
	@mkdir -p $(TEST_BIN)
	$(CC) -g3 -gdwarf-4 $(TEST)/symbol_table_test.c $(SRC)/symbol_table.c -o $(TEST_BIN)/symbol_table_test $(CFLAGS)


clean:
	@rm -Rf $(FLEX_OUT)/* $(BISON_OUT)/* $(BIN)/* $(BUILD)/* $(PROGRAM)
