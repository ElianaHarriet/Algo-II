#define _POSIX_C_SOURCE 200809L  // For strdup().

#include "abb.h"
#include "pila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct abb_nodo {
    struct abb_nodo *izq;
    struct abb_nodo *der;
    char *clave;
    void *dato;
} abb_nodo_t;

struct abb {
    abb_nodo_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir_dato;
    size_t cant;
};

struct abb_iter {
    pila_t *nodos;
};


static void _abb_nodo_imprimir(const abb_nodo_t *nodo, size_t nivel) {
    if (!nodo)
        return;

    char *hijo_izq = nodo->izq ? nodo->izq->clave : "-";
    char *hijo_der = nodo->der ? nodo->der->clave : "-";

    printf(
        "DEBUG IMPRIMIR: nivel %zu -- actual %s, hijo izq: %s, hijo der: %s \n",
        nivel, nodo->clave, hijo_izq, hijo_der);

    _abb_nodo_imprimir(nodo->izq, nivel + 1);
    _abb_nodo_imprimir(nodo->der, nivel + 1);
}


void abb_imprimir(const abb_t *arbol) {
    if (!arbol)
        return;
    _abb_nodo_imprimir(arbol->raiz, 1);
}

static abb_nodo_t *abb_nodo_crear(const char *clave, void *dato) {
    abb_nodo_t *nodo = malloc(sizeof(abb_nodo_t));
    if (!nodo)
        return NULL;

    nodo->izq = NULL;
    nodo->der = NULL;
    nodo->dato = dato;
    nodo->clave = strdup(clave);

    return nodo;
}

static void *abb_nodo_destruir(const abb_t *arbol,
                               abb_nodo_t *nodo,
                               bool destruir_dato) {
    void *dato = nodo->dato;
    free(nodo->clave);
    if (arbol->destruir_dato && destruir_dato)
        arbol->destruir_dato(dato);
    free(nodo);
    return dato;
}

/* Primitivas del mapa. */
abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    if (cmp == NULL)
        return NULL;

    abb_t *abb = malloc(sizeof(abb_t));
    abb->raiz = NULL;
    abb->cant = 0;
    abb->cmp = cmp;
    abb->destruir_dato = destruir_dato;

    return abb;
}

/* Función interna para reducir repetición de código en guardar borrar,
 * obtener y pertenece. Devuelve un puntero a la posición donde se guarda el
 * nodo correspondiente a clave, o donde debería estar el sub arbol. */
static abb_nodo_t **_abb_buscar_nodo(const abb_t *arbol,
                                     abb_nodo_t **padre,
                                     const char *clave) {
    abb_nodo_t *nodo = *padre;

    /* No está en el árbol */
    if (nodo == NULL)
        return padre;

    int comparacion = arbol->cmp(nodo->clave, clave);

    if (comparacion == 0) {
        return padre;
    }

    if (comparacion > 0)
        return _abb_buscar_nodo(arbol, &(nodo->izq), clave);

    return _abb_buscar_nodo(arbol, &(nodo->der), clave);
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    abb_nodo_t **pnodo = _abb_buscar_nodo(arbol, &(arbol->raiz), clave);

    if (*pnodo != NULL) {
        if (arbol->destruir_dato)
            arbol->destruir_dato((*pnodo)->dato);
        (*pnodo)->dato = dato;
        return true;
    }

    *pnodo = abb_nodo_crear(clave, dato);
    if (*pnodo == NULL)
        return false;

    arbol->cant++;
    return true;
}

/* Devuelve el menor de los hijos mayores de un nodo. */
static abb_nodo_t *buscar_siguiente_inorder(abb_nodo_t *nodo) {
    nodo = nodo->der;

    while (nodo->izq)
        nodo = nodo->izq;

    return nodo;
}

static void intercambiar_datos(abb_nodo_t *nodo, abb_nodo_t *siguiente) {
    void *dato = nodo->dato;
    char *clave = nodo->clave;
    nodo->dato = siguiente->dato;
    nodo->clave = siguiente->clave;
    siguiente->clave = clave;
    siguiente->dato = dato;
}

