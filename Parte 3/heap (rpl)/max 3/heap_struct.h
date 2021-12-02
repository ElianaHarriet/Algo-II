#ifndef HEAP_STR
#define HEAP_STR

#include "heap.h"
#include <stddef.h>

struct heap {
    void **datos;
    size_t tam;
    size_t cant;
    cmp_func_t cmp;
};

#endif