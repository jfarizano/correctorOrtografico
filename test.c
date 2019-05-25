#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "bstree.h"

int main() {
  setlocale(LC_ALL, "");
  wchar_t buff[80];
  size_t len;
  BSTree arbol = bstree_crear();

  FILE *archivo;
  archivo = fopen("listado-general.txt", "r");

  while (fgetws(buff, 80, archivo) != NULL) {
    len = wcslen(buff);
    if (buff[len-1] == '\n') {
      buff[len-1] = '\0';
    }
    len = wcslen(buff);
    // wprintf(L"%ls\n", buff);

  arbol = bstree_insertar(buff, arbol);
    
  }
  
  printf("\n");
  fclose(archivo);
  bstree_destruir(arbol);
  return 0;
}