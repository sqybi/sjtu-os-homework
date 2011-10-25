all: hcsh
 
hcsh: shell.o function.o
	gcc -lreadline -o hcsh shell.o function.o

shell.o: shell.c function.h
	gcc -c shell.c
function.o: function.c function.h
	gcc -c function.c

.PHONY: clean
clean:
	rm -rf hcsh *.o