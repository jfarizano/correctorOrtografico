# correctorOrtografico

Trabajo práctico 2 - Estructuras de Datos y Algoritmos

Realizado por:
Bernal, Pablo - Farizano, Juan Ignacio

### Requisitos para correr el programa:

Los archivos **main.c** y **makefile** se deberán encontrar en
el directorio principal del programa.
Los archivos **bstree.c**, **bstree.h**, **corrector.c**, **corrector.h**,
**slist.c**, **slist.h**, **tablaHash.C** y **tablaHash.c** deberán encontrarse
en el subdirectorio src.

### Sobre los caracteres especiales:
Para poder trabajar con los caracteres que no se encuentran en el código ASCII
(letras con tilde, u con diéresis o ü) se utiliza el tipo de dato wchar_t que se
obtiene de la librería **wchar.h**.

### Sobre el archivo de texto "listado-general.txt":
En este archivo se encuentra nuestro Universo, donde cada palabra
se encuentra separada por un salto de línea (es decir, un caracter \n).

### Sobre el archivo de entrada del programa.
En este archivo se encuentra el texto a corregir, las palabras deberán estar
separadas por un espacio ó un salto de línea.

### Como compilar y correr los programas:
- Para compilar el programa se debe ejecutar en consola el comando "make".

- Para correrlo se debe ejectutar en consola el comando:
"./main.o archivoEntrada archivoSalida"
donde archivoEntrada y archivoSalida son los archivos donde se encuentra el
texto a corregir y donde se encontrarán las correciones respectivamente.
