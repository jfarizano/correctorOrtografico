#include "slist.h"
#include <stdlib.h>
#include <wchar.h>

SList slist_crear() {
  return NULL;
}

SList slist_agregar_inicio(SList lista, wchar_t* string) {
  SNodo* nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->string = malloc(sizeof(wchar_t) * (wcslen(string) + 1));
  nuevoNodo->string = wcscpy(nuevoNodo->string, string);
  nuevoNodo->sig = lista;

  return nuevoNodo;
}

SList slist_eliminar_inicio(SList lista) {
  SNodo* temp = lista->sig;
  free(lista->string);
  free(lista);

  return temp;
}

int slist_cantidad(SList lista) {
  int cantidad = 0;
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig, cantidad++);

  return cantidad;  
}

void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar->string);
    free(nodoAEliminar);
  }
}

int slist_contiene(SList lista, wchar_t* string) {
  int encontrada = 0;
  for (SNodo *nodo = lista; nodo != NULL && encontrada == 0; nodo = nodo->sig) {
    if (wcscmp(string, nodo->string) == 0) {
      encontrada = 1;
    }
  }

  return encontrada;
}