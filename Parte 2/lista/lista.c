#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


/* Definición del struct nodo */
typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

/* *****************************************************************
 *                        PRIMITIVAS DEL NODO
 * *****************************************************************/

nodo_t* nodo_crear(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL) {
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t* nodo, void (*destruir_dato)(void *)) {
    if (destruir_dato != NULL) {
        destruir_dato(nodo->dato);
    }
    free(nodo);
}



/* Definición del struct lista */
typedef struct lista {
	struct nodo* prim;
    struct nodo* ult;
	size_t largo;
} lista_t;

/* *****************************************************************
 *                       PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(void) {
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL) {
        return NULL;
    }
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista) {
    if (lista->largo == 0) {
        return true;
    }
    return false;
}

bool lista_insertar_primero(lista_t* lista, void* dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) {
        return false;
    }
    
    if (lista_esta_vacia(lista)) {
        lista->prim = nodo;
        lista->ult = nodo;
        lista->largo++;
        return true;
    }
    nodo_t* ant_prim = lista->prim;
    lista->prim = nodo;
    lista->prim->prox = ant_prim;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato) {
    if (lista_esta_vacia(lista)) {
        return lista_insertar_primero(lista, dato);
    }
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) {
        return false;
    }
    lista->ult->prox = nodo;
    lista->ult = nodo;
    lista->largo++;
    return true;
}

void* lista_borrar_primero(lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    nodo_t* segundo = lista->prim->prox;
    void* dato_prim = lista->prim->dato;
    nodo_destruir(lista->prim, NULL);
    lista->prim = segundo;
    lista->largo--;
    return dato_prim;
}

void* lista_ver_primero(const lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    nodo_t* primero = lista->prim;
    return primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    nodo_t* ultimo = lista->ult;
    return ultimo->dato;   
}

size_t lista_largo(const lista_t* lista) {
    return lista->largo;
}

void lista_destruir(lista_t* lista, void (*destruir_dato)(void *)) {
    if(lista_esta_vacia(lista)) {
        free(lista);
        return;
    }
    nodo_t* actual = lista->prim;
    while(!lista_esta_vacia(lista)) {
        nodo_t* prox = actual->prox;
        nodo_destruir(actual, destruir_dato);
        actual = prox;
        lista->largo--;
    }
    free(lista);
}


/* *****************************************************************
 *                 PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra) {
    nodo_t* actual = lista->prim;
    while (actual) {
        if (!visitar(actual->dato, extra)) {
            return;
        }
        actual = actual->prox;
    }
}



/* Definición del struct lista_iter */
typedef struct lista_iter {
	lista_t* lista;
	struct nodo* act;
	struct nodo* ant;
} lista_iter_t;

/* *****************************************************************
 *                 PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t* lista_iter_crear(lista_t* lista) {
    lista_iter_t* iterador = malloc(sizeof(lista_iter_t));

    if (iterador == NULL) {
        return NULL;
    }
    iterador->lista = lista;
    iterador->act = lista->prim;
    iterador->ant = NULL;
    return iterador;
}

bool lista_iter_avanzar(lista_iter_t* iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
        return false;
    }
    iter->ant = iter->act;
    iter->act = iter->act->prox;
    return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
        return NULL;
    }
    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter) {
    return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t* iter) {
    free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato) {
    if (lista_esta_vacia(iter->lista) || iter->ant == NULL) {
        lista_insertar_primero(iter->lista, dato);
        iter->act = iter->lista->prim;
        return true;
    }
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) {
        return false;
    }
    iter->ant->prox = nodo;
    nodo->prox = iter->act;
    iter->act = nodo;
    iter->lista->largo++;
    if (iter->act->prox == NULL) {
        iter->lista->ult = nodo;
    }
    return true;
}

void* lista_iter_borrar(lista_iter_t* iter) {
    if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) {
        return NULL;
    }
    if (iter->ant == NULL) {
        void* dato = lista_borrar_primero(iter->lista);
        iter->act = iter->lista->prim;
        return dato;
    }
    if (iter->act->prox == NULL) {
        iter->lista->ult = iter->ant;
    }
    nodo_t* prox = iter->act->prox;
    iter->ant->prox = prox;
    void* dato_act = iter->act->dato;
    nodo_destruir(iter->act, NULL);
    iter->act = prox;
    iter->lista->largo--;
    return dato_act;
}
