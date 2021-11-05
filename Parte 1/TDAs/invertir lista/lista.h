#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

// Definicion del tipo de datos
typedef struct lista lista_t;

/*
 * Primitivas de lista simplemente enlazada
 */

// TODO
void* lista_ante_k_ultimo(lista_t* lista, size_t k);

// Crea una lista
// Post: Se devuelve una nueva lista.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento al principio de la lista
// Pre: la lista fue creada
// Post: se agregó un nodo con el dato recibido, al principio de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Borra el primer elemento de la lista
// Pre: la lista fue creada
// Post: se eliminó el primer nodo de la lista, se devuelve el dato contenido.
// En caso de lista vacía devuelve NULL.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el contenido de dato del primer nodo
// Pre: la lista fue creada
// Post: devuelve el valor almacenado en el primer dato, en caso de lista
// vacía devuelve NULL.
void *lista_ver_primero(const lista_t *lista);

// Obtener largo
// Pre: la lista fue creada
// Post: devuelve la cantidad de elementos almacenados
size_t lista_largo(const lista_t *lista);

// Destruye la lista
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/*
 * Primitivas de iterador interno
 */

// Iterador interno de la lista.
// Recorre la lista y para cada elemento de la misma llama a
// la función visitar, pasándole por parámetro el elemento de la lista
// (dato) y el parámetro extra.
// El parámetro extra sirve para que la función visitar pueda recibir
// información adicional. Puede ser NULL.
// La función visitar debe devolver true si se debe seguir iterando,
// false para cortar la iteración. No puede agregar ni quitar elementos
// a la lista).
// Pre: la lista fue creada.
// Post: se llamó a la función visitar una vez por cada elemento de la lista,
// en orden.
void lista_iterar(
    lista_t *lista,
    bool (*visitar)(void *dato, void *extra),
    void *extra
);

#endif // LISTA_H
