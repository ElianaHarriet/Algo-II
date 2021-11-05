// Implementar en C una primitiva void lista_invertir(lista_t* lista) que invierta
// la lista recibida por parámetro, sin utilizar estructuras auxiliares. Indicar y
// justificar el orden de la primitiva.
#include "lista.h"
#include "lista_struct.h"

void lista_invertir(lista_t* lista) {
    nodo_t* anterior = NULL;
    nodo_t* actual = lista->primero;
    if(!actual || !actual->prox) {
        return;
    }
    nodo_t* proximo = actual->prox;
    while (actual) {
        actual->prox = anterior;
        if (proximo) {
            anterior = actual;
            actual = proximo;
            proximo = proximo->prox;
        } else {
            lista->primero = actual;
            return;
        }
    }
}