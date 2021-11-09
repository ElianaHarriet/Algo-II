#ifndef ABB_STRUCT_H
#define ABB_STRUCT_H
#include "abb.h"

/* Los structs deben llamarse 'abb' y 'abb_iter'. */
typedef struct abb_nodo {
    struct abb_nodo *izq;
    struct abb_nodo *der;
    char *clave;
    void *dato;
} abb_nodo_t;

struct abb {
    abb_nodo_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
};

#endif