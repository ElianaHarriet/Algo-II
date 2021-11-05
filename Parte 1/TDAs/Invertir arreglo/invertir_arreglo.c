// Implementar una función que reciba un arreglo de void* e invierta su
// orden, utilizando los TDAs vistos. Indicar y justificar el orden de
// ejecución.
#include <stddef.h> 
#include "invertir_arreglo.h"
#include "pila.h"

void invertir_arreglo(void** arreglo, size_t n) {
    pila_t* pila = pila_crear();
    for (size_t i = 0; i < n; i++) {
        pila_apilar(pila, arreglo[i]);
    }
    for (size_t i = 0; i < n; i++) {
        arreglo[i] = pila_desapilar(pila);
    }
    pila_destruir(pila);
} // T(n) = 2 O(n) = O(n)
