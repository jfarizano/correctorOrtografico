#include "tablaHash.h"
#include <stdlib.h>
#include <stddef.h>
#include <wchar.h>

TablaHash* tablahash_crear(size_t capacidad, FuncionHash hash) {
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->tabla = malloc(sizeof(BSTree) * capacidad);
  tabla->capacidad = capacidad;
  tabla->hash = hash;

  for (size_t i = 0; i < capacidad; i++) {
    tabla->tabla[i] = NULL;
  }

  return tabla;
}

void tablahash_insertar(TablaHash* tabla, wchar_t* string) {
  size_t key = tabla->hash(string) % tabla->capacidad;
  tabla->tabla[key] = bstree_insertar(tabla->tabla[key], string);
}

int tablahash_buscar(TablaHash* tabla, wchar_t* string) {
  size_t key = tabla->hash(string) % tabla->capacidad;
  return bstree_buscar(tabla->tabla[key], string);
}

void tablahash_destruir(TablaHash* tabla) {
  for (size_t i = 0; i < tabla->capacidad; i++) {
    bstree_destruir(tabla->tabla[i]);
  }
  free(tabla->tabla);
  free(tabla);
}