#include "hash.h"
#include "hash_struct.h"

lista_t* hash_claves(const hash_t* hash) {
    lista_t* lista = lista_crear();
    for (int i = 0; i < hash->capacidad; i++) {
        campo_t campo = (hash->tabla)[i];
        if (campo.estado == OCUPADO) {
            char* clave = campo.clave;
            //falta copiar la clave por las dudas (obligatorio)
            lista_insertar_ultimo(lista, clave);
        }
    }
    return lista;
}