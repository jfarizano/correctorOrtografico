#include "bstree.h"
#include "tablaHash.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>

#define SIZETABLAHASH 1999
#define XHASHPOLINOMICO 39

size_t hash_suma(wchar_t* string) {
  size_t suma = 0;
  for (size_t i = 0; i < wcslen(string); i++) {
    suma += string[i];
  }

  return suma;
}

size_t hash_polinomico(wchar_t* string) {
  size_t clave = 0, len = wcslen(string);

  for (size_t i = 0; i < len; i++) {
    clave = XHASHPOLINOMICO * (string[i] + clave);
  }

  return clave % SIZETABLAHASH;
}

void imprimir_string(wchar_t* string) {
  wprintf(L"%ls\n", string);
}

void string_minuscula(wchar_t* string) {
  size_t len = wcslen(string);

  for (size_t i = 0; i < len; i++) {
    if (string[i] >= 65 && string[i] <= 90) {
      string[i] += 32;
    } else if (string[i] == 193 ||
              string[i] == 201 ||
              string[i] == 205 ||
              string[i] == 211 ||
              string[i] == 218 ||
              string[i] == 220) {
      string[i] += 32;
    }
  }
}

TablaHash* leer_diccionario(char* nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);

  TablaHash* tablaStrings = tablahash_crear(SIZETABLAHASH, hash_polinomico);
  wchar_t* buff = malloc(sizeof(wchar_t) * 80);
  size_t len;


  while (fgetws(buff, 80, archivo) != NULL) {
    len = wcslen(buff);

    // Borrar el salto de línea si tiene.
    if (buff[len-1] == '\n') {
      buff[len-1] = '\0';
      len--;
    }
    string_minuscula(buff);
    tablahash_insertar(tablaStrings, buff);  
  }

  fclose(archivo);
  free(buff);

  return tablaStrings;
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  
  if (argc != 2) {
  TablaHash* tablaStrings = leer_diccionario("listado-general.txt");

  tablahash_destruir(tablaStrings);
  return 0;
  }

  printf("ERROR: Numero de argumentos del programa inválido\n");
  return 1;
}