static void *_abb_borrar(abb_t *arbol, abb_nodo_t **padre, const char *clave) {
    abb_nodo_t **pnodo = _abb_buscar_nodo(arbol, padre, clave);
    abb_nodo_t *nodo = *pnodo;
    if (nodo == NULL)
        return NULL;

    /* Almacena el dato a ser devuelto. */
    void *dato;

    /* Caso 1: nodo hoja. */
    if (!nodo->izq && !nodo->der) {
        arbol->cant--;
        *pnodo = NULL;
        dato = abb_nodo_destruir(arbol, nodo, false);
    }

    /* Caso 2: nodo con sólo un hijo. */else if (!nodo->izq || !nodo->der) {
        arbol->cant--;
        if (nodo->izq)
            *pnodo = nodo->izq;
        else
            *pnodo = nodo->der;

        dato = abb_nodo_destruir(arbol, nodo, false);
    }

    /* Caso 3: nodo con ambos hijos.
     *         No se actualiza arbol->cant acá, se actualiza en la
     *         llamada recursiva. */
    else  // if(nodo->izq && nodo->der)
    {
        abb_nodo_t *siguiente = buscar_siguiente_inorder(nodo);

        /* Reemplaza los datos del siguiente con los del actual. */
        intercambiar_datos(nodo, siguiente);

        /* Elimina el nodo recientemente intercambiado. */
        dato = _abb_borrar(arbol, &(nodo->der), clave);
    }
    return dato;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    return _abb_borrar(arbol, &(arbol->raiz), clave);
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
    if (!arbol)
        return NULL;

    abb_nodo_t **pnodo =
        _abb_buscar_nodo(arbol, (abb_nodo_t **) &(arbol->raiz), clave);
    return *pnodo ? (*pnodo)->dato : NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    if (!arbol)
        return false;

    abb_nodo_t **pnodo =
        _abb_buscar_nodo(arbol, (abb_nodo_t **) &(arbol->raiz), clave);
    return *pnodo != NULL;
}

size_t abb_cantidad(abb_t *arbol) {
    return arbol->cant;
}

static void _abb_destruir(abb_t *arbol, abb_nodo_t *nodo) {
    if (!nodo)
        return;

    if (nodo->izq)
        _abb_destruir(arbol, nodo->izq);

    if (nodo->der)
        _abb_destruir(arbol, nodo->der);

    abb_nodo_destruir(arbol, nodo, true);
}

void abb_destruir(abb_t *arbol) {
    if (!arbol)
        return;

    _abb_destruir(arbol, arbol->raiz);
    free(arbol);

    return;
}

static bool _abb_visitar_in_order(abb_nodo_t *nodo,
                                  bool visitar(const char *, void *, void *),
                                  void *extra) {
    if (!nodo)
        return true;

    if(!_abb_visitar_in_order(nodo->izq, visitar, extra))
		return false;

    bool resultado = visitar(nodo->clave, nodo->dato, extra);
    if (!resultado)
        return false;

    return _abb_visitar_in_order(nodo->der, visitar, extra);
}

/* Implementa el iterador interno.
   "visitar" es una función de callback que recibe la clave, el valor y un
   puntero extra, y devuelve true si se debe seguir iterando, false en caso
   contrario).
 */
void abb_in_order(abb_t *arbol,
                  bool visitar(const char *, void *, void *),
                  void *extra) {
    _abb_visitar_in_order(arbol->raiz, visitar, extra);
}

/* Primitivas del iterador externo. */

static void apilar_siguientes(pila_t *pila, abb_nodo_t *nodo) {
    while (nodo) {
        pila_apilar(pila, nodo);
        nodo = nodo->izq;
    }
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    if (!arbol)
        return NULL;

    abb_iter_t *iter = malloc(sizeof(abb_iter_t));
    if (!iter)
        return NULL;

    iter->nodos = pila_crear();
    if (!iter->nodos)
        return NULL;

    /* Apila los elementos del árbol en el iterador. */
    if (arbol->raiz)
        apilar_siguientes(iter->nodos, arbol->raiz);

    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (!iter)
        return false;

    if (pila_esta_vacia(iter->nodos))
        return false;

    abb_nodo_t *actual = pila_desapilar(iter->nodos);
    apilar_siguientes(iter->nodos, actual->der);

    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if (!iter)
        return NULL;

    if (pila_esta_vacia(iter->nodos))
        return NULL;

    abb_nodo_t *actual = pila_ver_tope(iter->nodos);
    return actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    if (!iter)
        return false;

    return pila_esta_vacia(iter->nodos);
}

void abb_iter_in_destruir(abb_iter_t *iter) {
    if (!iter)
        return;

    pila_destruir(iter->nodos);
    free(iter);
}