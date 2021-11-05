// Implementar en lenguaje C una función recursiva con la firma
// bool es_heap(int arr[], size_t n). Esta función debe devolver true
// o false de acuerdo a si el arreglo que recibe como parámetro cumple
// la propiedad de heap (de mínimos).
// #include "main.h"
#include <stdbool.h>
#include <stdlib.h>

bool es_heap(int arr[], size_t n) {
    for (size_t p = 1; p < n; p++) {
        size_t h_izq = 2 * p + 1;
        size_t h_der = 2 * p + 2;
        if ((h_izq < n && arr[p] > arr[h_izq]) || (h_der < n && arr[p] > arr[h_der])) {
            return false;
        }
    }
    return true;
}