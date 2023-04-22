APP = symble
FLAGS = -Wall -DYYERROR_VERBOSE -g

${APP}: ${APP}.tab.c ${APP}.lex.c hash_table.c symbol_table.c ${APP}_handlers.c
	gcc $(FLAGS) $^ -o $@

${APP}.tab.c: ${APP}.y
	bison -dv $^

${APP}.lex.c: ${APP}.l
	lex -o $@ $^

clean:
	rm -rf ${APP} ${APP}.tab.* ${APP}.lex.* *.output *.dSYM

