#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras

// BSTree es un árbol de búsqueda (ABB)
typedef struct _BSTNodo {
  wchar_t *string;
  struct _BSTNodo *left;
  struct _BSTNodo *right;
} BSTNodo;

typedef BSTNodo *BSTree;

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

/*
  bstree_crear(): None -> BSTree
  Crea un árbol vacío.
*/
BSTree bstree_crear();

/*
  bstree_insertar(): wchar_t* BSTree -> BSTree
  Inserta el string dado en el árbol dado.
*/
BSTree bstree_insertar(wchar_t *string, BSTree arbol);

/*
  bstree_buscar(): wchar_t* BSTree -> int
  Dado un string y un árbol, devuelve 1 si el árbol contiene al string,
  en caso contrario devuelve 0.
*/
int bstree_buscar(wchar_t *string, BSTree arbol);

/*
  bstree_destruir(): BSTree -> void
  Libera de la memoria un árbol y sus datos
*/
void bstree_destruir(BSTree arbol);

#endif /* __BSTREE_H__ */