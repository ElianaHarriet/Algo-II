#include "heap.h"
#include <stdlib.h>
#include <stdio.h>


/* *********************************************************************
 *                        DEFINICIÓN DEL TDA HEAP
 * *********************************************************************/

/* Definición del heap */
typedef struct heap {
    size_t cantidad;
    size_t capacidad;
    void** elementos;
    cmp_func_t cmp;
} heap_t;

/* *********************************************************************
 *                        FUNCIONES AUXILIARES
 * *********************************************************************/

/* Función auxiliar que retorna la posición en el arreglo del
 * elemento mayor entre el padre y sus dos hijos
 */
size_t maximo(void** arreglo, size_t pos_padre, size_t pos_hijo_izq, size_t pos_hijo_der, cmp_func_t cmp, size_t cant) {
    void* padre = arreglo[pos_padre];
    if (pos_hijo_izq < cant && pos_hijo_der < cant) {
        void* hijo_izq = arreglo[pos_hijo_izq];
        void* hijo_der = arreglo[pos_hijo_der];
        return cmp(padre, hijo_izq) > 0 ? cmp(padre, hijo_der) > 0 ? pos_padre : pos_hijo_der :
                cmp(hijo_izq, hijo_der) > 0 ? pos_hijo_izq : pos_hijo_der;
    }
    if (pos_hijo_izq < cant) {
        return cmp(padre, arreglo[pos_hijo_izq]) > 0 ? pos_padre : pos_hijo_izq;
    }
    return cmp(padre, arreglo[pos_hijo_der]) > 0 ? pos_padre : pos_hijo_der;
}

void downheap(void*** arreglo, cmp_func_t cmp, size_t i, size_t cantidad) {
    size_t pos_padre = i;
    size_t pos_hijo_izq = 2 * i + 1;
    if(pos_hijo_izq >= cantidad) return;
    size_t pos_hijo_der = 2 * i + 2;
    void* padre = (*arreglo)[i];
    size_t pos_max = maximo(*arreglo, pos_padre, pos_hijo_izq, pos_hijo_der, cmp, cantidad);
    if(pos_max != pos_padre) {
        void* aux = padre;
        (*arreglo)[pos_padre] = (*arreglo)[pos_max];
        (*arreglo)[pos_max] = aux;
        downheap(arreglo, cmp, pos_max, cantidad);
    }
}  

void upheap(heap_t* heap, size_t i) {
    if (i == 0) return;
    size_t pos_padre = (i - 1) / 2;
    void* padre = heap->elementos[pos_padre];
    void* hijo = heap->elementos[i];
    if(heap->cmp(padre, hijo) < 0) {
        void* aux = padre;
        heap->elementos[pos_padre] = hijo;
        heap->elementos[i] = aux;
        upheap(heap, pos_padre);
    }
}

bool heap_redimensionar(heap_t* heap, size_t nueva_capacidad) {
    void* elementos_nuevo = realloc(heap->elementos, nueva_capacidad * sizeof(void*));
    if (elementos_nuevo == NULL) {
        return false;
    }
    heap->elementos = elementos_nuevo;
    heap->capacidad = nueva_capacidad;
    return true;
}



/* *********************************************************************
 *                        PRIMITIVAS DEL HASH
 * *********************************************************************/

heap_t* heap_crear(cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    heap->cantidad = 0;
    heap->capacidad = 20;
    heap->cmp = cmp;
    heap->elementos = malloc(sizeof(void*) * 20);
    if(!heap->elementos) {
        free(heap);
        return NULL;
    }
    return heap;
}
    
heap_t* heap_crear_arr(void* arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    heap->cantidad = n;
    heap->capacidad = 20;
    while (heap->capacidad < n) {
        heap->capacidad *= 2;
    }
    heap->cmp = cmp;
    heap->elementos = malloc(sizeof(void*) * heap->capacidad);
    if(!heap->elementos) {
        free(heap);
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        heap->elementos[i] = arreglo[i];
    }
    size_t i = n/2;
    while (i >= 0) {
        if(i == -1) break;
        downheap(&heap->elementos, heap->cmp, i, heap->cantidad);
        i--;
    }
    return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void* e)) {
    if(!heap) return;
    for(size_t i = 0; i < heap->cantidad; i++) {
        if(destruir_elemento) destruir_elemento(heap->elementos[i]);
    }
    free(heap->elementos);
    free(heap);
}

size_t heap_cantidad(const heap_t* heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t* heap) {
    return heap->cantidad == 0;
}

bool heap_encolar(heap_t* heap, void* elem) {
    if (heap->cantidad == heap->capacidad) {
        if (!heap_redimensionar(heap, heap->capacidad * 2)) return false;
    }
    heap->elementos[heap->cantidad] = elem;
    upheap(heap, heap->cantidad);
    heap->cantidad++;
    return true;
}

void* heap_ver_max(const heap_t* heap) {
    if(heap_esta_vacio(heap)) return NULL;
    return heap->elementos[0];
}        

void* heap_desencolar(heap_t* heap){
    if(heap_esta_vacio(heap)) return NULL;
    void* maximo = heap->elementos[0];
    heap->elementos[0] = heap->elementos[heap->cantidad - 1];
    heap->elementos[heap->cantidad - 1] = NULL;
    heap->cantidad--;
    downheap(&heap->elementos, heap->cmp, 0, heap->cantidad);
    return maximo;
}



/* *********************************************************************
 *                            HEAP-SORT
 * *********************************************************************/

void heap_sort(void* elementos[], size_t cant, cmp_func_t cmp) {
    size_t j = cant / 2;
    while (j >= 0) {
        if(j == -1) break;
        downheap(&elementos, cmp, j, cant);
        j--;
    }
    for (size_t i = 0; i < cant; i++) {
        void* aux = elementos[0];
        elementos[0] = elementos[cant - 1 - i];
        elementos[cant - 1 - i] = aux;
        downheap(&elementos, cmp, 0, cant - 1 - i);
    }
}