#ifndef HASH_STRUCT_H
#define HASH_STRUCT_H

#include "hash.h"

/* Estructura para almacenar clave, valor */
typedef struct hash_nodo {
    char *clave;
    void *valor;
} hash_nodo_t;

/* Estructura del hash: arreglo de punteros a lista. */
struct hash {
    lista_t **tabla;
    size_t cantidad;
    size_t largo;
    hash_destruir_dato_t destruir_dato;
};

/* Estructura del iterador. */
struct hash_iter {
    const hash_t *hash;
    size_t indice;
    lista_iter_t *iter_actual;
};

#endif