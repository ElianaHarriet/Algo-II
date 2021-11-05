#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "hash.h"


/* *********************************************************************
 *               DEFINICIÓN DE LOS TIPOS DE DATOS
 * *********************************************************************/

/* Definición del hash_t, campo_t y estado_t */
typedef enum estado {
    VACIO, OCUPADO, BORRADO
} estado_t;

typedef struct campo {
  char* clave;
  void* valor;
  estado_t estado;
} campo_t;

struct hash {
  size_t capacidad;
  size_t cantidad;
  hash_destruir_dato_t funcion_destruccion;
  campo_t* tabla;
};


/* Definición del hash_iter */
struct hash_iter {
  const hash_t* hash;
  campo_t campo_act;
  size_t posicion;
};



/* *********************************************************************
 *                        FUNCIONES AUXILIARES
 * *********************************************************************/

/* Función de hashing para cadenas -> Fowler/Noll/Vo (FNV) hash function, variant 1a */
size_t fnv1a(const char *clave, size_t capacidad){
	size_t hash = 0x811c9dc5;
	while (*clave){
		hash ^= (unsigned char) *clave++;
		hash *= 0x01000193;
	}
	return (hash % capacidad);
} // {https://codereview.stackexchange.com/questions/85556/simple-string-hashing-algorithm-implementation}

/* Obtiene el índice de una clave en la tabla de hash */
size_t obtener_indice(const hash_t* hash, const char* clave) {
    size_t indice = fnv1a((const char*)clave, hash->capacidad); 
    campo_t actual = hash->tabla[indice];
    while (actual.estado != VACIO && (actual.estado == BORRADO || strcmp(actual.clave, clave) != 0)) {
        indice = (indice + 1) % hash->capacidad;
        actual = hash->tabla[indice];
    }
    return indice;
}

/* Destruye un dato de la tabla de hash */
void func_destruccion(hash_t* hash, size_t indice) {
    if (hash->funcion_destruccion != NULL) {
        hash->funcion_destruccion(hash->tabla[indice].valor);
    }
}

/* Inicia el estado de cada campo del hash como VACIO */
void llenar_vacio(hash_t* hash) {
    for(int i = 0; i < hash->capacidad; i++) {
        hash->tabla[i].estado = VACIO;
    }
}

/* Elimina la tabla vieja tras guradar cada clave-valor en la nueva tabla del hash */
void liberar_tabla(hash_t* hash, campo_t* tabla_vieja, size_t capacidad_vieja) {
    for (int i = 0; i < capacidad_vieja; i++) {
        if (tabla_vieja[i].estado == OCUPADO) {
            hash_guardar(hash, tabla_vieja[i].clave, tabla_vieja[i].valor);
            free(tabla_vieja[i].clave);
        }
    }
}

/* Devuelve una copia de la clave, en el caso en que la clave no se encuentre en el hash
   la crea usando la función strdup, en caso contrario destruye el dato guardado con esa
   clave (que posteriormente en la primitiva hash_guardar será reemplazado por el nuevo)
   y devuelve la misma clave que estaba guardada en dicho indice                        */
char* devolver_copia(hash_t* hash, size_t indice, const char* clave) {
    if (hash->tabla[indice].estado != OCUPADO) {
        hash->cantidad++;
        return strdup(clave);
    }
    func_destruccion(hash, indice);
    return hash->tabla[indice].clave;
}

/* Redimensiona la tabla de hash a la capadicad indicada */
bool hash_redimensionar(hash_t* hash, size_t capacidad) {
    campo_t* tabla_nueva = malloc(sizeof(campo_t) * capacidad);
    if (tabla_nueva == NULL){
        return false;
    }
    size_t capacidad_vieja = hash->capacidad;
    campo_t* tabla_vieja = hash->tabla;
    hash->tabla = tabla_nueva;
    hash->capacidad = capacidad;
    hash->cantidad = 0;
    llenar_vacio(hash);
    liberar_tabla(hash, tabla_vieja, capacidad_vieja);
    free(tabla_vieja);
    return true;
}

