all: hcsh
 
hcsh: shell.o function.o
	gcc -lreadline -o hcsh shell.o function.o

shell.o: shell.c function.h constant.h
	gcc -c shell.c
function.o: function.c function.h constant.h
	gcc -c function.c
function.h: datastructure.h
datastructure.h: constant.h

.PHONY: clean
clean:
	rm -rf hcsh *.o
