#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pila.h"
#include "abb.h"



/* *********************************************************************
 *               DEFINICIÓN DE LOS TIPOS DE DATOS
 * *********************************************************************/

/* Definición del tipo abb_nodo y abb */
typedef struct abb_nodo {
    char* clave;
    void* dato;
    struct abb_nodo* izq;
    struct abb_nodo* der;
} abb_nodo_t;

typedef struct abb {
    abb_nodo_t* raiz;
    size_t cantidad;
    abb_comparar_clave_t func_cmp;
    abb_destruir_dato_t func_destr;
} abb_t;


/* Definición del abb_iter */
typedef struct abb_iter {
    pila_t* nodos;
} abb_iter_t;



/* *********************************************************************
 *                        FUNCIONES AUXILIARES
 * *********************************************************************/

/* Crea un nodo abb_nodo
 */
abb_nodo_t* nodo_crear(const char* clave, void* dato) {
    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
    if (!nodo){
        return NULL;
    }
    nodo->clave = strdup(clave);
    nodo->dato = dato;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

/* Devuelve el padre del nodo que estamos buscando, si no encuentra
 * al padre, devuelve la raiz
 */
abb_nodo_t* devolver_padre(const abb_t* abb, abb_nodo_t* padre, abb_nodo_t* nodo, const char* clave) {
    abb_comparar_clave_t funcion = abb->func_cmp;
    if (funcion(nodo->clave, clave) > 0) {
        return nodo->izq ? devolver_padre(abb, nodo, nodo->izq, clave) : nodo;
    } 
    if (funcion(nodo->clave, clave) < 0) {
        return nodo->der ? devolver_padre(abb, nodo, nodo->der, clave) : nodo;
    }
    return padre; 
}

/* Destruye el nodo pasado por parámetro, luego destruye el dato del nodo padre
 * si es que tiene funcion destruir_dato, le resta uno a la cantidad de nodos
 * y reemplaza el dato destruido del nodo por el dato que se pasa por parámetro
*/
bool _guardar(abb_t* arbol, abb_nodo_t* padre, abb_nodo_t* nodo, void *dato) {
    free(nodo->clave);
    free(nodo);
    if (arbol->func_destr) {
        arbol->func_destr(padre->dato);
    }
    arbol->cantidad--;
    padre->dato = dato;
    return true;
}

/* Se le llama cuando se quiere guardar algo ya guardado, le cambia su dato
 */
void abb_reemplazar(abb_t* arbol, const char* clave, void* dato) {
    abb_nodo_t* padre = devolver_padre(arbol, arbol->raiz, arbol->raiz, clave);
    int func = arbol->func_cmp(padre->clave, clave);
    abb_nodo_t* nodo = func == 0 ? padre : func > 0 ? padre->izq : padre->der;
    if (arbol->func_destr) {
        arbol->func_destr(nodo->dato);
    }
    nodo->dato = dato;
}

/* Devuelve la cantidad de hijos
 */
int cant_hijos(abb_nodo_t* nodo) {
    int a = nodo->izq ? 1 : 0;
    int b = nodo->der ? 1 : 0;
    return a + b;
}

/* Destruye un nodo abb_nodo, si destruir_dato es true, llama a la función
 * destruir_dato pasándole el dato del nodo para que lo destruya
 */
void nodo_destruir(abb_nodo_t* nodo, abb_t* arbol, bool destruir_dato) {
    if (destruir_dato && arbol->func_destr) {
        arbol->func_destr(nodo->dato);
    }
    free(nodo->clave);
    free(nodo);
}

/* Busca el nodo minimo en el subarbol izquierdo de un nodo
 * (Usado cuando de borra un nodo con dos hijos)
 */
abb_nodo_t* nodo_minimo(abb_nodo_t* nodo) {
    while (nodo->izq) {
        nodo = nodo->izq;
    }
    return nodo;
}

/* Borra un nodo con dos hijos
*/
void nodo_borrar_dos_h(abb_t *arbol, abb_nodo_t* actual) {
    abb_nodo_t* nodo_min = nodo_minimo(actual->der);
    char* clave_min = strdup(nodo_min->clave);
    void* dato_min = abb_borrar(arbol, clave_min);
    free(actual->clave);
    actual->clave = clave_min;
    actual->dato = dato_min;
    arbol->cantidad++;
}



/* *********************************************************************
 *                         PRIMITIVAS DEL ABB
 * *********************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
    abb_t* arbol = malloc(sizeof(abb_t));
    if (!arbol) {
        return NULL;
    }
    arbol->cantidad = 0;
    arbol->raiz = NULL;
    arbol->func_cmp = cmp;
    arbol->func_destr = destruir_dato;
    return arbol;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    if (abb_pertenece(arbol, clave)) {
        abb_reemplazar(arbol, clave, dato);
        return true;
    }

    abb_nodo_t* raiz = arbol->raiz;
    abb_nodo_t* nodo = nodo_crear(clave, dato);
    if (!nodo) {
        return false;
    }

    arbol->cantidad++;
    if (arbol->raiz == NULL) {
        arbol->raiz = nodo;
        return true;
    }
    abb_nodo_t* padre = devolver_padre(arbol, raiz, raiz, clave);
    int func = arbol->func_cmp(padre->clave, clave);
    if (func == 0) {
        return _guardar(arbol, padre, nodo, dato);
    }
    if (func > 0) {
        padre->izq = nodo;
    } else {
        padre->der = nodo;
    }
    return true;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    abb_nodo_t* raiz = arbol->raiz;
    if (!raiz) {
        return NULL;
    }

    abb_nodo_t* padre = devolver_padre(arbol, raiz, raiz, clave);
    int func = arbol->func_cmp(padre->clave, clave);
    abb_nodo_t* nodo = func > 0 ? padre->izq : func < 0 ? padre->der : padre;
    if (!nodo || arbol->func_cmp(nodo->clave, clave) != 0) {
        return NULL;
    }

    void* dato = nodo->dato;
    int hijos = cant_hijos(nodo);
    abb_nodo_t* aux = NULL;
    if (hijos == 0) {
        nodo_destruir(nodo, arbol, false);
    } else if (hijos == 1) {
        aux = nodo->izq ? nodo->izq : nodo->der;
        nodo_destruir(nodo, arbol, false);
    } else {
        nodo_borrar_dos_h(arbol, nodo);
        arbol->cantidad--;
        return dato;
    }

    if (func > 0) {
        padre->izq = aux;
    } else if (func < 0) {
        padre->der = aux;
    } else {
        arbol->raiz = aux;
    }
    arbol->cantidad--;
    return dato;
}

void* _abb_obtener(const abb_t* arbol, const char* clave, bool* pertenece) {
    abb_nodo_t* raiz = arbol->raiz;
    if (!raiz) {
        return NULL;
    }
    abb_nodo_t* padre = devolver_padre(arbol, raiz, raiz, clave);
    if (arbol->func_cmp(padre->clave, clave) == 0) {
        void* dato = padre->dato;
        *pertenece = true;
        return dato; 
    }
    abb_nodo_t* hijo = arbol->func_cmp(padre->clave, clave) > 0 ? padre->izq : padre->der;
    if (!hijo || arbol->func_cmp(hijo->clave, clave) != 0) {
        return NULL;
    }
    void* dato = hijo->dato;
    *pertenece = true;
    return dato;
}

void* abb_obtener(const abb_t* arbol, const char* clave) {
    bool pertenece = false;
    return _abb_obtener(arbol, clave, &pertenece);
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
    bool pertenece = false;
    _abb_obtener(arbol, clave, &pertenece);
    return pertenece;
}

size_t abb_cantidad(const abb_t *arbol) {
    return arbol->cantidad;
}

void _abb_destruir(abb_t* arbol, abb_nodo_t* abb) {
    if (!abb) {
        return;
    }
    _abb_destruir(arbol, abb->izq);
    _abb_destruir(arbol, abb->der);
    nodo_destruir(abb, arbol, true);
}

void abb_destruir(abb_t *arbol) {
    _abb_destruir(arbol, arbol->raiz);
    free(arbol);
}



/* *********************************************************************
 *               PRIMITIVA DEL ITERADOR INTERNO DEL ABB
 *                             (Inorder)
 * *********************************************************************/

bool _abb_in_order(abb_nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra) {
    if (!nodo) {
        return true;
    }

    if (!_abb_in_order(nodo->izq, visitar, extra)) {
        return false;
    }
    if (!visitar(nodo->clave, nodo->dato, extra)) {
        return false;
    }
    if (!_abb_in_order(nodo->der, visitar, extra)) {
        return false;
    }
    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    _abb_in_order(arbol->raiz, visitar, extra);
}



/* *********************************************************************
 *               PRIMITIVA DEL ITERADOR EXTERNO DEL ABB
 *                             (Inorder)
 * *********************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
    if(!arbol) {
        return NULL;
    }

    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) {
        return NULL;
    }

    iter->nodos = pila_crear();
    if (!iter->nodos) {
        free(iter);
        return NULL;
    }

    if (!arbol->raiz) {
        return iter;
    }
    pila_apilar(iter->nodos, arbol->raiz);
    abb_nodo_t* actual = pila_ver_tope(iter->nodos);
    while(actual->izq) {
        pila_apilar(iter->nodos, actual->izq);
        actual = pila_ver_tope(iter->nodos);
    }
    return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
    return pila_esta_vacia(iter->nodos);
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
    if (abb_iter_in_al_final(iter)) {
        return false;
    }
    abb_nodo_t* actual = pila_ver_tope(iter->nodos);
    abb_nodo_t* nodo_desapilado = pila_desapilar(iter->nodos);
    if (nodo_desapilado->der) {
        pila_apilar(iter->nodos, nodo_desapilado->der);
        actual = pila_ver_tope(iter->nodos);
        while(actual->izq) {
            pila_apilar(iter->nodos, actual->izq);
            actual = pila_ver_tope(iter->nodos);
        }
    }  
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
    if(abb_iter_in_al_final(iter)) {
        return NULL;
    }
    abb_nodo_t* actual = pila_ver_tope(iter->nodos);
    return (const char*)actual->clave;   
}

void abb_iter_in_destruir(abb_iter_t* iter) {
    pila_destruir(iter->nodos);
    free(iter);
}
