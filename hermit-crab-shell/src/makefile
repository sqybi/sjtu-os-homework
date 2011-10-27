# make all
# default entry
all: hcsh

# make all and run the shell
# for debug
run: all
	./hcsh

# compile the whole shell
hcsh: shell.o lexer.o parser.o tokens.o command.o inline.o prompt.o dir.o
	gcc -o hcsh shell.o lexer.o parser.o tokens.o command.o inline.o prompt.o dir.o -lreadline -lhistory

# compile .c files to .o files
shell.o: shell.c const.h tokens.h lexer.h parser.h prompt.h debug.h 
	gcc -c shell.c
lexer.o: lexer.c const.h tokens.h lexer.h debug.h
	gcc -c lexer.c
parser.o: parser.c tokens.h command.h parser.h dir.h debug.h
	gcc -c parser.c
tokens.o: tokens.c tokens.h debug.h
	gcc -c tokens.c
command.o: command.c inline.h command.h dir.h debug.h
	gcc -c command.c
prompt.o: prompt.c prompt.h debug.h
	gcc -c prompt.c
inline.o: inline.c command.h inline.h debug.h
	gcc -c inline.c
dir.o: dir.c dir.h debug.h
	gcc -c dir.c

# generate .c files from .lex files
lexer.c: lexer.lex
	flex -o lexer.c lexer.lex

# link for .h files
lexer.h: tokens.h debug.h
parser.h: tokens.h command.h debug.h
tokens.h: debug.h
command.h: debug.h
prompt.h: debug.h
inline.h: command.h debug.h
const.h: debug.h
dir.h: debug.h

# clean process
.PHONY: clean
clean:
	rm -rf hcsh *.o lexer.c
