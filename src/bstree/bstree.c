#include "bstree.h"
#include <stdlib.h>
#include <stddef.h>
#include <wchar.h>

BSTree bstree_crear() {
  return NULL;
}

BSTree bstree_nuevo_nodo(wchar_t *string) {
  BSTree nuevoArbol = malloc(sizeof(BSTNodo));
  wchar_t *nuevoString = malloc(sizeof(wchar_t) * wcslen(string));
  nuevoArbol->left = NULL;
  nuevoArbol->right = NULL;
  nuevoArbol->string = nuevoString;

  return nuevoArbol;
}

BSTree bstree_insertar(wchar_t *string, BSTree arbol) {
  
  if (arbol == NULL) {
    BSTree nuevoArbol = bstree_nuevo_nodo(string);
    return nuevoArbol;
  }

  int comparacionStrings = wcscmp (string, arbol->string);

  if (comparacionStrings < 0) {
    arbol->left = bstree_insertar(string, arbol->left);
  } else if (comparacionStrings > 0) {
    arbol->right = bstree_insertar(string, arbol->right);
  }

  return arbol;
}

int bstree_buscar(wchar_t *string, BSTree arbol) {
  if (arbol == NULL) {
    return 0;
  }

  int comparacionStrings = wcscmp (string, arbol->string);

  if (comparacionStrings == 0) {
    return 1;
  } else if (comparacionStrings < 0) {
    return bstree_buscar(string, arbol->left);
  } else {
    return bstree_buscar(string, arbol->right);
  }
}

void bstree_destruir(BSTree arbol) {
  if (arbol != NULL) {
    bstree_destruir(arbol->left);
    bstree_destruir(arbol->right);
    free(arbol->string);
    free(arbol);
  }
}