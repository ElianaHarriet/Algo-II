// Implementar una función que ordene de manera ascendente una pila de enteros sin conocer
// su estructura interna y utilizando como estructura auxiliar sólo otra pila auxiliar.
// Por ejemplo, la pila [ 4, 1, 5, 2, 3 ] debe quedar como [ 1, 2, 3, 4, 5 ] (siendo el
// último elemento el tope de la pila, en ambos casos). Indicar y justificar el orden de
// la función.
#include "pila.h"

void ordenar_pila(pila_t* pila) {
    pila_t* aux = pila_crear();
    while (!pila_esta_vacia(pila)) {
        void* elemento = pila_desapilar(pila);
        while (!pila_esta_vacia(aux) && *(int*)pila_ver_tope(aux) < *(int*)elemento) {
            pila_apilar(pila, pila_desapilar(aux));
        }
        pila_apilar(aux, elemento);
    }
    while (!pila_esta_vacia(aux)) {
        pila_apilar(pila, pila_desapilar(aux));
    }
}