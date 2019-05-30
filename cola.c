#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

Cola cola_crear() {
  return NULL;
}

int cola_vacia(Cola cola) {
  return cola == NULL;
}

wchar_t* cola_primero(Cola cola) {
  return cola->ant->string;
}

Cola cola_encolar(Cola cola, wchar_t* string) {
  CNodo* nuevoNodo = malloc(sizeof(CNodo));
  wchar_t* nuevoString = malloc(sizeof(wchar_t) * (wcslen(string) + 1));
  nuevoNodo->string = wcscpy(nuevoString, string);

  if (cola_vacia(cola)) {
    nuevoNodo->sig = nuevoNodo;
    nuevoNodo->ant = nuevoNodo;
  } else {
    nuevoNodo->sig = cola;
    nuevoNodo->ant = cola->ant;
    nuevoNodo->ant->sig = nuevoNodo;
    cola->ant = nuevoNodo;
  }

  return nuevoNodo;
}

Cola cola_desencolar(Cola cola) {
  if (cola == cola->ant) {
    free(cola->string);
    free(cola);
    return NULL;
  } else {
    CNodo *temp = cola->ant;
    cola->ant->ant->sig = cola;
    cola->ant = cola->ant->ant;
    free(temp->string);
    free(temp);
    return cola;
  }
}

void cola_destruir(Cola cola) {
  while (cola != NULL) {
    cola = cola_desencolar(cola);
  }
}
