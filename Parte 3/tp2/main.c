#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algogram.h"



void maquina(algo_gram_t* gram) {
    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos = getline(&linea, &capacidad, stdin);
    linea[strlen(linea) - 1] = '\0';

    while (leidos > 0) {     // leidos > 0, porque si es 0, es porque se acabó la operacion
        
        if (strcmp("login", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* nombre = linea;
            login(gram, get_usuarios(gram), nombre);

        } else if (strcmp("logout", linea) == 0) {
            logout(gram);

        } else if (strcmp("publicar", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* texto = linea;
            publicar(gram, texto);

        } else if (strcmp("likear_post", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* id = linea;
            dar_like(gram, id);

        } else if (strcmp("mostrar_likes", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* id = linea;
            mostrar_likes(gram, id);

        } else if (strcmp("ver_siguiente_feed", linea) == 0) {
            ver_posts(gram);
        } else {
            fprintf(stdout, "%s", "Error: Comando invalido\n");
        }

        leidos = getline(&linea, &capacidad, stdin);
        linea[strlen(linea) - 1] = '\0';
        }

    free(linea);
    algo_gram_destruir(gram);
}


algo_gram_t* manejo_errores(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stdout, "%s", "Error: Cantidad de argumentos invalida\n");
        return NULL;
    }
    algo_gram_t* gram = algo_gram_crear(argv[1]);
    if (gram == NULL) {
        algo_gram_destruir(gram);
        fprintf(stdout, "%s", "Error: No se pudo crear el algo_gram\n");
        return NULL;
    }
    if (!get_usuarios(gram)) {
        algo_gram_destruir(gram);
        fprintf(stdout, "%s", "Error: No se pudo cargar los usuarios\n");
        return NULL;
    }
    return gram;
}


int main(int argc, char* argv[]) {
    algo_gram_t* gram = manejo_errores(argc, argv);
    if (gram == NULL) {
        return -1;}
    maquina(gram);
}