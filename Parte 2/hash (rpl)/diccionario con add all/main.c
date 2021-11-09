// Se quiere implementar un TDA Diccionario con las siguientes primitivas:
// obtener(x) devuelve el valor de x en el diccionario;
// insertar(x, y) inserta en el diccionario la clave x con el valor y (entero);
// borrar(x) borra la entrada de x;
// add(x, n) le suma n al contenido de x;
// add_all(m) le suma m a todos los valores.

// Proponer una implementación donde todas las operaciones sean O(1).
// Justificar el orden de las operaciones.

// (En general un ejercicio así podría plantearse solo describiendo, pero para quienes
// quieran corroborarlo, en esta plataforma se encuentra definido el ejercicio en C)
#include "dic_all.h"
#include "hash.h"
#include "cola.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Pueden agregar la dependencia al TDA que quieran, inclusive agregar archivos de otros
// TDAs que hayan implementado ustedes

struct dic_all {
    hash_t *hash;
    cola_t* cola;
    size_t tam;
};

dic_all_t* dic_all_crear() {
    hash_t* hash = hash_crear(NULL);
    cola_t* cola = cola_crear();
    if (!hash || !cola) {
        hash_destruir(hash);
        cola_destruir(cola, NULL);
        return NULL;
    }
    dic_all_t* dic = malloc(sizeof(dic_all_t));
    if (!dic) {
        hash_destruir(hash);
        cola_destruir(cola, NULL);
        return NULL;
    }
    dic->hash = hash;
    dic->cola = cola;
    dic->tam = 0;
    return dic;
}

bool dic_all_guardar(dic_all_t* dic, const char* clave, int dato) {
    int* num = malloc(sizeof(int));
    *num = dato;
    if (hash_guardar(dic->hash, clave, num)) {
        cola_encolar(dic->cola, num);
        dic->tam++;
        return true;
    }
    free(num);
    return false;
}

int dic_all_obtener(dic_all_t* dic, const char* clave) {
    return hash_pertenece(dic->hash, clave) ? *(int*)hash_obtener(dic->hash, clave) : 0;
}

int dic_all_borrar(dic_all_t* dic, const char* clave) {
    if (!hash_pertenece(dic->hash, clave)) {
        return 0;
    }
    int dato = *(int*)hash_borrar(dic->hash, clave);
    while (*(int*)cola_ver_primero(dic->cola) != dato) {
        cola_encolar(dic->cola, cola_desencolar(dic->cola));
    }
    cola_desencolar(dic->cola);
    dic->tam--;
    return dato;
}

bool dic_all_add(dic_all_t* dic, const char* clave, int valor) {
    if (!hash_pertenece(dic->hash, clave)) {
        return false;
    }
    int dato = *(int*)hash_obtener(dic->hash, clave);
    while (*(int*)cola_ver_primero(dic->cola) != dato) {
        cola_encolar(dic->cola, cola_desencolar(dic->cola));
    }
    *(int*)cola_ver_primero(dic->cola) += valor;
    return true;
}

void dic_all_add_all(dic_all_t* dic, int valor) {
    for (size_t i = 0; i < dic->tam; i++) {
        int* num = cola_desencolar(dic->cola);
        *num += valor;
        cola_encolar(dic->cola, num);
    }
}

void dic_all_destruir(dic_all_t* dic) {
    hash_destruir(dic->hash);
    cola_destruir(dic->cola, NULL);
    free(dic);
}