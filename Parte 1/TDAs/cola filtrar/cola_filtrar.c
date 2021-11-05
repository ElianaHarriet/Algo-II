// Implementar una función void cola_filtrar(cola_t* cola, bool (*filtro)(void*)),
// que elimine los elementos encolados para los cuales la función filtro devuelve false.
// Aquellos elementos que no son eliminados deben permanecer en el mismo orden en el que
// estaban antes de invocar a la función. No es necesario destruir los elementos que sí
// fueron eliminados. Se pueden utilizar las estructuras auxiliares que se consideren
// necesarias y no está permitido acceder a la estructura interna de la cola (es una
// función). ¿Cuál es el orden del algoritmo implementado?
#include "cola.h"
#include <stdlib.h>

void cola_filtrar(cola_t* cola, bool (*filtro)(void*)) {
    cola_t* aux = cola_crear();
    while (!cola_esta_vacia(cola)) { 
        cola_encolar(aux, cola_desencolar(cola));
    }
    void * val;
    while (!cola_esta_vacia(aux)) {
        val = cola_desencolar(aux);
        if (filtro(val)) {
            cola_encolar(cola, val); 
        }
    }
    cola_destruir(aux, NULL); 
} // Siendo n la cantidad de elementos en la cola -> T(n) = O(n)