#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

//Valida que la cantidad ingresada de parámetros sea la correcta
//Además valida que el segundo parámetro sea un entero positivo
//De ir todo correcto devuelve 0, en caso contrario imprime por
//stderr un mensaje de error y devuelve -1
int validar_parametros(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "%s", "Error: Cantidad erronea de parametros\n");
        return -1;
    }
    int columnas = atoi(argv[1]);
    if (columnas <= 0) {
        fprintf(stderr, "%s", "Error: Cantidad erronea de parametros\n");
        return -1;
    }
    return 0;
}

//Dado un path del archivo y un puntero a FILE* abre el archivo
//De ir todo correcto devuelve 0, en caso contrario imprime por
//stderr un mensaje de error y devuelve -1
int open_file(char* name, FILE** archivo) {
    *archivo = fopen(name, "r");
    if (*archivo == NULL) {
        fprintf(stderr, "%s", "Error: archivo fuente inaccesible\n");
        return -1;
    }
    return 0;
}

//Dado un caracter, un puntero a int que señale la columna actual
//en la que se va a imprimir y la cantidad máxima de columnas,
//imprime por sdtout el caracter, de ser necesario agrega un salto
//de línea, y actualiza el valor de col_actual
void printc(int char_leido, int* col_actual, int columnas) {
    if (*col_actual == columnas || char_leido == '\n') {
        fprintf(stdout, "\n");
        *col_actual = 0;
    }
    if (char_leido != '\n') {
        fprintf(stdout, "%c", char_leido);
        *col_actual = *col_actual + 1;
    }
}

//Dado un path a archivo y la cantidad máxima de columnas en las que
//se va a imprimir, imprime por stdout el archivo siendo sus líneas
//del largo establecido (o menor, en el caso en que dicha línea no
//tenga más caracteres para imprimir)
//De ir todo correcto devuelve 0, en caso contrario imprime por
//stderr un mensaje de error y devuelve -1
int fixcol_archivo(char* filename, int columnas) {
    FILE* archivo;
    int val_archivo = open_file(filename, &archivo);
    if (val_archivo == -1) {
        return val_archivo;
    }
    int col_actual = 0;
    int char_leido = fgetc(archivo);
    while(char_leido != EOF) {
        printc(char_leido, &col_actual, columnas);
        char_leido = fgetc(archivo);
    }
    fclose(archivo);
    return 0;
}

//Dada la cantidad máxima de columnas en las que se va a imprimir,
//imprime por stdout el texto recibido por stdin siendo sus líneas
//del largo establecido (o menor, en el caso en que dicha línea no
//tenga más caracteres para imprimir)
//De ir todo correcto devuelve 0, en caso contrario imprime por
//stderr un mensaje de error y devuelve -1
void fixcol_stdin(int columnas) {
    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos = getline(&linea, &capacidad, stdin);
    int col_actual = 0;
    while (leidos > 0) {
        for (size_t i = 0; linea[i] != '\0'; i++) {
            printc(linea[i], &col_actual, columnas);
        }
        leidos = getline(&linea, &capacidad, stdin);
    }
    free(linea);
}



int main(int argc, char* argv[]) {
    int val = validar_parametros(argc, argv);
    if (val == -1) {
        return val;
    }
    int columnas = atoi(argv[1]);

    if (argc == 3) {
        char* filename = argv[2];
        int fixcol_arch = fixcol_archivo(filename, columnas);
        if (fixcol_arch == -1) {
            return fixcol_arch;
        } 
    } else {
        fixcol_stdin(columnas);
    }
    return 0;
}