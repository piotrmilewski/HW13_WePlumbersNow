all: main.o
	gcc -o runo main.o

main.o: main.c
	gcc -c main.c

run: all
	./runo

clean:
	rm -rf *.o *~ runo
