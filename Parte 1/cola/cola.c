#include "cola.h"
#include <stdlib.h>

/* Definición del struct nodo */
typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

/* *****************************************************************
 *                        PRIMITIVAS DEL NODO
 * *****************************************************************/

nodo_t* nodo_crear(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t* nodo, void (*destruir_dato)(void *)) {
    if (destruir_dato != NULL) {
        destruir_dato(nodo->dato);
    }
    free(nodo);
}

/* Definición del struct cola */
struct cola {
    nodo_t* primero;
    nodo_t* ultimo;
};

/* *****************************************************************
 *                       PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {
    cola_t* cola = malloc(sizeof(cola_t));

    if (cola == NULL) {
        return NULL;
    }
    cola->primero = NULL;
    cola->ultimo = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t* cola) {
    return cola->primero == NULL;
}

bool cola_encolar(cola_t* cola, void* valor) {
    nodo_t* nodo = nodo_crear(valor);
    if (nodo == NULL) {
        return false;
    }

    if (cola_esta_vacia(cola)) {
        cola->primero = nodo;
    } else {
        cola->ultimo->prox = nodo;
    }
    cola->ultimo = nodo;
    return true;
}

void* cola_ver_primero(const cola_t* cola) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    return cola->primero->dato;
}

void* _cola_desencolar(cola_t* cola, void (*destruir_dato)(void *)) {
    if (cola_esta_vacia(cola)) {
        return NULL;
    }
    nodo_t* nodo = cola->primero;
    void* dato = nodo->dato;
    cola->primero = nodo->prox;
    nodo_destruir(nodo, destruir_dato);
    if (cola->primero == NULL) {
        cola->ultimo = NULL;
    }
    return dato;
}

void* cola_desencolar(cola_t* cola) {
    return _cola_desencolar(cola, NULL);
}

void cola_destruir(cola_t* cola, void (*destruir_dato)(void *)) {
    while (!cola_esta_vacia(cola)) {
        _cola_desencolar(cola, destruir_dato);
    }
    free(cola);
}