/* Avanza una posición al iterador del hash */
size_t avanzar_pos(hash_iter_t* iter) {
    size_t posicion = iter->posicion;
    posicion++;
    if (posicion < iter->hash->capacidad) {
        iter->campo_act = iter->hash->tabla[posicion];
    }
    while(posicion < iter->hash->capacidad && iter->hash->tabla[posicion].estado != OCUPADO){
        posicion++;
        if (posicion < iter->hash->capacidad) {
            iter->campo_act = iter->hash->tabla[posicion];
        }
    }
    return posicion;
}



/* *********************************************************************
 *                        PRIMITIVAS DEL HASH
 * *********************************************************************/

hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL) {
        return NULL;
    }
    campo_t* tabla = malloc(sizeof(campo_t) * 23);
    if (tabla == NULL) {
        free(hash);
        return NULL;
    }
    hash->cantidad = 0;
    hash->capacidad = 23;
    hash->tabla = tabla;
    hash->funcion_destruccion = destruir_dato;
    llenar_vacio(hash);
    return hash;
}

bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
    size_t indice = obtener_indice(hash, clave);
    char* copia_clave = devolver_copia(hash, indice, clave);
    hash->tabla[indice].clave = copia_clave;
    hash->tabla[indice].valor = dato;
    hash->tabla[indice].estado = OCUPADO;
    float fact_carg = (float)hash->cantidad / (float)hash->capacidad;
    if (fact_carg >= 0.55) {
        return hash_redimensionar(hash, hash->capacidad * 2);
    }
    return true;
}

void* hash_borrar(hash_t* hash, const char* clave) {
    size_t indice = obtener_indice(hash, clave);
    if(hash->tabla[indice].estado != OCUPADO){
        return NULL;
    }
    hash->tabla[indice].estado = BORRADO;
    free(hash->tabla[indice].clave);
    hash->cantidad--;
    float fact_carg = (float)hash->cantidad / (float)hash->capacidad;
    void* dato = hash->tabla[indice].valor;
    if (fact_carg <= 0.05 && hash->capacidad >= 46) { 
        bool redim = hash_redimensionar(hash, hash->capacidad / 2);
        if (!redim) {
            return NULL;
        }
    }
    return dato;
}

void* hash_obtener(const hash_t* hash, const char* clave) {
    size_t indice = obtener_indice(hash, clave);
    if (hash->tabla[indice].estado != OCUPADO) {
        return NULL;
    }
    return hash->tabla[indice].valor;
}

bool hash_pertenece(const hash_t* hash, const char* clave) {
    size_t indice = obtener_indice(hash, clave);
    return hash->tabla[indice].estado == OCUPADO;
}

size_t hash_cantidad(const hash_t* hash) {
    return hash->cantidad;
}
  
void hash_destruir(hash_t* hash) {
    for(size_t i = 0; i < hash->capacidad; i++) {  
        if (hash->tabla[i].estado == OCUPADO) {
            func_destruccion(hash, i);
            free(hash->tabla[i].clave);
        }
    }
    free(hash->tabla);
    free(hash);
}



/* *********************************************************************
 *                 PRIMITIVAS DEL ITERADOR DEL HASH
 * *********************************************************************/

hash_iter_t* hash_iter_crear(const hash_t* hash) {
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(iter == NULL){
        return NULL;
    }
    int i = 0;
    campo_t actual = hash->tabla[i];
    while (actual.estado != OCUPADO){ 
        i++;
        if (i >= hash->capacidad) {
            break;
        }
        actual = hash->tabla[i];
    }
    iter->campo_act = actual;
    iter->hash = hash;
    iter->posicion = i;
    return iter;
}

bool hash_iter_avanzar(hash_iter_t* iter) {
    if (hash_iter_al_final(iter)) {
        return false;
    }
    size_t posicion = avanzar_pos(iter);
    if (posicion < iter->hash->capacidad) {
        iter->campo_act = iter->hash->tabla[posicion];
    }
    iter->posicion = posicion;
    return true;
}

const char* hash_iter_ver_actual(const hash_iter_t* iter) {
    if(!hash_iter_al_final(iter)) {
        campo_t actual = iter->campo_act;
        return actual.clave;
    }
    return NULL;
}

bool hash_iter_al_final(const hash_iter_t* iter) {
    if(iter->posicion == iter->hash->capacidad) {
        return true;
    }
    return false;
}

void hash_iter_destruir(hash_iter_t* iter) {
    free(iter);
}