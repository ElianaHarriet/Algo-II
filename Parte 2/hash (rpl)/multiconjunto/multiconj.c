// Implementar el TDA MultiConjunto. Este es un Conjunto que permite más de una
// aparición de un elemento, por lo que eliminando una aparición, el elemento
// puede seguir perteneciendo. Dicho TDA debe tener como primitivas:

// •multiconj_t* multiconj_crear(): crea un multiconjunto.
// •bool multiconj_guardar(multiconj_t* multiconj, const char* elem): guarda un
//   elemento en el multiconjunto. Devuelve true si se pudo guardar el elemento
//   correctamente, false en caso contrario.
// •bool multiconj_pertenece(const multiconj_t* multiconj, const char* elem):
//   devuelve true si el elemento aparece al menos una vez en el conjunto.
// •bool multiconj_borrar(multiconj_t* multiconj, const char* elem): elimina una
//   aparición del elemento dentro del conjunto. Devuelve true si se eliminó una
//   aparición del elemento.
// •void multiconj_destruir(multiconj_t* multiconj) que libera la memoria asociada
//   al TDA.

// Dar la estructura del TDA y la implementación de las 4 primitivas marcadas, de
// forma tal que todas sean de tiempo constante.

#include "hash.h"
#include "multiconj.h"
#include <stdbool.h>
#include <stdlib.h>

/* Estructura de TDA multiconjunto */
struct multiconj {
    hash_t* hash;
};

multiconj_t* multiconj_crear() {
    multiconj_t* multiconj = malloc(sizeof(multiconj_t));
    if (!multiconj) return NULL;
    multiconj->hash = hash_crear(free);
    if (!multiconj->hash) {
        free(multiconj);
        return NULL;
    }
    return multiconj;
}

bool multiconj_guardar(multiconj_t* multiconj, const char* elem) {
    void* valor = hash_obtener(multiconj->hash, elem);
    if (valor) {
        *(int*)valor += 1;
        return true;
    }
    int* valor_nuevo = malloc(sizeof(int));
    if (!valor_nuevo) return false;
    *valor_nuevo = 1;
    return hash_guardar(multiconj->hash, elem, valor_nuevo);
}

bool multiconj_pertenece(const multiconj_t* multiconj, const char* elem) {
    return hash_pertenece(multiconj->hash, elem);
}

bool multiconj_borrar(multiconj_t* multiconj, char* elem) {
    void* valor = hash_obtener(multiconj->hash, elem);
    if (!valor) return false;
    if (*(int*)valor == 1) {
        free(hash_borrar(multiconj->hash, elem));
        return true;
    }
    *(int*)valor -= 1;
    return true;
}

void multiconj_destruir(multiconj_t* multiconj) {
    hash_destruir(multiconj->hash);
    free(multiconj);
}