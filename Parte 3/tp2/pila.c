#include "pila.h"
#include <stdio.h>    //para poder debugear con printf
#include <stdlib.h>
#define CAPACIDAD_INICIAL 10
#define VACIO 0

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad ==VACIO;
}

bool pila_redimensionar(pila_t *pila, size_t nueva_capacidad){
    void* datos_nuevo = realloc(pila->datos,nueva_capacidad*sizeof(void*));
    if (datos_nuevo == NULL){
        return false;
    }
    pila->datos = datos_nuevo;
    pila->capacidad = nueva_capacidad;
    return true;
}

bool pila_apilar(pila_t *pila, void *valor){
    if (pila->cantidad == pila->capacidad){
        size_t nueva_capacidad = pila->capacidad*2;
        bool fallo = pila_redimensionar(pila,nueva_capacidad);
        if (!fallo){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad ++;
    return true;
    }

void *pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad-1];
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    void* el_anterior = pila->datos[pila->cantidad-1];
    pila->cantidad-=1;
    if ((pila->cantidad)*4 <= pila->capacidad  && pila->capacidad != CAPACIDAD_INICIAL){
        size_t nueva_capacidad = pila->capacidad/2;
        if (nueva_capacidad<(CAPACIDAD_INICIAL)){
            nueva_capacidad = CAPACIDAD_INICIAL;
        }
        pila_redimensionar(pila,nueva_capacidad);
        pila->capacidad = nueva_capacidad;
    }
    return el_anterior;


}




pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL){
        return NULL;
    }
    pila->capacidad = CAPACIDAD_INICIAL;     
    pila->datos = malloc( CAPACIDAD_INICIAL * sizeof(void*));
    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    pila->cantidad = VACIO;

    return pila;
}

// ...
