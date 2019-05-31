#include "bstree.h"
#include "tablaHash.h"
#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <assert.h>

#define XHASHPOLINOMICO 39
#define SIZETABLAHASH 1999

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

size_t hash_polinomico(wchar_t* string) {
  size_t clave = 0, len = wcslen(string);

  for (size_t i = 0; i < len; i++) {
    clave = XHASHPOLINOMICO * (string[i] + clave);
  }

  return clave % SIZETABLAHASH;
}

size_t hash_suma(wchar_t* string) {
  size_t suma = 0;
  for (size_t i = 0; i < wcslen(string); i++) {
    suma += string[i];
  }

  return suma;
}

int caracter_especial(wchar_t charFinal) {
  if (charFinal == 58 || charFinal == 59 || charFinal == 44 || 
      charFinal == 46 || charFinal == 63 || charFinal == 33)  {
    return 1;
  }
  return 0;
}

SList metodo_permutacion(SList cambiosActuales, SList cambiosNuevos) {
  size_t lenString;
  wchar_t charBuff, strBuff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(strBuff, nodo->string);

    for (size_t i = 0; i < lenString - 1; i++) {
      charBuff = strBuff[i];
      strBuff[i] = strBuff[i + 1];
      strBuff[i + 1] = charBuff;
      cambiosNuevos = slist_agregar_inicio(cambiosNuevos, strBuff);
      wcscpy(strBuff, nodo->string);
    }
  }

  return cambiosNuevos;
}

SList metodo_insercion(SList cambiosActuales, SList cambiosNuevos) {
  size_t lenString;
  wchar_t abecedario[] = L"abcdefghijklmnñopqrstuvwxyzáéíóúü";
  wchar_t buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);

    for (size_t i = 0; i < lenString + 1; i++) {
      for (size_t j = lenString + 1; j > i; j--) {
        buff[j] = buff[j - 1];
      }
      for (size_t j = 0; j < 33; j++) {
        buff[i] = abecedario[j];
        cambiosNuevos = slist_agregar_inicio(cambiosNuevos, buff);
      }
      wcscpy(buff, nodo->string);
    }
  }

  return cambiosNuevos;
}

SList metodo_eliminacion(SList cambiosActuales, SList cambiosNuevos) {
  size_t lenString;
  wchar_t buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);

    for (size_t i = 0; i < lenString; i++) {
      for (size_t j = i; j < lenString; j++) {
        buff[j] = buff[j + 1];
      }
      buff[lenString] = L'\0';
      cambiosNuevos = slist_agregar_inicio(cambiosNuevos, buff);
      wcscpy(buff, nodo->string);
    }
  }

  return cambiosNuevos;
}

SList metodo_reemplazo(SList cambiosActuales, SList cambiosNuevos) {
  size_t lenString;
  wchar_t abecedario[] = L"abcdefghijklmnñopqrstuvwxyzáéíóúü";
  wchar_t charBuff, buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);
    for (size_t i = 0; i < lenString; i++) {
      charBuff = buff[i];
      for (size_t j = 0; j < 33; j++) {
        buff[i] = abecedario[j];
        cambiosNuevos = slist_agregar_inicio(cambiosNuevos, buff);
      }
      buff[i] = charBuff;
    }
  }

  return cambiosNuevos;
}

SList metodo_separacion(SList cambiosActuales, SList cambiosNuevos) {
  size_t lenString;
  wchar_t buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL; nodo = nodo->sig) {
    lenString = wcslen(nodo->string);

    for (size_t i = 1; i < lenString; i++) {
      wcsncpy(buff, nodo->string, i);
      buff[i] = L'\0';
      cambiosNuevos = slist_agregar_inicio(cambiosNuevos, buff);
      wcscpy(buff, nodo->string + i);
      cambiosNuevos = slist_agregar_inicio(cambiosNuevos, buff);
    }
  }

  return cambiosNuevos;
}

void corregir_palabra(wchar_t* palabra, TablaHash* diccionario) {
  size_t lenPalabra = wcslen(palabra);
  int caracterEspecialAlFinal = 0;
  wchar_t charFinal = palabra[lenPalabra - 1];
  if (caracter_especial(charFinal)) {
    palabra[lenPalabra - 1] = L'\0';
    caracterEspecialAlFinal++;
  }

  if (!tablahash_contiene(diccionario, palabra)) {
    size_t cantSugerencias = 0, profundidad = 1;
    SList sugerencias = slist_crear();
    SList cambiosActuales = slist_crear(), cambiosNuevos = slist_crear();
    cambiosActuales = slist_agregar_inicio(cambiosActuales, palabra);
 
    while (cantSugerencias < 5 && profundidad < 3) {
      cambiosNuevos = metodo_permutacion(cambiosActuales, cambiosNuevos);
      cambiosNuevos = metodo_insercion(cambiosActuales, cambiosNuevos);
      cambiosNuevos = metodo_eliminacion(cambiosActuales, cambiosNuevos);
      cambiosNuevos = metodo_reemplazo(cambiosActuales, cambiosNuevos);
      cambiosNuevos = metodo_separacion(cambiosActuales, cambiosNuevos);

      for (SNodo *nodo = cambiosNuevos; nodo != NULL; nodo = nodo->sig) {
        if (tablahash_contiene(diccionario, nodo->string) &&
            !slist_contiene(sugerencias, nodo->string)) {
          sugerencias = slist_agregar_inicio(sugerencias, nodo->string);
          cantSugerencias++;
          // wprintf(L"Palabra a corregir: %ls, correción: %ls, profundidad: %d, sugerencia n: %d", palabra, nodo->string, profundidad, cantSugerencias);
          // wprintf(L"\n");
        }
      }

      profundidad++;
      slist_destruir(cambiosActuales);
      cambiosActuales = cambiosNuevos;
      cambiosNuevos = slist_crear();
    }

    slist_destruir(cambiosActuales);
    // salida_archivo(palabra, sugerencias, caracterEspecialAlFinal, charFinal);
    if (sugerencias != NULL) {
      slist_destruir(sugerencias);
    }
  }
}

void corregir_archivo(char* nombreArchivo, TablaHash* diccionario) {
  FILE *archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);

  wchar_t charBuff, strBuff[80];

  for (size_t i = 0; (charBuff = fgetwc(archivo)) != WEOF;) {
    if (charBuff != L' ' && charBuff != L'\n') {
      strBuff[i] = charBuff;
      i++;
    } else {
      strBuff[i] = L'\0';
      i = 0;
      string_minuscula(strBuff);
      corregir_palabra(strBuff, diccionario);
    }
  }

  fclose(archivo);
}

TablaHash* leer_diccionario(char* nombreArchivo) {
  FILE *archivo = fopen(nombreArchivo, "r");
  assert(archivo != NULL);

  TablaHash* diccionario = tablahash_crear(SIZETABLAHASH, hash_polinomico);
  wchar_t buff[80];
  size_t len;

  while (fgetws(buff, 80, archivo) != NULL) {
    len = wcslen(buff);

    // Borrar el salto de línea si tiene.
    if (buff[len-1] == '\n') {
      buff[len-1] = '\0';
      len--;
    }
    string_minuscula(buff);
    tablahash_insertar(diccionario, buff);
  }

  fclose(archivo);

  return diccionario;
}

int main() {
  setlocale(LC_ALL, "");

  TablaHash* diccionario = leer_diccionario("listado-general.txt");
  corregir_archivo("entrada.txt", diccionario);

  tablahash_destruir(diccionario);
  return 0;
}
