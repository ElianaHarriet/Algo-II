// Implementar la función void** cola_multiprimeros(cola_t* cola, size_t k) que
// dada una cola y un número k, devuelva los primeros k elementos de la cola, en
// el mismo orden en el que habrían salido de la cola. En caso que la cola tenga
// menos de kk elementos, rellenar con NULL. Indicar y justificar el orden de
// ejecución del algoritmo.
#include "cola.h"
#include "cola_multi.h"

void** cola_multiprimeros(cola_t* cola, size_t k) {
    cola_t* aux = cola_crear();
    int len = 0;
    while (!cola_esta_vacia(cola)) {
        cola_encolar(aux, cola_desencolar(cola));
        len++;
    }

    void** multi = malloc(sizeof(void*) * k);
    void* val;
    for (int i = 0; i < len; i++) {
        val = cola_desencolar(aux);
        cola_encolar(cola, val);
        if (i < k) {
            multi[i] = val;
        }
    }
    
    for (int j = len; j < k; j++) {
        multi[j] = NULL;
    }
    return multi;
} // Siendo k los primeros k-elementos de la cola y n la cantidad total de elementos en la cola
// Si k << n -> T(k, n) = O(k) + O(n) = O(n)
// Si k >> n -> T(k, n) = O(k) + O(n) + O(k - n) = 2.O(k) = O(k)
// Si k == n -> T(k, n) = O(k) + O(n) = 2.O(k) = O(k)
//                                    = 2.O(n) = O(n)  