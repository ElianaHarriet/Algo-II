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

void guardar_campo(int pos, hash_t* hash, char* clave, void* dato, int num_fhash, bool prim) {
    campo_hash_t campo = hash->tabla[pos];
    campo.clave = strdup(clave);
    campo.dato = dato;
    campo.num_fhash = num_fhash;
    hash->tabla[pos] = campo;
    hash->cantidad = prim ? hash->cantidad + 1 : hash->cantidad;
}

bool _hash_guardar(hash_t* hash, const char* clave, void* dato, int num_fhash, bool prim, char* original) {
    if (strcmp(original, clave) == 0 && !prim && num_fhash == 1) {
        return false;
    }
    if (hash_pertenece(hash, clave) && prim) {
        size_t pos = h1(clave, num_fhash);
        size_t pos2 = h2(clave, num_fhash);
        campo_hash_t campo = hash->tabla[pos];
        if (strcmp(campo.clave, clave) != 0) {
            pos = pos2;
            campo = hash->tabla[pos];
        }
        campo.dato = dato;
        hash->tabla[pos] = campo;
        return true;
    }
    size_t pos = num_fhash == 1 ? h1(clave, hash->tam_tabla) : h2(clave, hash->tam_tabla);
    campo_hash_t campo = hash->tabla[pos];
    if (campo.clave == NULL) {
        guardar_campo(pos, hash, clave, dato, num_fhash, prim);
        return true;
    }
    int fhash = campo.num_fhash == 1 ? 2 : 1;
    bool guard = _hash_guardar(hash, campo.clave, campo.dato, fhash, false, original);
    if (!guard) return false;
    guardar_campo(pos, hash, clave, dato, num_fhash, prim);
    return true;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    return _hash_guardar(hash, clave, dato, 1, true, clave);
}