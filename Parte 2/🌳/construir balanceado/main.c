// Implementar una función que reciba un arreglo ordenado y devuelva una lista con los
// elementos en orden para ser insertados en un ABB, de tal forma que al insertarlos en
// dicho orden se asegure que el ABB quede balanceado. ¿Cómo cambiarías tu resolución si
// en vez de querer guardarlos en un ABB se fueran a insertar en un AVL?
#include "main.h"

void _desorden_crear_abb(char**claves, size_t desde, size_t hasta, lista_t* lista) {
    if (desde + 1 == hasta) {
        lista_insertar_ultimo(lista, claves[desde]);
        return;
    }
    size_t medio = (desde + hasta) / 2;
    lista_insertar_ultimo(lista, claves[medio]);
    _desorden_crear_abb(claves, desde, medio, lista);
    _desorden_crear_abb(claves, medio + 1, hasta, lista);
}


lista_t* desorden_crear_abb(char** claves, size_t n) {
    lista_t* lista = lista_crear();
    _desorden_crear_abb(claves, 0, n, lista);
    return lista;
}