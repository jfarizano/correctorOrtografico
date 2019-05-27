#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "src/bstree/bstree.h"
#include "src/tablaHash/tablaHash.h"

size_t hash(wchar_t* string) {
  size_t suma = 0;
  for (size_t i = 0; i < wcslen(string); i++) {
    suma += string[i];
  }

  return suma;
}

int main() {
  setlocale(LC_ALL, "");
  wchar_t* buff = malloc(sizeof(wchar_t) * 80);
  size_t len;
  TablaHash* tablaStrings = tablahash_crear(1999, hash);

  FILE *archivo;
  archivo = fopen("listado-general.txt", "r");
  wchar_t* ptr = fgetws(buff, 80, archivo);
  while (ptr != NULL) {
    len = wcslen(buff);
    if (buff[len-1] == '\n') {
      buff[len-1] = '\0';
      len--;
    }

    tablahash_insertar(tablaStrings, buff);
    
    ptr = fgetws(buff, 80, archivo);
  }

  fclose(archivo);
  free(buff);
  tablahash_destruir(tablaStrings);
  return 0;
}