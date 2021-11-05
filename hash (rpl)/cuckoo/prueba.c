#include <stdlib.h>
#include <stdbool.h>

/* Estructura de un campo */
typedef struct campo_hash {
    char* clave;
    void* dato;
    int num_fhash;
} campo_hash_t;

/* Estructrua de un hash cuckoo */
typedef struct hash {                   
    campo_hash_t* tabla;                   
    size_t cantidad;                        
    size_t tam_tabla;                       
} hash_t;

/* Función de hashing 1 */
size_t hash_djb2(const char* clave) {
    size_t hash = 5381;
    int c = *clave++;
    
    while ((c = *clave++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

/* Función de hashing 2 */
size_t hash_sdbm(const char* clave) {
    size_t hash = 0;
    int c = *clave++;
    
    while ((c = *clave++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

/* Función para crear el hash */
hash_t* hash_crear(size_t tam_tabla) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash) return NULL;
    
    hash->tabla = malloc(sizeof(campo_hash_t) * tam_tabla);
    if (!hash->tabla) {
        free(hash);
        return NULL;
    }
    
    hash->cantidad = 0;
    hash->tam_tabla = tam_tabla;
    
    return hash;
}

/* Función para guardar clave y dato en el hash cuckoo  (github copilot) */
bool hash_guardar(hash_t* hash, const char* clave, void* valor) {
    return _hash_guardar(hash, clave, valor, hash_djb2, true, clave);
}
bool _hash_guardar(hash_t* hash, const char* clave, void* valor, size_t (*fhash)(const char*), bool prim, const char* original) {
    if (strcmp(clave, original) == 0 && !prim) return false;
    if (hash->cantidad >= hash->tam_tabla * 0.7) {
        return false;
    }
    size_t pos = fhash(clave) % hash->tam_tabla;
    
    if (strcmp(hash->tabla[pos].clave, clave) == 0) {
        hash->tabla[pos].dato = valor;
        return true;
    }
    if (hash->tabla[pos].clave != NULL) {
        if (hash->tabla[pos].num_fhash == 1) {
            hash->tabla[pos].num_fhash = 2;
            return _hash_guardar(hash, hash->tabla[pos].clave, hash->tabla[pos].dato, hash_sdbm, false, original);
        } else {
            hash->tabla[pos].num_fhash = 1;
            return _hash_guardar(hash, hash->tabla[pos].clave, hash->tabla[pos].dato, hash_djb2, false, original);
        }
    }
    bool pertenece = hash_pertenece(hash, clave);
    if (!pertenece) {
        hash->tabla[pos].clave = strdup(clave);
        hash->tabla[pos].dato = valor;
        hash->cantidad++;
        hash->tabla[pos].num_fhash = 1;
    }
    hash->tabla[pos].dato = valor;
    return true;
}