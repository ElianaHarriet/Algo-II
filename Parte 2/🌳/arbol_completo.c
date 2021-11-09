#include <stdlib.h>
#include <stdbool.h>
#include "abb_struct.h"
#include <math.h>

size_t abb_altura(const abb_nodo_t* abb) {
    if (abb == NULL) {
        return 0;
    }
    size_t alt_der = abb_altura(abb->der);
    size_t alt_izq = abb_altura(abb->izq);
    return (alt_der > alt_izq ? alt_der : alt_izq) + 1;
}

size_t nodos(const abb_nodo_t* abb) {
    if (abb == NULL) {
        return 0;
    }
    size_t der = nodos(abb->der);
    size_t izq = nodos(abb->izq);
    return der + izq + 1;
}

size_t cant_completo(size_t altura) {
    size_t cant = 0;
    for (double i = 0; i < altura; i++) {
        cant += (size_t)pow(2.0, i);
    }
    return cant;
}

bool abb_completo(const abb_t *arbol){
    size_t altura = abb_altura(arbol->raiz);
    size_t cant_nodos = nodos(arbol->raiz);
    size_t completo = cant_completo(altura);
    return cant_nodos == completo;
}