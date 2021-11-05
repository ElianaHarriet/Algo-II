// Dada una lista enlazada implementada con las siguientes estructuras:

// typedef struct nodo {
//     void *dato;
//     struct nodo *prox;
// } nodo_t;

// struct lista {
//     nodo_t *primero;
// };

// Escribir una primitiva que reciba una lista y devuelva el elemento que esté a k
// posiciones del final (el ante-k-último), recorriendo la lista una sola vez y sin
// usar estructuras auxiliares. Considerar que k es siempre menor al largo de la lista.
// Por ejemplo, si se recibe la lista [ 1, 5, 10, 3, 6, 8 ], y k = 4, debe devolver 10.
// Indicar el orden de complejidad de la primitiva.
#include "lista.h"
#include "lista_struct.h"

void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
    nodo_t* n_act = lista->primero;
    nodo_t* n_prox = lista->primero;
    for (size_t i = 0; i < k; i++) {
        n_act = n_act->prox;
    }
    while(n_act) {
        n_act = n_act->prox;
        n_prox = n_prox->prox;
    }
    return n_prox->dato;
}



// size_t lista_largo(const lista_t *lista) {
//     nodo_t* nodo = lista->primero;
//     if (!nodo) {
//         return 0;
//     }
//     size_t lar = 1;
//     while (nodo->prox != NULL) {
//         nodo = nodo->prox;
//         lar++;
//     }
//     return lar;
// }

// void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
//     size_t lar = lista_largo(lista);
//     size_t pos = lar - k;
//     nodo_t* nodo = lista->primero;
//     for (int i = 0; i < pos; i++) {
//         nodo = nodo->prox;
//     }
//     return nodo->dato;
// }
