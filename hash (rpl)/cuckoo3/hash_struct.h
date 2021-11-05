#ifndef STRUCT_HASH
#define STRUCT_HASH

#include <stddef.h>

typedef struct campo_hash {
    char* clave;
    void* dato;
    int num_fhash;
} campo_hash_t;

struct hash {                   
    campo_hash_t* tabla;                   
    size_t cantidad;                        
    size_t tam_tabla;                       
};

size_t h1(const char* clave, size_t largo);
size_t h2(const char* clave, size_t largo);

#endif