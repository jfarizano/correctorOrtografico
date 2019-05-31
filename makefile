CC = gcc
CFLAGS = -std=c99 -Wall

corrector: corrector.c bstree.c tablaHash.c slist.c
	$(CC) $(CFLAGS) corrector.c bstree.c tablaHash.c slist.c -o corrector.o
