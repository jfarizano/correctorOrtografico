#ifndef __CORRECTOR_H__
#define __CORRECTOR_H__

#include "bstree.h"
#include "tablaHash.h"
#include "slist.h"
#include <stdio.h>
#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.

void salida_archivo(wchar_t* palabra, SList sugerencias, 
                     int terminaCharEspecial, wchar_t charFinal, 
                     size_t linea, FILE* archivoSalida);

void string_minuscula(wchar_t* string);

size_t hash_polinomico(wchar_t* string);

size_t hash_suma(wchar_t* string);

int caracter_especial(wchar_t charFinal);

int continuar(size_t cantSugerencias, size_t profundidad);

void comprobar_sugerencia(TablaHash* diccionario, SList* sugerencias, 
                          size_t* cantSugerencias, wchar_t* sugerencia);

void metodo_permutacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad, 
                          wchar_t* palabra);

void metodo_insercion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad, 
                          wchar_t* palabra);

void metodo_eliminacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad, 
                          wchar_t* palabra);

void metodo_reemplazo(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad, 
                          wchar_t* palabra);

void metodo_separacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad, 
                          wchar_t* palabra);

void corregir_palabra(wchar_t* palabra, TablaHash* diccionario, 
                      size_t linea, FILE* archivoSalida);

void corregir_archivo(char* nombreArchivoEntrada, char* nombreArchivoSalida, 
                        TablaHash* diccionario);

TablaHash* leer_diccionario(char* nombreArchivo);                                               

#endif /* __CORRECTOR_H__ */