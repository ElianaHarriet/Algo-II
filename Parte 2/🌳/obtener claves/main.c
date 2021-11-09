// Implementar una primitiva para el ABB, que devuelva una lista con las claves
// del mismo, ordenadas tal que si insertáramos las claves en un ABB vacío, dicho
// ABB tendría la misma estructura que el árbol original.
#include "abb.h"
#include "abb_struct.h"
#include "lista.h"
#include <stddef.h>

lista_t* _abb_obtener_claves(abb_nodo_t* nodo, lista_t* lista) {
    if (nodo == NULL) {
        return lista;
    }
    lista_insertar_ultimo(lista, nodo->clave);
    _abb_obtener_claves(nodo->izq, lista);
    _abb_obtener_claves(nodo->der, lista);
    return lista;
}

lista_t* abb_obtener_claves(abb_t* abb) {
    lista_t* lista = lista_crear();
    if (abb_cantidad(abb) == 0) return lista;

    return _abb_obtener_claves(abb->raiz, lista);
}

/*
orden_por_nivel(raíz)
     cola = nueva cola
     cola.encola(raíz)
     mientras not cola.vacía hacer
          nodo := cola.desencola()
          visita(nodo)
          si nodo.izquierdo ≠ null entonces
               cola.encola(nodo.izquierdo)
          si nodo.derecho ≠ null entonces
               cola.encola(nodo.derecha)
*/