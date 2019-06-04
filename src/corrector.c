#include "corrector.h"
#include <stdlib.h>
// #include <string.h>
#include <wchar.h>
#include <assert.h>

#define XHASHPOLINOMICO 39
#define SIZETABLAHASH 1999
#define MINCANTSUGERENCIAS 5


 void salida_archivo(wchar_t* palabra, SList sugerencias, 
                     int terminaCharEspecial, wchar_t charFinal, 
                     size_t linea, FILE* archivoSalida) {

  SNodo* nodo = sugerencias;
  fwprintf(archivoSalida, L"LINEA %lu, \"%ls\" no está en el diccionario.\n", 
            linea, palabra);      
  fwprintf(archivoSalida, L"Quizás quiso decir: ");                    
  for (; nodo->sig != NULL; nodo = nodo->sig) {
    fwprintf(archivoSalida, L"%ls, ", nodo->string);
  }
  fwprintf(archivoSalida, L"%ls.\n\n", nodo->string);
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

size_t hash_polinomico(wchar_t* string) {
  size_t clave = 0, len = wcslen(string);

  for (size_t i = 0; i < len; i++) {
    clave = XHASHPOLINOMICO * (string[i] + clave);
  }

  return clave % SIZETABLAHASH;
}



int caracter_especial(wchar_t charFinal) {
  if (charFinal == 58 || charFinal == 59 || charFinal == 44 || 
      charFinal == 46 || charFinal == 63 || charFinal == 33)  {
    return 1;
  }
  return 0;
}

int continuar(size_t cantSugerencias, size_t profundidad) {
  return cantSugerencias < MINCANTSUGERENCIAS || profundidad == 1;
}

// int continuar(size_t cantSugerencias, size_t profundidad) {
//   return (cantSugerencias < MINCANTSUGERENCIAS && profundidad <= 2) || 
//           profundidad == 1;
// }

void comprobar_sugerencia(TablaHash* diccionario, SList* sugerencias, 
                          size_t* cantSugerencias, wchar_t* sugerencia) {

  if (tablahash_contiene(diccionario, sugerencia) && 
      !slist_contiene(*sugerencias, sugerencia)) {
    *sugerencias = slist_agregar_inicio(*sugerencias, sugerencia);
    (*cantSugerencias)++;
  }                            
}

void metodo_permutacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad) {

  if (!continuar(*cantSugerencias, *profundidad)) {
    return;
  }

  size_t lenString;
  wchar_t charBuff, strBuff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && 
        continuar(*cantSugerencias, *profundidad); nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(strBuff, nodo->string);

    for (size_t i = 0; i < lenString - 1 && 
          continuar(*cantSugerencias, *profundidad); i++) {
      if (strBuff[i] != strBuff[i + 1]) {
        charBuff = strBuff[i];
        strBuff[i] = strBuff[i + 1];
        strBuff[i + 1] = charBuff;
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, strBuff);
        comprobar_sugerencia(diccionario, sugerencias, cantSugerencias, 
                              strBuff);                     
        strBuff[i + 1] = strBuff[i];
        strBuff[i] = charBuff;
      }
    }
  }
}

void metodo_insercion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad) {

  if (!continuar(*cantSugerencias, *profundidad)) {
    return;
  }   

  size_t lenString;
  wchar_t abecedario[] = L"abcdefghijklmnñopqrstuvwxyzáéíóúü";
  wchar_t buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && 
      continuar(*cantSugerencias, *profundidad); nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);

    for (size_t i = lenString + 1; i > 0; i--) {
        buff[i] = buff[i - 1];
    }

    for (size_t i = 0; i < lenString + 1 && 
          continuar(*cantSugerencias, *profundidad); i++) {

      for (size_t j = 0; j < 33 && 
            continuar(*cantSugerencias, *profundidad); j++) {
        buff[i] = abecedario[j];
        *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, buff);
        comprobar_sugerencia(diccionario, sugerencias, cantSugerencias, 
                              buff);
      }
      buff[i] = buff[i + 1];
    }
  }
}

void metodo_eliminacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad) {

  if (!continuar(*cantSugerencias, *profundidad)) {
    return;
  } 
                            
  size_t lenString;
  wchar_t buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && 
        continuar(*cantSugerencias, *profundidad); nodo = nodo->sig) {
    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);

    for (size_t i = 0; i < lenString && 
          continuar(*cantSugerencias, *profundidad); i++) {
      for (size_t j = i; j < lenString; j++) {
        buff[j] = buff[j + 1];
      }
      *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, buff);
      comprobar_sugerencia(diccionario, sugerencias, cantSugerencias, 
                              buff);                       
      wcscpy(buff, nodo->string);
    }
  }
}

