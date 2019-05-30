#ifndef __COLA_H__
#define __COLA_H__

#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Definiciones de estructuras.

typedef struct _CNodo {
  wchar_t* string;
  struct _CNodo *ant;
  struct _CNodo *sig;
} CNodo;

typedef CNodo* Cola;

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

Cola cola_crear();

int cola_vacia(Cola cola);

wchar_t* cola_primero(Cola cola);

Cola cola_encolar(Cola cola, wchar_t* string);

Cola cola_desencolar(Cola cola);

void cola_destruir(Cola cola);

#endif /* __COLA_H__ */