all: rw

rw: rw.o
	gcc -pthread -o rw rw.o
rw.o: rw.c
	gcc -c rw.c

.PHONY: clean
clean:
	rm -rf *.o rw
