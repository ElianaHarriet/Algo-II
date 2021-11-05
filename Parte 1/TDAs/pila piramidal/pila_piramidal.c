// Dada una pila de punteros a enteros, escribir una función que determine si es piramidal.
// Una pila de enteros es piramidal si cada elemento es menor a su elemento inferior (en el
// sentido que va desde el tope de la pila hacia el otro extremo).
// La pila no debe ser modificada.
// #include "main.h" // No borrar
#include "pila.h"
#include <stdlib.h>

bool pila_es_piramidal(pila_t* pila) {
    pila_t* aux = pila_crear();
    while(!pila_esta_vacia(pila)) {
        pila_apilar(aux, pila_desapilar(pila));
    }
    bool pira = true;
    while(!pila_esta_vacia(aux)) {
        pila_apilar(pila, pila_desapilar(aux));
        if (!pila_esta_vacia(aux) && !pila_esta_vacia(pila) && *(int*)pila_ver_tope(aux) >= *(int*)pila_ver_tope(pila)) {
            pira = false;
        }
    }
    return pira;
} // Siendo n la cantidad de elementos de la pila
// T(n) = 2.O(n) = O(n)
