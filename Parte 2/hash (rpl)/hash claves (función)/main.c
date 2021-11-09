// Implementar una función lista_t* hash_claves(const hash_t*) que reciba un hash y
// devuelva una lista con sus claves.
#include "hash.h"

lista_t* hash_claves(const hash_t* hash) {
    lista_t* lista = lista_crear();
    hash_iter_t* iter = hash_iter_crear(hash);
    while(!hash_iter_al_final(iter)) {
        //falta copiar la clave por las dudas (obligatorio)
        lista_insertar_ultimo(lista, hash_iter_ver_actual(iter));
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
    return lista;
}