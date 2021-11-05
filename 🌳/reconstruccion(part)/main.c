#include "ab.h"
#include <stdio.h>
#include <stdlib.h>

// pre order: EURMAONDVSZT
// in order: MRAUOZSVDNET

/*
EURMAONDVSZT
MRAUOZSVDNET

*/

ab_t* ab_crear(char dato) {
    ab_t* arbol = malloc(sizeof(ab_t));
    arbol->dato = dato;
    arbol->izq = NULL;
    arbol->der = NULL;
    return arbol;
}

ab_t* arbol_con_recorridos() {
    ab_t* t = ab_crear('T');  t->izq = NULL;  t->der = NULL;
    ab_t* z = ab_crear('Z');  z->izq = NULL;  z->der = NULL;
    ab_t* s = ab_crear('S');  s->izq = z;     s->der = NULL;
    ab_t* v = ab_crear('V');  v->izq = s;     v->der = NULL;
    ab_t* d = ab_crear('D');  d->izq = v;     d->der = NULL;
    ab_t* n = ab_crear('N');  n->izq = d;     n->der = NULL;
    ab_t* o = ab_crear('O');  o->izq = NULL;  o->der = n;
    ab_t* a = ab_crear('A');  a->izq = NULL;  a->der = NULL;
    ab_t* m = ab_crear('M');  m->izq = NULL;  m->der = NULL;
    ab_t* r = ab_crear('R');  r->izq = m;     r->der = a;
    ab_t* u = ab_crear('U');  u->izq = r;     u->der = o;
    ab_t* e = ab_crear('E');  e->izq = u;     e->der = t;
    return e;
}

void ab_recorrer_pre_order(ab_t* arbol) {
    if (arbol == NULL) return;
    printf("%c", arbol->dato);
    ab_recorrer_pre_order(arbol->izq);
    ab_recorrer_pre_order(arbol->der);
}

void ab_recorrer_in_order(ab_t* arbol) {
    if (arbol == NULL) return;
    ab_recorrer_in_order(arbol->izq);
    printf("%c", arbol->dato);
    ab_recorrer_in_order(arbol->der);
}

void ab_destruir(ab_t* arbol) {
    if (arbol == NULL) return;
    ab_destruir(arbol->izq);
    ab_destruir(arbol->der);
    free(arbol);
}

int main() {
    ab_t* arbol = arbol_con_recorridos();
    ab_recorrer_pre_order(arbol);
    printf("\n");
    ab_recorrer_in_order(arbol);
    printf("\n");
    ab_destruir(arbol);
    return 0;
}