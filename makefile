CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

test: test.c bstree.c tablaHash.c cola.c
	$(CC) $(CFLAGS) test.c bstree.c tablaHash.c cola.c -o test.o
