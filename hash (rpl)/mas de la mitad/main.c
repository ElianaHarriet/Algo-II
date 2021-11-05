// Implementar una función de orden O(n) que dado un arreglo de n números enteros devuelva
// true o false según si existe algún elemento que aparezca más de la mitad de las veces.
// Justificar el orden de la solución. Ejemplos:

// [1, 2, 1, 2, 3] -> false
// [1, 1, 2, 3] -> false
// [1, 2, 3, 1, 1, 1] -> true
// [1] -> true

// #include "main.h" // No borrar
#include "hash.h"

bool mas_de_mitad(void* arreglo[], size_t n) {
    hash_t* hash = hash_crear(NULL);
    for (int i = 0; i < n; i++) {
        char* clave = malloc(sizeof(char) * 20);
        sprintf(clave, "%d", *(int*)arreglo[i]); 

        int* veces = malloc(sizeof(int));
        *veces = hash_pertenece(hash, clave) ? *(int*)hash_obtener(hash, clave) + 1 : 1;
        hash_guardar(hash, clave, veces);
        if (*veces > n / 2) {
            hash_destruir(hash);
            return true;
        }
    }
    hash_destruir(hash);
    return false;
}