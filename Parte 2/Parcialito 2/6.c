// Dado un árbol binario que tiene como datos números enteros, implementar una primitiva que reemplace el valor de todos
// los nodos del árbol de manera tal que cada nodo X tenga como valor la cantidad de nodos que existen en la sub-rama
// de ese nodo X. En otras palabras, para cada nodo el valor resultante representa su cantidad de hijos, nietos, bis-nietos,
// bis-bis-nietos, etc. Ayuda: para la raíz, este valor es igual a la cantidad de elementos en el árbol, menos 1. Para las hojas,
// el valor es de 0, ya que no tiene descendientes. ¿Cuál es el orden de la primitiva implementada? ¿Qué tipo de recorrido
// utilizaste? La estructura de cada nodo es la siguiente:
#include <stdio.h>
#include <stdlib.h>

typedef struct ab {
    int valor;
    struct ab* izq;
    struct ab* der
} ab_t;

void _reemplazar(ab_t* arbol) {
    if (arbol == NULL) {
        return;
    }
    
    int izq = arbol->izq == NULL ? 0 : arbol->izq->valor + 1;
    int der = arbol->der == NULL ? 0 : arbol->der->valor + 1;
    arbol->valor = izq + der;
}

void reemplazar(ab_t* arbol) {
    _reemplazar(arbol->izq);
    _reemplazar(arbol->der);
    _reemplazar(arbol);
}

/* •{Orden de la primitiva}•
 * El orden de la primitiva es O(n), siendo n la cantidad de nodos
 * que tiene el árbol.
 * Se debe a que el reemplazo hay que hacerlo en todos los nodos del
 * árbol.
 * 
 * •{Tipo de recorrido}•
 * El tipo de recorrido utilizado es postorder debido a que se va
 * reemplazando el valor desde las hojas hasta la raíz.
 * Esto es así debido a que se va usando el valor que tiene cada hijo
 * para calcular el valor de su padre, hasta llegar a la raíz.
 */
static void _ab_nodo_imprimir(const ab_t *nodo, size_t nivel) {
    if (!nodo)
        return;

    int hijo_izq = nodo->izq ? nodo->izq->valor : -1;
    int hijo_der = nodo->der ? nodo->der->valor : -1;

    printf(
        "DEBUG IMPRIMIR: nivel %zu -- actual %i, hijo izq: %i, hijo der: %i \n",
        nivel, nodo->valor, hijo_izq, hijo_der);

    _ab_nodo_imprimir(nodo->izq, nivel + 1);
    _ab_nodo_imprimir(nodo->der, nivel + 1);
}


void ab_imprimir(const ab_t *arbol) {
    if (!arbol)
        return;
    _ab_nodo_imprimir(arbol, 1);
}

int main() {
    ab_t* a = malloc(sizeof(ab_t));
    ab_t* b = malloc(sizeof(ab_t));
    ab_t* c = malloc(sizeof(ab_t));
    ab_t* d = malloc(sizeof(ab_t));
    ab_t* e = malloc(sizeof(ab_t));
    ab_t* f = malloc(sizeof(ab_t));
    ab_t* g = malloc(sizeof(ab_t));
    ab_t* h = malloc(sizeof(ab_t));
    ab_t* i = malloc(sizeof(ab_t));
    ab_t* j = malloc(sizeof(ab_t));
    ab_t* k = malloc(sizeof(ab_t));

    a->izq = b;     a->der = c;     a->valor = 10;
    b->izq = d;     b->der = e;     b->valor = 20;
    c->izq = f;     c->der = g;     c->valor = 30;
    d->izq = h;     d->der = i;     d->valor = 40;
    e->izq = j;     e->der = k;     e->valor = 50;
    f->izq = NULL;  f->der = NULL;  f->valor = 60;
    g->izq = NULL;  g->der = NULL;  g->valor = 70;
    h->izq = NULL;  h->der = NULL;  h->valor = 80;
    i->izq = NULL;  i->der = NULL;  i->valor = 90;
    j->izq = NULL;  j->der = NULL;  j->valor = 100;
    k->izq = NULL;  k->der = NULL;  k->valor = 110;
    
    // ab_imprimir(a);
    reemplazar(a);
    ab_imprimir(a);
    
    
    return 0;
}