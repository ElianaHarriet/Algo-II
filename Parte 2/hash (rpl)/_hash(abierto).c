#include "hash.h"
#include "lista.h"


/* *********************************************************************
 *                  DEFINICIÓN DE LOS TIPOS DE DATOS
 * *********************************************************************/

/* Definición del tipo de dato hash_nodo_t y hash_t */

typedef struct hash_nodo {
    char* clave;
    void* dato;
} hash_nodo_t;

typedef struct hash {
    size_t cantidad;
    size_t capacidad;
    lista_t** tabla;
    hash_destruir_dato_t destruir_dato;
} hash_t;

/* Estructura del iterador */
typedef struct hash_iter {
    const hash_t *hash;
    size_t pos;
    lista_iter_t* iter_l;
} hash_iter_t;



/* *********************************************************************
 *                        FUNCIONES AUXILIARES
 * *********************************************************************/

char* strdup(const char* org) {
    char* cpy = malloc(sizeof(char) * (strlen(org) + 1));
    if (!cpy) return NULL;
    strcpy(cpy, org);
    return cpy;
}

size_t fnv1a(const char *clave, size_t largo_primo){
	size_t hash = 0x811c9dc5;
	while (*clave){
		hash ^= (unsigned char) *clave++;
		hash *= 0x01000193;
	}
	return (hash % largo_primo);
}


// /* Función para saber si un número es primo */
// bool es_primo(size_t num) {
//     size_t i;
//     for (i = 2; i < num / 2; i++) {
//         if (num % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }

// /* Función para hallar un número primo mayor al número pasado por parámetro */
// size_t primo_mayor(size_t num) {
//     size_t i;
//     for (i = num; ; i++) {
//         if (es_primo(i)) {
//             return i;
//         }
//     }
// }

// /* Función para hallar un número primo menor al número pasado por parámetro */
// size_t primo_menor(size_t num) {
//     size_t i;
//     for (i = num; ; i--) {
//         if (es_primo(i)) {
//             return i;
//         }
//     }
// }

/* *********************************************************************
 *                        PRIMITIVAS DEL HASH
 * *********************************************************************/

hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash) {
        return NULL;
    }
    hash->cantidad = 0;
    hash->capacidad = 23;
    hash->tabla = malloc(sizeof(lista_t*) * hash->capacidad);
    if (!hash->tabla) {
        free(hash);
        return NULL;
    }
    for (size_t i = 0; i < hash->capacidad; i++) {
        hash->tabla[i] = lista_crear();
        if (!hash->tabla[i]) {
            for (size_t j = 0; j < i; j++) {
                lista_destruir(hash->tabla[j], destruir_dato);
            }
            free(hash->tabla);
            free(hash);
            return NULL;
        }
    }
    hash->destruir_dato = destruir_dato;
    return hash;
}

