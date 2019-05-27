#ifndef __BSTREE_H__
#define __BSTREE_H__

#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Puntero a función utilizada en recorrer
typedef void (*FuncionVisitante) (wchar_t* string);

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras

// BSTree es un árbol de búsqueda (ABB)
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
int bstree_buscar(BSTree arbol, wchar_t* string);

/*
  bstree_destruir(): BSTree -> void
  Libera de la memoria un árbol y sus datos.
*/
void bstree_destruir(BSTree arbol);

int bstree_cantidad(BSTree arbol);

void bstree_recorrer(BSTree arbol, BSTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit);

void bstree_recorrido_in(BSTree arbol, FuncionVisitante visit);

void bstree_recorrido_pre(BSTree arbol, FuncionVisitante visit);

void bstree_recorrido_post(BSTree arbol, FuncionVisitante visit);

#endif /* __BSTREE_H__ */