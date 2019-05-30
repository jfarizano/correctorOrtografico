#include "bstree.h"
#include <stdlib.h>
#include <stddef.h>
#include <wchar.h>
#include <stdio.h>

BSTree bstree_crear() {
  return NULL;
}

BSTree bstree_insertar(BSTree arbol, wchar_t* string) {  
  if (arbol == NULL) {
    BSTree nuevoArbol = malloc(sizeof(BSTNodo));
    wchar_t* nuevoString = malloc(sizeof(wchar_t) * (wcslen(string) + 1));
    nuevoArbol->left = NULL;
    nuevoArbol->right = NULL;
    nuevoArbol->string = wcscpy(nuevoString, string);
    return nuevoArbol;
  }

  int comparacionStrings = wcscmp(string, arbol->string);

  if (comparacionStrings < 0) {
    arbol->left = bstree_insertar(arbol->left, string);
  } else if (comparacionStrings > 0) {
    arbol->right = bstree_insertar(arbol->right, string);
  }

  return arbol;
}

int bstree_buscar(BSTree arbol, wchar_t* string) {
  if (arbol == NULL) {
    return 0;
  }

  int comparacionStrings = wcscmp(string, arbol->string);

  if (comparacionStrings == 0) {
    return 1;
  } else if (comparacionStrings < 0) {
    return bstree_buscar(arbol->left, string);
  } else {
    return bstree_buscar(arbol->right, string);
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

int bstree_cantidad(BSTree arbol) {
  if (arbol != NULL) {
    return (1 + bstree_cantidad(arbol->left) + bstree_cantidad(arbol->right));
  } else {
    return 0;
  }
}

void bstree_recorrer(BSTree arbol, BSTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  switch (orden) {
    case BSTREE_RECORRIDO_IN:
    bstree_recorrido_in(arbol, visit);
    break;

    case BSTREE_RECORRIDO_PRE:
    bstree_recorrido_pre(arbol, visit);
    break;

    case BSTREE_RECORRIDO_POST:
    bstree_recorrido_post(arbol, visit);
    break;
  }
}

void bstree_recorrido_in(BSTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    bstree_recorrido_in(arbol->left, visit);
    visit(arbol->string);
    bstree_recorrido_in(arbol->right, visit);
  }
}

void bstree_recorrido_pre(BSTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    visit(arbol->string);
    bstree_recorrido_pre(arbol->left, visit);
    bstree_recorrido_pre(arbol->right, visit);
  }
}

void bstree_recorrido_post(BSTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    bstree_recorrido_post(arbol->left, visit);
    bstree_recorrido_post(arbol->right, visit);
    visit(arbol->string);
  }
}