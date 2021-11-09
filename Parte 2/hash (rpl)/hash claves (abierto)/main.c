#include "lista.h"
#include "hash.h"
#include "hash_struct.h"

lista_t* hash_claves(const hash_t* hash) {
    lista_t* lista = lista_crear();

    for (int i = 0; i < hash->largo; i++) {
        lista_t* list = (hash->tabla)[i];
        if (!lista_esta_vacia(list)) {
            lista_iter_t* iter = lista_iter_crear(list);
            while(!lista_iter_al_final(iter)) {
                hash_nodo_t* nodo = lista_iter_ver_actual(iter);
                //falta copiar la clave por las dudas (obligatorio)
                lista_insertar_ultimo(lista, nodo->clave);
                lista_iter_avanzar(iter);
            }
            hash_iter_destruir(iter);
        }
    }
    return lista;
}