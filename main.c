#include "src/corrector.h"
#include <locale.h>

int main(int argc, char **argv ) {

  if (argc == 3) {
    setlocale(LC_ALL, "");

    TablaHash* diccionario = leer_diccionario("listado-general.txt");
    corregir_archivo(argv[1], argv[2], diccionario);

    tablahash_destruir(diccionario);

    return 0;

  } else {
    printf("Cantidad de argumentos inválida.\n");
    return -1;
  }
}