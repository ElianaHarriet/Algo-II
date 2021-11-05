// Implementar en C el TDA ComposiciónFunciones que emula la composición de funciones
// (i.e. f(g(h(x))). Se debe definir la estructura del TDA, y las siguientes primitivas:

// composicion_t* composicion_crear();
// void composicion_destruir(composicion_t*);
// bool composicion_agregar_funcion(composicion_t*, double (*f)(double));
// double composicion_aplicar(composicion_t*, double);

// Considerar que primero se irán agregando las funciones como se leen, pero tener
// en cuenta el correcto orden de aplicación. Por ejemplo: para emular f(g(x)), se
// debe hacer:
// composicion_agregar_funcion(composicion, f);
// composicion_agregar_funcion(composicion, g);
// composicion_aplicar(composicion, x);
// Indicar el orden de las primitivas.
#include "composicion_funciones.h"
#include <stdlib.h>
#include "pila.h"

// Agregar #include <tda.h> dependiendo del tda que necesites 

struct composicion {
    pila_t* pila;
};

composicion_t* composicion_crear() {
    composicion_t* comp = malloc(sizeof(composicion_t));

    if (comp == NULL) {
        return NULL;
    }
    pila_t* pila = pila_crear();
    
    if (pila == NULL) {
        return NULL;
    }
    comp->pila = pila;
    return comp;
}

void composicion_destruir(composicion_t* composicion) {
    pila_destruir(composicion->pila);
    free(composicion);
}

bool composicion_agregar_funcion(composicion_t* composicion, funcion_t f) {
    return pila_apilar(composicion->pila, f);
}

double composicion_aplicar(composicion_t* composicion, double x) {
    funcion_t f;
    while (!pila_esta_vacia(composicion->pila)) {
        f = pila_desapilar(composicion->pila);
        x = f(x);
    }
    return x;
}