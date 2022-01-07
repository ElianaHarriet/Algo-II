// 2. Dada una lista enlazada que almacena cadenas, notamos que algunas cadenas podrían estar repetidas. Se pide una función
// que, en orden lineal, devuelva una nueva lista que contenga solamente las cadenas que aparecen una única vez. La lista
// original no puede ser modificada. Justificar el orden de la solución propuesta.
#include "lista.h"
#include "hash.h"

lista_t* sin_repetidos(lista_t* lista) {
    lista_t* nueva = lista_crear();
    if (!nueva) return NULL;
    hash_t* hash = hash_crear(NULL);
    if (!hash) {
        lista_destruir(nueva, NULL);
        return NULL;
    }

    lista_iter_t* iter = lista_iter_crear(lista);
    if (!iter) {
        lista_destruir(nueva, NULL);
        hash_destruir(hash);
        return NULL;
    }

    while (!lista_iter_al_final(iter)) {
        char* clave = lista_iter_ver_actual(iter);
        if (!hash_pertenece(hash, clave)) {
            if (!hash_guardar(hash, clave, clave)) {
                lista_destruir(nueva, NULL);
                hash_destruir(hash);
                lista_iter_destruir(iter);
                return NULL;
            }
            if (!lista_insertar_ultimo(nueva, clave)) {
                lista_destruir(nueva, NULL);
                hash_destruir(hash);
                lista_iter_destruir(iter);
                return NULL;
            }
        }
        lista_iter_avanzar(iter);
    }

    lista_iter_destruir(iter);
    hash_destruir(hash);
    return nueva;
}

/* {Orden del algoritmo} *
 * Crear una lista y comprobar si se creó correctamente -> O(1)
 * Crear un hash y comprobar si se creó correctamente -> O(1)
 * Crear el iterador y comprobar si se creó correctamente -> O(1)
 * Al iterar sobre la lista:
 *  Ver la clave actual -> O(1)
 *  Comprobar si la clave ya está en el hash -> O(1)
 *  Si no está, insertarla en la lista e insertarla en el hash (con sus debidas comprobaciones) -> O(1)
 *  Avanzar el iterador -> O(1)
 * Iteración sobre la lista -> n O(1) -> O(n)
 * Destruir el iterador -> O(1)
 * Destruir el hash -> O(1)
 * Total -> O(n) Lineal ✓
 */