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


bool _hash_guardar(hash_t* hash, const char* clave, void* dato, int num_fhash, const char* original, bool prim){
    num_fhash = num_fhash % 2;
    if (strcmp(clave, original) == 0 && num_fhash == 0 && !prim) {
        return false;
    }
    size_t indice = num_fhash == 0 ? h1(clave, hash->tam_tabla) : h2(clave, hash->tam_tabla);
    campo_hash_t* actual = &(hash->tabla[indice]);
    if (actual->clave != NULL && strcmp(clave, actual->clave) != 0) {
        bool aux = _hash_guardar(hash, actual->clave, actual->dato, actual->num_fhash + 1, original, false);
        if (!aux) {
            return false;
        }
    } else if (actual->clave == NULL || strcmp(clave, actual->clave) != 0) {
        hash->cantidad++;
    }
    actual->clave = strdup(clave);
    actual->dato = dato;
    actual->num_fhash = num_fhash;
    return true;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    // TODO
    // Asumir que no hay que lidiar con potenciales redimensiones (en caso de tener que,
    // devovler false)
    return _hash_guardar(hash, clave, dato, 0, clave, true);
}




hash_t *hash_crear(){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) {
        return NULL;
    }
    campo_hash_t* tabla = malloc(sizeof(campo_hash_t*) * 20);
    if (tabla == NULL){
        free(hash);
        return NULL;
    }
    hash->cantidad = 0;
    hash->tam_tabla = 20;
    return hash;
}