// Asumiendo que se tiene disponible una implementación completa del TDA Hash, se desea
// implementar una función que decida si dos Hash dados representan o no el mismo
// Diccionario. Considere para la solución que es de interés la mejor eficiencia temporal
// posible. Indique, para su solución, eficiencia en tiempo y espacio. Nota: Dos tablas de
// hash representan el mismo diccionario si tienen la misma cantidad de elementos; todas
// las claves del primero están en el segundo; todas las del segundo, en el primero; y los
// datos asociados a cada una de esas claves son iguales (se pueden comparar los valores
// con “==”).
#include "hash.h"

bool son_iguales(hash_t* a, hash_t* b) {
    hash_iter_t* iter_a = hash_iter_crear(a);

    while(!hash_iter_al_final(iter_a)) {
        char* clave_act = hash_iter_ver_actual(iter_a);
        if (!hash_pertenece(b, clave_act)) {
            hash_iter_destruir(iter_a);
            return false;
        }
        void* valor_a = hash_obtener(a, clave_act);
        void* valor_b = hash_obtener(b, clave_act);
        if (valor_a != valor_b) {
            hash_iter_destruir(iter_a);
            return false;
        }
        hash_iter_avanzar(iter_a);
    }
    hash_iter_destruir(iter_a);

    size_t cant_a = hash_cantidad(a);
    size_t cant_b = hash_cantidad(b);
    return cant_a == cant_b;
}