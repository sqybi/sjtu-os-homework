all: hcsh

run: all
	make all
	./hcsh
 
hcsh: lexer.o tokens.o prompt.o shell.o
	gcc -o hcsh lexer.o tokens.o prompt.o shell.o -lreadline

shell.o: shell.c const.h lexer.h prompt.h tokens.h
	gcc -c shell.c

prompt.o: prompt.c prompt.h
	gcc -c prompt.c

lexer.o: lexer.c tokens.h const.h lexer.h
	gcc -c lexer.c

tokens.o: tokens.c tokens.h const.h
	gcc -c tokens.c

lexer.c: lexer.lex
	flex -o lexer.c lexer.lex

lexer.h: tokens.h

.PHONY: clean
clean:
	rm -rf hcsh *.o lexer.c
