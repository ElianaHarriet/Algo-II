#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "hash_struct.h"

/* crea una copia (memoria dinamica) de la cadena pasada por parametro */
char* strdup(const char* org) {
    char* cpy = malloc(sizeof(char) * (strlen(org) + 1));
    if (!cpy) return NULL;
    strcpy(cpy, org);
    return cpy;
}

void guardar_campo(size_t pos, hash_t* hash, const char* clave, void* dato, int num_fhash, bool prim) {
    hash->tabla[pos].clave = strdup(clave);
    hash->tabla[pos].dato = dato;
    hash->tabla[pos].num_fhash = num_fhash;
    hash->cantidad = prim ? hash->cantidad + 1 : hash->cantidad;
}

bool _hash_guardar(hash_t* hash, const char* clave, void* dato, int num_fhash, bool prim, const char* original, size_t llamadas) {
    if (llamadas == hash->tam_tabla) {
        return false;
    }
    size_t pos = num_fhash == 1 ? h1(clave, hash->tam_tabla) : h2(clave, hash->tam_tabla);
    campo_hash_t campo = hash->tabla[pos];
    if (campo.clave == NULL) {
        guardar_campo(pos, hash, clave, dato, num_fhash, prim);
        return true;
    }
    int fhash = campo.num_fhash == 1 ? 2 : 1;
    bool guard = _hash_guardar(hash, campo.clave, campo.dato, fhash, false, original, llamadas + 1);
    if (!guard) return false;
    guardar_campo(pos, hash, clave, dato, num_fhash, prim);
    return true;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    return hash_pertenece(hash, clave) ? false : _hash_guardar(hash, clave, dato, 1, true, clave, 0);
}