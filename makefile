CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic-errors

PARSER=parser
PARSER_SRC=$(PARSER).y
PARSER_C=$(PARSER).c
PARSER_HEADER=$(PARSER).h
BISON=bison
BISON_FLAGS=

LEXER=lexer
LEXER_SRC=$(LEXER).lex
LEXER_C=$(LEXER).c
FLEX=flex
FLEX_FLAGS=--never-interactive --batch

PROGRAM=$(PARSER)

$(PARSER): $(LEXER_C) $(PARSER_C)
	$(CC) $(PARSER_C) $(SCANNER_C) -o $(PARSER) $(CFLAGS) -ly -ll

$(PARSER_C) $(PARSER_HEADER): $(PARSER_SRC)
	$(BISON) $(BISON_FLAGS) --defines=$(PARSER_HEADER) --output=$(PARSER_C) $(PARSER_SRC)

$(LEXER_C): $(LEXER_SRC) $(PARSER_HEADER) # Run bison first so we have the generated header
	$(FLEX) -o $(LEXER) $(LEXER_SRC)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	@rm -f $(LEXER_C) $(PARSER_C) $(PARSER) 
