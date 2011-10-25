all: hcsh

run: all
	make all
	./hcsh
 
hcsh: lexer.o tokens.o shell.o
	gcc -o hcsh lexer.o tokens.o shell.o

shell.o: shell.c lexer.h const.h
	gcc -c shell.c

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
