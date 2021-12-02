// #include "heap.h"
#include <stdbool.h>    // bool
#include <stddef.h>    // size_t
#include <stdio.h>    // printf
#include <stdlib.h>  // malloc

typedef int (*cmp_func_t)(const void *a, const void *b);

// int max(const void *a, const void *b) {
//     printf("a -> %i\t| b -> %i\n", *(int *)a, *(int *)b);
//     return *(int *)a - *(int *)b;
// }

int max(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

bool _es_heap_max(void** arr, size_t n, cmp_func_t cmp) {
    for (size_t p = 0; p < n; p++) {
        size_t h_izq = 2 * p + 1;
        size_t h_der = 2 * p + 2;
        if ((h_izq < n && cmp(arr[p], arr[h_izq]) < 0) || (h_der < n && cmp(arr[p], arr[h_der]) < 0)) {
            return false;
        }
    }
    return true;
}

// int main() {
//     void** arr = malloc(sizeof(void*) * 10);
//     printf("[");
//     for (int i = 0; i < 25; i++) {
//         arr[i] = malloc(sizeof(int));
//         *(int *)arr[i] = 30 - i;
//         printf("h, ");
//     }
//     printf("]\n");
//     bool b = _es_heap_max(arr, 10, max);
//     if (b) {
//         printf("Es un heap max\n");
//     } else {
//         printf("No es un heap max\n");
//     }
//     return 0;
// }