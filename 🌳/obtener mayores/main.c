// Se tiene un árbol binario de búsqueda con cadenas como claves y función de comparación strcmp.
// Implementar una primitiva lista_t* abb_mayores(const abb_t* abb, const char* cadena) que,
// dados un ABB y una cadena, devuelva una lista ordenada con las claves del árbol estrictamente
// mayores a la cadena recibida por parámetro (que no necesariamente está en el árbol).
#include "abb.h"
#include "lista.h"
#include "abb_struct.h"


void _abb_mayores(const abb_t* abb, const char* clave, lista_t* lista, abb_nodo_t* nodo) {
    if (nodo == NULL) return;
    if (abb->cmp(nodo->clave, clave) > 0) {
        bool insert = lista_insertar_ultimo(lista, nodo->clave);
        _abb_mayores(abb, clave, lista, nodo->izq);
        _abb_mayores(abb, clave, lista, nodo->der);
        return;
    }
    _abb_mayores(abb, clave, lista, nodo->der);
}

lista_t* abb_mayores(const abb_t* abb, const char* clave) {
    lista_t* lista = lista_crear();
    if (!lista) return NULL;
    _abb_mayores(abb, clave, lista, abb->raiz);
    return lista;
}