bool hash_redimensionar(hash_t* hash, size_t nueva_capacidad) {
    lista_t** nueva_tabla = malloc(sizeof(lista_t*) * nueva_capacidad);
    if (!nueva_tabla) {
        return false;
    }
    for (size_t i = 0; i < nueva_capacidad; i++) {
        nueva_tabla[i] = lista_crear();
    }
    for (size_t i = 0; i < hash->capacidad; i++) {
        lista_t* lista = hash->tabla[i];
        lista_iter_t* iter = lista_iter_crear(lista);
        if (!iter) {
            return false;
        }
        while (!lista_iter_al_final(iter)) {
            hash_nodo_t* nodo = lista_iter_ver_actual(iter);
            size_t pos = fnv1a((const char*)nodo->clave, nueva_capacidad);
            if (!lista_insertar_ultimo(nueva_tabla[pos], nodo)) {
                return false;
            }
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
        lista_destruir(lista, NULL); // ->> Si hubo un problema en algún momento y no se terminó
    }                               // de hacer se pueden perder datos, poner en otro ciclo
    free(hash->tabla);
    hash->tabla = nueva_tabla;
    hash->capacidad = nueva_capacidad;
    return true;
}

hash_nodo_t* nodo_buscar(lista_t* lista, const char* clave) {
    lista_iter_t* iter = lista_iter_crear(lista);
    if (!iter) {
        return NULL;
    }
    while (!lista_iter_al_final(iter)) {
        hash_nodo_t* nodo = lista_iter_ver_actual(iter);
        if (!strcmp(nodo->clave, clave)) {
            lista_iter_destruir(iter);
            return nodo;
        }
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
    return NULL;
}

bool hash_pertenece(const hash_t* hash, const char* clave) {
    size_t pos = fnv1a((const char*)clave, hash->capacidad);
    lista_t* lista = hash->tabla[pos];
    hash_nodo_t* nodo = nodo_buscar(lista, clave);
    return nodo != NULL;
}

void* hash_obtener(const hash_t* hash, const char* clave) {
    size_t pos = fnv1a((const char*)clave, hash->capacidad);
    lista_t* lista = hash->tabla[pos];
    hash_nodo_t* nodo = nodo_buscar(lista, clave);
    return nodo ? nodo->dato : NULL;
}    

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    size_t indice = fnv1a((const char*)clave, hash->capacidad);
    lista_t* lista_indice = hash->tabla[indice];
    hash_nodo_t* nodo_pertenece = nodo_buscar(lista_indice, clave);
    if (nodo_pertenece) {
        if (hash->destruir_dato) {
            hash->destruir_dato(nodo_pertenece->dato);
        }
        nodo_pertenece->dato = dato;
    } else {
        char* copia_clave = strdup(clave);
        hash_nodo_t* nodo = malloc(sizeof(hash_nodo_t));
        if (!nodo){
            return false;
        }
        nodo->clave = copia_clave;
        nodo->dato = dato;
        bool insert = lista_insertar_ultimo(lista_indice, nodo);
        if (!insert) {
            free(copia_clave);
            free(nodo);
            return false;
        }
        hash->cantidad++;
    }
    if (hash_cantidad((const hash_t*)hash) >= hash->capacidad * 2) { // ir variando y probar velocidad
        return hash_redimensionar(hash, primo_mayor(hash->capacidad * 2));
    }
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t indice = fnv1a((const char*)clave, hash->capacidad);
    lista_t* lista_indice = hash->tabla[indice];
    lista_iter_t* iterador = lista_iter_crear(lista_indice);
    if(!iterador){
        return NULL;
    }
    for(int i=0; i<lista_largo(lista_indice);i++){
        hash_nodo_t* nodo_actual = lista_iter_ver_actual(iterador);
        const char* clave_actual = nodo_actual->clave;
        if(strcmp(clave_actual, clave) == 0) {
            lista_iter_borrar(iterador);
            void* dato = nodo_actual->dato;
            free(nodo_actual->clave);
            hash->cantidad--;
            // free(clave_actual);
            free(nodo_actual);
            if (hash_cantidad((const hash_t*)hash) >= 47 && hash_cantidad((const hash_t*)hash) <= (float)hash->capacidad * 0.125) { // ir variando y probar velocidad
                bool redim = hash_redimensionar(hash, hash->capacidad / 2);   /// ver para este casooooooo....
                if (!redim) {
                    return NULL;
                }
            }
            lista_iter_destruir(iterador);
            return dato;
        }
        lista_iter_avanzar(iterador);
    }
    lista_iter_destruir(iterador);
    return NULL;
}

    

void hash_destruir(hash_t* hash) {
    for (size_t i = 0; i < hash->capacidad; i++) {
        lista_iter_t* iter = lista_iter_crear(hash->tabla[i]);
        while (!lista_iter_al_final(iter)) {
            hash_nodo_t* nodo = lista_iter_ver_actual(iter);
            if (hash->destruir_dato) {
                hash->destruir_dato(nodo->dato);
            }
            free(nodo->clave);
            free(nodo);
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
        lista_destruir(hash->tabla[i], NULL);
    }
    free(hash->tabla);
    free(hash);
}

size_t hash_cantidad(const hash_t* hash) {
    return hash->cantidad;
}



/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t* iterador = malloc(sizeof(hash_iter_t));
    if(!iterador){
        return NULL;
    }
    int pos = 0;
    while(pos < hash->capacidad && lista_esta_vacia(hash->tabla[pos])){
        pos++;
    }
    iterador->hash = hash;
    iterador->pos = pos;
    if (pos == hash->capacidad) {
        iterador->iter_l = NULL;
        return iterador;
    }
    // if(pos != 0){
        lista_t* lista_indice = hash->tabla[pos];
        lista_iter_t* iterador_lista = lista_iter_crear(lista_indice);
        iterador->iter_l = iterador_lista;
    // }
    return iterador;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->pos == iter->hash->capacidad;
}

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter){
    if (hash_iter_al_final(iter)) {
        return false;
    }
    lista_iter_t* iterador_lista = iter->iter_l;
    lista_iter_avanzar(iterador_lista);
    if(!lista_iter_al_final(iterador_lista)){
        return true;
    }
    lista_iter_destruir(iter->iter_l);
    size_t pos = iter->pos + 1;
    while(pos < iter->hash->capacidad && lista_esta_vacia(iter->hash->tabla[pos])){
        pos++;
    }
    iter->pos = pos;
    if(pos == iter->hash->capacidad){
        iter->iter_l = NULL;
        return true;
    }
    lista_t* nueva_lista = iter->hash->tabla[pos];
    lista_iter_t* nuevo_iter = lista_iter_crear(nueva_lista);
    if(!nuevo_iter){
        return false;
    }
    iter->iter_l = nuevo_iter;
    return true;

}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if(hash_iter_al_final(iter)){
        return NULL;
    }
    lista_iter_t* iter_lista = iter->iter_l;
    hash_nodo_t* nodo_actual = lista_iter_ver_actual(iter_lista);
    return nodo_actual->clave;
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t *iter){
    if (iter->iter_l) {
        lista_iter_destruir(iter->iter_l);
    }
    free(iter);
}