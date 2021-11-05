// Implementar la primitiva void** cola_multiprimeros(const cola_t* cola, size_t k)
// que dada una cola y un número k, devuelva los primeros k elementos de la cola,
// en el mismo orden en el que habrían salido de la cola. En caso que la cola tenga
// menos de kk elementos, rellenar con NULL.
// Indicar y justificar el orden de ejecución del algoritmo.
#include "cola.h"
#include "cola_struct.h"
#include <stdlib.h>

void** cola_multiprimeros(const cola_t* cola, size_t k) {
    void** multi = malloc(sizeof(void*) * k);

    nodo_t* nodo = cola->prim;
    for (int i = 0; i < k; i++) {
        if (nodo != NULL) {
            multi[i] = nodo->dato;
            nodo = nodo->sig;
        } else {
            multi[i] = NULL;
        }
    }
    return multi;
} // T(k) = O(k)
