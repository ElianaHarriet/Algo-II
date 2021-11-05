#include "pila.h"

#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void) {
    pila_t* pila = malloc(sizeof(pila_t));

    if (pila == NULL) {
        return NULL;
    }
    pila->datos = malloc(15 * sizeof(void*));

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->capacidad = 15;
    pila->cantidad = 0;
    return pila;
}

void pila_destruir(pila_t* pila) {
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t* pila) {
    return pila->cantidad == 0;
}

bool _pila_redimensionar(pila_t* pila, size_t tam_nuevo) {
    void** aux = realloc(pila->datos, tam_nuevo * sizeof(void*));
    
    if (aux == NULL) {
        return false;
    }
    pila->datos = aux;
    pila->capacidad = tam_nuevo;
    return true;
}

bool pila_apilar(pila_t* pila, void* valor) {
    if (pila->cantidad == pila->capacidad) {
        bool redimensionar = _pila_redimensionar(pila, pila->capacidad * 2);

        if (!redimensionar) {
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void* pila_ver_tope(const pila_t* pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    return pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t* pila) {
    if (pila_esta_vacia(pila)) {
        return NULL;
    }
    void* tope = pila->datos[pila->cantidad - 1];
    pila->cantidad--;
    if (pila->cantidad * 4 <= pila->capacidad && pila->capacidad > 15) {
        bool redimensionar;
        do {
            redimensionar = _pila_redimensionar(pila, pila->capacidad / 2);
        } while (!redimensionar);
    }
    return tope;
}
