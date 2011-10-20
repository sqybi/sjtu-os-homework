all: bus

bus: bus.o
	gcc -pthread -o bus bus.o
bus.o: bus.c
	gcc -c bus.c

clean:
	rm -rf *.o bus