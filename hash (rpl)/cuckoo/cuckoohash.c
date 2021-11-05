#include "hash.h"
#include <string.h>

#define CANT_FUNC_HASH 2

typedef struct hash{
  size_t capacidad;
  size_t cantidad;
  hash_destruir_dato_t funcion_destruccion;
  campo_t* tabla;
} hash_t;

typedef struct campo{
  char* clave;
  void* valor;
  size_t func_hash;
} campo_t;



struct hash_iter{
  const hash_t* hash;
  campo_t campo_act;
  size_t posicion;
};


// campo_t* campo_crear(char* clave, void* valor) {
//     campo_t* campo = malloc(sizeof(campo_t));
//     if (campo == NULL) {
//         return NULL;
//     }
//     sprintf(campo->clave, "%s", clave);
//     campo->valor = valor;
//     campo->func_hash = 1;
//     return campo;
// }

size_t h1(char *key, size_t len, size_t capacidad)
{
    unsigned int hash, i;
    for(hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash % capacidad;
} // {jenkins_one_at_a_time_hash} https://en.wikipedia.org/wiki/Jenkins_hash_function

size_t h2(unsigned char *str, size_t capacidad) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % capacidad;
} // {djb2} http://www.cse.yorku.ca/~oz/hash.html

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    return _hash_crear(destruir_dato, 20);
}

hash_t* _hash_crear(hash_destruir_dato_t destruir_dato, size_t cap) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) {
        return NULL;
    }
    campo_t* tabla = malloc(sizeof(campo_t) * cap);
    if (tabla == NULL){
        free(hash);
        return NULL;
    }
    hash->cantidad = 0;
    hash->capacidad = cap;
    hash->tabla = tabla;
    hash->funcion_destruccion = destruir_dato;
    return hash;
}


size_t contraseña(const char* clave, size_t func_hash, size_t capacidad){
    if (func_hash == 1 ){
        return h1(clave, capacidad);
    }
    if (func_hash == 2 ){
        return h2(clave, capacidad);
    }
}

bool _hash_guardar(hash_t* hash, const char* clave, void* dato, size_t func_hash, const char* original){
    campo_t* campo = campo_crear(clave, dato);
    if (campo == NULL) {
        return false;
    }
    size_t contra =  contraseña(clave, func_hash, hash->capacidad);
    campo_t* actual = hash->tabla[contra];
    if(actual == NULL){
        actual = campo;
        return true;
    }
    if (actual == original){
        return false;
        //llamar funcion redimensionar;
    }
    size_t hash_fun = actual->func_hash;
    size_t nueva_fun = (hash_fun + 1) % CANT_FUNC_HASH + 1;
    bool guardo = _hash_guardar(hash, actual->clave, actual->valor, nueva_fun, original);
    hash->tabla[contra] = campo;
    return guardo;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    return _hash_guardar(hash, clave, dato, 1, clave);
}

hash_t* hash_redimensionar(hash_t* hash, size_t x) {
    hash_t* nuevo = _hash_crear(hash->funcion_destruccion, hash->capacidad * x);
    for (int i = 0; i < nuevo->capacidad; i++) {
        
    }
}