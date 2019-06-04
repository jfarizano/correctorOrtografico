#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras

// SList es una lista simplemente enlazada.
typedef struct _SNodo {
  wchar_t* string;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

/*
  slist_crear(): None -> SList
  Devuelve una lista vacía.
*/
SList slist_crear();

/*
  slist_agregar_inicio(): SList wchar_t* -> SList
  Agrega el string dado al inicio de la lista.
*/
SList slist_agregar_inicio(SList lista, wchar_t* string);

/*
  slist_agregar_inicio(): SList wchar_t* -> SList
  Elimina el primer string de la lista.
*/
SList slist_eliminar_inicio(SList lista);

/*
  slist_cantidad(): SList -> int
  Devuelve la cantidad de elementos que contiene la lista.
*/
int slist_cantidad(SList lista);

/*
  slist_destruir(): SList -> void
  Libera de la memoria una lista y sus strings.
*/
void slist_destruir(SList lista);

/*
  slist_contiene(): SList wchar_t* -> int
*/
int slist_contiene(SList lista, wchar_t* string);

#endif /* __SLIST_H__ */