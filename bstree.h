#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Puntero a función utilizada en recorrer.
typedef void (*FuncionVisitante) (wchar_t* string);

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras.

// BSTree es un árbol de búsqueda (ABB).
typedef struct _BSTNodo {
  wchar_t* string;
  struct _BSTNodo *left;
  struct _BSTNodo *right;
} BSTNodo;

typedef BSTNodo* BSTree;

typedef enum {
  BSTREE_RECORRIDO_IN,
  BSTREE_RECORRIDO_PRE,
  BSTREE_RECORRIDO_POST,
} BSTreeOrdenDeRecorrido;

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
BSTree bstree_insertar(BSTree arbol, wchar_t* string);

/*
  bstree_buscar(): wchar_t* BSTree -> int
  Dado un string y un árbol, devuelve 1 si el árbol contiene al string,
  en caso contrario devuelve 0.
*/
int bstree_contiene(BSTree arbol, wchar_t* string);

/*
  bstree_destruir(): BSTree -> void
  Libera de la memoria un árbol y sus datos.
*/
void bstree_destruir(BSTree arbol);

/*
  bstree_cantidad(): BSTree -> int
  Devuelve la cantidad de elementos que tiene el árbol.
*/
int bstree_cantidad(BSTree arbol);

/*
  bstree_recorrer(): BSTree BSTreeOrdenDeRecorrido FuncionVisitante -> void
  Evalúa la función visit en todos los elementos del arbol en el orden dado.
*/
void bstree_recorrer(BSTree arbol, BSTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

/*
  bstree_recorrer_in(): BSTree FuncionVisitante -> void
  Evalúa la función visit en todos los elementos del arbol en inorden
*/
void bstree_recorrido_in(BSTree arbol, FuncionVisitante visit);

/*
  bstree_recorrer_pre(): BSTree FuncionVisitante -> void
  Evalúa la función visit en todos los elementos del arbol en preorden.
*/
void bstree_recorrido_pre(BSTree arbol, FuncionVisitante visit);

/*
  bstree_recorrer_post(): BSTree FuncionVisitante -> void
  Evalúa la función visit en todos los elementos del arbol en postorden.
*/
void bstree_recorrido_post(BSTree arbol, FuncionVisitante visit);

#endif /* __BSTREE_H__ */