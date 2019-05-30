#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "bstree.h"
#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Puntero a función hash.

typedef size_t (*FuncionHash)(wchar_t* string);

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras.


typedef struct {
  BSTree* tabla;
  size_t capacidad;
  FuncionHash hash;
} TablaHash;

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

/*
  tablahash_crear(): size_t FuncionHash -> TablaHash*
  Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(size_t capacidad, FuncionHash hash);

/*
  tablahash_insertar(): TablaHash* wchar_t*
  Inserta el string en la tabla.
 */
void tablahash_insertar(TablaHash* tabla, wchar_t* string);

/*
  tablahash_buscar(): TablaHash* wchar_t* -> int
  Dado un string, lo busca en la tabla hash. Si la tabla contiene el string
  devuelve 1, en caso contrario devuelve 0.
 */
int tablahash_buscar(TablaHash* tabla, wchar_t* string);

/*
  tablahash_destruir(): TablaHash* -> void
  Destruye la tabla y sus datos.
 */
void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */