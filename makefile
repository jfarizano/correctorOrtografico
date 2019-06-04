CC = gcc
CFLAGS = -std=c99 -Wall

main: main.c src/corrector.c src/bstree.c src/tablaHash.c src/slist.c
	$(CC) $(CFLAGS) main.c src/corrector.c src/bstree.c src/tablaHash.c src/slist.c -o main.o