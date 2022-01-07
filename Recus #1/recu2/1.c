// 1. Dada la siguiente estructura de lista, implementar una primitiva bool lista_repetir_elementos(lista_t* lista)
// que para cada elemento presente en la lista genere un nuevo elemento repetido justo a su lado.
// Ejemplo: para la siguiente lista, donde A, B y C son los datos de Bárbara: A -> B -> C
// el resultado esperado es: A -> A -> B -> B -> C -> C
// La primitiva devuelve true si la operción fue un éxito, false en caso contrario.
typedef struct nodo_lista {
    struct nodo_lista* prox;
    void* dato;
} nodo_lista_t;

typedef struct lista {
    nodo_lista_t* prim;
} lista_t;
// Indicar y justificar la complejidad de la primitiva implementada.
#include <stdlib.h>
#include <stdbool.h>

nodo_lista_t* nodo_crear(void* dato) {
    nodo_lista_t* nodo = malloc(sizeof(nodo_lista_t));

    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}    

bool lista_repetir_elementos(lista_t* lista) {
    nodo_lista_t* nodo_actual = lista->prim;
    nodo_lista_t* nodo_nuevo;
    bool duplicar = true;
    while (nodo_actual != NULL) {
        if (duplicar) {
            nodo_nuevo = nodo_crear(nodo_actual->dato);
            if (nodo_nuevo == NULL) {
                return false;
            }

            nodo_nuevo->prox = nodo_actual->prox;
            nodo_actual->prox = nodo_nuevo;
        }
        nodo_actual = nodo_actual->prox;
        duplicar = !duplicar;
    }
    return true;
}

/* {Orden de la primitiva} *
 * La primitiva lista_repetir_elementos() tiene una complejidad de O(n)
 * donde n es el largo de la lista. Ya que se recorre la lista completa
 * y durante el recorrido se crean los nodos necesarios O(1) y se
 * actualizan los punteros entre nodos de la lista O(1).
 * n * O(1) -> O(n)
 */