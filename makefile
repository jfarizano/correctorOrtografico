CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

test: test.c $(BSTREE) $(TABLAHASH)
	$(CC) $(CFLAGS) test.c "src/bstree/bstree.c" "src/tablaHash/tablahash.c" -o test.o
