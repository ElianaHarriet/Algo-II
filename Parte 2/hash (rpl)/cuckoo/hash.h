#ifndef HASH_H
#define HASH_H
#include <stdbool.h> 
#include <stddef.h>

typedef struct hash hash_t;

// A implementar
bool hash_guardar(hash_t* hash, const char* clave, void* dato);

hash_t* hash_crear();

bool hash_pertenece(const hash_t* hash, const char* clave);

void* hash_borrar(hash_t* hash, const char* clave);

void* hash_obtener(const hash_t* hash, const char* clave);

size_t hash_cantidad(const hash_t* hash);

// Se asume que Barbara se encarga de los datos, por simplicidad del ejercicio
void hash_destruir(hash_t* hash);

#endif