void metodo_reemplazo(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad) {

  if (!continuar(*cantSugerencias, *profundidad)) {
    return;
  }      
  
  size_t lenString;
  wchar_t abecedario[] = L"abcdefghijklmnñopqrstuvwxyzáéíóúü";
  wchar_t charBuff, buff[80];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && 
        continuar(*cantSugerencias, *profundidad); nodo = nodo->sig) {

    lenString = wcslen(nodo->string);
    wcscpy(buff, nodo->string);

    for (size_t i = 0; i < lenString; i++) {
      charBuff = buff[i];
      for (size_t j = 0; j < 33 && 
            continuar(*cantSugerencias, *profundidad); j++) {
        if (buff[i] != abecedario[j]) {
          buff[i] = abecedario[j];
          *cambiosNuevos = slist_agregar_inicio(*cambiosNuevos, buff);
          comprobar_sugerencia(diccionario, sugerencias, cantSugerencias, 
                              buff);
        }
      }
      buff[i] = charBuff;
    }
  }
}

void metodo_separacion(TablaHash* diccionario, SList cambiosActuales, 
                          SList* cambiosNuevos, SList* sugerencias, 
                          size_t* cantSugerencias, size_t* profundidad) {

  if (!continuar(*cantSugerencias, *profundidad) || *profundidad > 1) {
    return;
  }

  size_t lenString;
  wchar_t buff1[80], buff2[40];

  for (SNodo *nodo = cambiosActuales; nodo != NULL && 
      continuar(*cantSugerencias, *profundidad); nodo = nodo->sig) {
    lenString = wcslen(nodo->string);

    for (size_t i = 1; i < lenString && 
          continuar(*cantSugerencias, *profundidad); i++) {
      wcsncpy(buff1, nodo->string, i);
      buff1[i] = L'\0';
      wcscpy(buff2, nodo->string + i);
      
      if (tablahash_contiene(diccionario, buff1) && 
          tablahash_contiene(diccionario, buff2)) {
        buff1[i] = L' ';
        buff1[i + 1] = L'\0';
        wcscat(buff1, buff2);
        *sugerencias = slist_agregar_inicio(*sugerencias, buff1);
        (*cantSugerencias)++;
      }
    }
  }
}

void corregir_palabra(wchar_t* palabra, TablaHash* diccionario, 
                      size_t linea, FILE* archivoSalida) {

  size_t lenPalabra = wcslen(palabra);
  int terminaCharEspecial = 0;
  wchar_t charFinal = palabra[lenPalabra - 1];
  if (caracter_especial(charFinal)) {
    palabra[lenPalabra - 1] = L'\0';
    terminaCharEspecial++;
  }

  if (!tablahash_contiene(diccionario, palabra)) {
    size_t cantSugerencias = 0, profundidad = 1;
    SList sugerencias = slist_crear();
    SList cambiosActuales = slist_crear(), cambiosNuevos = slist_crear();
    cambiosActuales = slist_agregar_inicio(cambiosActuales, palabra);
 
    while (continuar(cantSugerencias, profundidad)) {
      metodo_permutacion(diccionario, cambiosActuales, &cambiosNuevos, 
                          &sugerencias, &cantSugerencias, &profundidad);
      metodo_insercion(diccionario, cambiosActuales, &cambiosNuevos, 
                        &sugerencias, &cantSugerencias, &profundidad);
      metodo_eliminacion(diccionario, cambiosActuales, &cambiosNuevos, 
                          &sugerencias, &cantSugerencias, &profundidad);
      metodo_reemplazo(diccionario, cambiosActuales, &cambiosNuevos, 
                        &sugerencias, &cantSugerencias, &profundidad);
      metodo_separacion(diccionario, cambiosActuales, &cambiosNuevos, 
                          &sugerencias, &cantSugerencias, &profundidad);

      profundidad++;
      slist_destruir(cambiosActuales);
      cambiosActuales = cambiosNuevos;
      cambiosNuevos = slist_crear();
    }

    slist_destruir(cambiosActuales);
    salida_archivo(palabra, sugerencias, terminaCharEspecial, 
                    charFinal, linea, archivoSalida);
    if (sugerencias != NULL) {
      slist_destruir(sugerencias);
    }
  }
}


void corregir_archivo(char* nombreArchivoEntrada, char* nombreArchivoSalida, 
                        TablaHash* diccionario) {

  FILE *archivoEntrada = fopen(nombreArchivoEntrada, "r");
  FILE *archivoSalida = fopen(nombreArchivoSalida, "w");
  assert(archivoEntrada != NULL);

  wchar_t charBuff, strBuff[80];

  for (size_t i = 0, linea = 1; (charBuff = fgetwc(archivoEntrada)) != WEOF;) {
    if (charBuff != L' ' && charBuff != L'\n') {
      strBuff[i] = charBuff;
      i++;
    } else {   
      strBuff[i] = L'\0';
      i = 0;
      if (wcslen(strBuff) != 0) {
        string_minuscula(strBuff);
        corregir_palabra(strBuff, diccionario, linea, archivoSalida);
      }
      if (charBuff == L'\n') {
        linea++;
      }
    }
  }

  fclose(archivoEntrada);
  fclose(archivoSalida);
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


