// Implementar una primitiva para el heap (de máximos) que obtenga
// los 3 elementos más grandes del heap en tiempos constante.
#include "heap_struct.h"
#include "heap.h"
#include <stdlib.h>

size_t pos_max(size_t except, heap_t *heap) {
    size_t pos = except == 1 ? 2 : 1;
    for (size_t i = 2; i <= 6 && i < heap->cant; i++) {
        if (i != except && heap->cmp(heap->datos[i], heap->datos[pos]) > 0) {
            pos = i;
        }
    }
    return pos;
}

void** heap_max3(const heap_t* heap) {
    void** max3 = malloc(sizeof(void*) * 3);
    if (heap_esta_vacio(heap)) return max3;
    max3[0] = heap->datos[0];
    if (heap->cant == 1) return max3;
    size_t segundo = pos_max(0, heap);
    max3[1] = heap->datos[segundo];
    if (heap->cant == 2) return max3;
    size_t tercero = pos_max(segundo, heap);
    max3[2] = heap->datos[tercero];
    return max3;
}

