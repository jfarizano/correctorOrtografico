#ifndef __CORRECTOR_H__
#define __CORRECTOR_H__

#include "bstree.h"
#include "tablaHash.h"
#include "slist.h"
#include <stdio.h>
#include <stddef.h>

///////////////////////////////////////////////////////////////////////////////
// Prototipos de funciones.



/*
  salida_archivo(): wchar_t SList int wchar_t size_t .

  Toma la palabra que no se encuentra en el diccionario, la lista de sugerencias,
  la condicion de si tiene o no caracteres especiales(los cuales serian agregados
  al final) y el numero de linea, y devuelve la salida a archivo formateada de 
  la siguente forma :
  Linea N, "PALABRA" no esta en el diccionario.
  Quizas quiso decir: SUGERENCIA1, SUGERENCIA2, ..., SUGERENCIAN.
*/
void salida_archivo(wchar_t* palabra, SList sugerencias, 
                     int terminaCharEspecial, wchar_t charFinal, 
                     size_t linea, FILE* archivoSalida);


/*
  string_minuscula() : wchar_t*
  Toma una palabra y la normaliza a minuscula.
*/
void string_minuscula(wchar_t* string);


/*
  hash_polinomico() : wchar_t* -> size_t

  Toma una palabra a ser ingresada en la tabla hash, y obtiene su clave.
  Esta clave se obtiene mediante un algoritmo polinómico al cual se aplicará
  el módulo por el tamaño de la tabla hash.
*/
size_t hash_polinomico(wchar_t* string);

/*
  caracter_especial() : wchar_t -> int
  Revisa si la palabra, tomada como argumento, posee o no caracteres especiales
  al final de la misma, de ser asi devuelve 1, de lo contrario devuelve 0.
*/
int caracter_especial(wchar_t charFinal);

/*
  continuar(): size_t size_t -> int
  Toma  la cantidad de sugerencias y profundidad, y devuelve 1 si lo cumplen, o 
  0 si alguno de los parametros falla.

*/
int continuar(size_t cantSugerencias, size_t profundidad);

/*
  comprobar_sugerencia() : TablaHash SList size_t* wchar_t*
  Toma la sugerencia y la revisa, si esta en el diccionario y no esta en la lista
  de sugerencias previas, la añade.
*/
void comprobar_sugerencia(TablaHash* diccionario, SList* sugerencias, 
                          size_t* cantSugerencias, wchar_t* sugerencia);

///////////////////////////////////////////////////////////////////////////////
// Funciones de metodos de correcion.

/*
  Estas funciones reciben el diccionario, los strings sobre los que hay que
  iterar en cambiosActuales, y guardan los cambios en cambiosNuevos.
  cantSugerencias y profundidad se utilizan para limitar la cantidad de
  operaciones. 
*/

/*
  metodo_permutacion(): TablaHash* SList SList* SList* size_t* size_t* -> void
  Este método intercambia dos letras adyacentes.
*/
void metodo_permutacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad);

/*
  metodo_insercion(): TablaHash* SList SList* SList* size_t* size_t* -> void
  Este método inserta una letra del abecedario en cada posición.
*/                          
void metodo_insercion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad);

/*
  metodo_eliminacion(): TablaHash* SList SList* SList* size_t* size_t* -> void
  Este método elimina cada caracter de la palabra.
*/
void metodo_eliminacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad);

/*
  metodo_reemplazo(): TablaHash* SList SList* SList* size_t* size_t* -> void
  Este método reemplaza cada caracter de la palabra por otro del abecedario.
*/
void metodo_reemplazo(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad);

/*
  metodo_permutacion(): TablaHash* SList SList* SList* size_t* size_t* -> void
  Este método recibe un string y lo divide en 2 mediante un espacio.
*/
void metodo_separacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad);
///////////////////////////////////////////////////////////////////////////////

/*
  corregir_palabra(): wchar_t* TablaHash* size_t FILE* -> void
  Esta funcion recibe una palabra a corregir, un diccionario, la linea en la 
  que se encuentra y el archivo en que se realiza la salida.
  Busca todas las correciones posibles y realiza la salida indicandolas en
  el archivo dado.
*/
void corregir_palabra(wchar_t* palabra, TablaHash* diccionario, 
                      size_t linea, FILE* archivoSalida);

/*
  corregir_archivo(): char* char* TablaHash* -> void
  Esta función recibe los nombres de los archivos de entrada y salida, y
  el diccionario.
  Lee cada palabra del archivo de entrada, y realiza las correcciones
  y la salida.
*/
void corregir_archivo(char* nombreArchivoEntrada, char* nombreArchivoSalida, 
                        TablaHash* diccionario);

/*
  leer_diccionario(): char* -> TablaHash*
  Recibe el nombre del archivo en que se encuentra el diccionario y lo carga
  a una tabla hash.
*/
TablaHash* leer_diccionario(char* nombreArchivo);                                               

#endif /* __CORRECTOR_H__ */