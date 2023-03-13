all: mymalloc.o memgrind

memgrind: memgrind.c mymalloc.o
	gcc -o memgrind memgrind.c mymalloc.o

mymalloc.o: mymalloc.c mymalloc.h
	gcc -c mymalloc.c

clean:
	rm -rf *.o memgrind
