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

void guardar(hash_t* hash, char* clave, void* dato, size_t pos, bool prim, int num_hash) {
    hash->tabla[pos].clave = clave;
    hash->tabla[pos].dato = dato;
    hash->tabla[pos].num_fhash = num_hash;
    hash->cantidad = prim ? hash->cantidad + 1 : hash->cantidad;
}

bool _hash_guardar(hash_t* hash, char* clave, void* dato, bool prim) {
    int x = 0;
    char* _clave = strdup(clave);
    char* clave_nueva;
    void* dato_nuevo;
    int num_hash = 1;
    int num_hash_nuevo;
    while (x < hash->cantidad) {
        size_t pos = num_hash == 1 ? h1(_clave, hash->cantidad) : h2(_clave, hash->cantidad);
        if (hash->tabla[pos].clave == NULL) {
            guardar(hash, _clave, dato, pos, prim, 1);
            return true;
        }
        clave_nueva = hash->tabla[pos].clave;
        dato_nuevo = hash->tabla[pos].dato;
        num_hash_nuevo = hash->tabla[pos].num_fhash == 1 ? 2 : 1;
        guardar(hash, _clave, dato, pos, prim, num_hash);
        _clave = clave_nueva;
        dato = dato_nuevo;
        num_hash = num_hash_nuevo;
        // x++
    }
    return false;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    return _hash_guardar(hash, clave, dato, true);
}




/*
function insert(x) is
    if lookup(x) then
        return
    end if
    while Max-Loop <= then
        if T1[h1(x)] = NULL then
            T1[h1(x)] := x
            return
        end if
        x <-> T1[h1(x)]
        if T2[h2(x)] = NULL then
            T2[h2(x)] := x
            return
        end if
        x <-> T2[h2(x)]
    repeat
    rehash()
    insert(x)
end function
*/