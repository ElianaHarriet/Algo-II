// Implementar en C una primitiva para el heap (siendo este un max-heap) que reciba un heap
// y una función de comparación y lo reordene de manera tal que se se comporte como max-heap
// para la nueva función de comparación (se cambia la función de prioridad). El orden de dicha
// primitiva debe ser O(n).
#include "heap.h"

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

void heap_cambiar_prioridad(heap_t* heap, cmp_func_t nueva_cmp) {
    heap->cmp = nueva_cmp;
    heapify(heap->datos, heap->cant, heap->cmp);
}