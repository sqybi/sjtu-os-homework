all: bus

bus: bus.o
	gcc -pthread -o bus bus.o
bus.o: bus.c
	gcc -c bus.c

.PHONY: clean
clean:
	rm -rf *.o bus
