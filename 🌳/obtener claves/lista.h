#ifndef _LISTA_H
#define _LISTA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

// lista
typedef struct lista lista_t;

// iterador externo de la lista
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                       PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve true si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve false en
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// principio de la lista. La lista es más larga
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve false en
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// final de la lista. La lista es más larga
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista. Si la lista tiene elementos, 
// se quita el primero y se devuelve el dato, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el dato del primer elemento, la lista tiene un elemento
// menos, si la lista no estaba vacía. La lista es más corta
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el dato del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el dato del primer elemento de la lista o NULL.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del último elemento de la lista. Si la lista tiene
// elementos, se devuelve el dato del últimoo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el dato del último elemento de la lista o NULL.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elemntos en la lista
// Pre: la lista fue creada
// Post: se devolvió el largo de la lista sin modificarla
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));


/* ******************************************************************
 *                  PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

// Se llama a la función visitar para que se encargue de recorrer todos los
// los elementos de la lista hasta que dicha función devuelva falso. El parámetro
// extra es usado dentro de la función visitar a criterio de quien use la lista.
// Pre: la lista fue creada. visitar es una función capaz de realizar una acción
// a cada paso de la iteración. extra es un puntero genérico a un parametro o NULL.
// Post: se iteró la lista al completo o hasta que la función visitar devolvió false
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
 *                   PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea una iterador. Devuelve NULL en caso de error.
// Post: devuelve un nuevo iterador.
lista_iter_t *lista_iter_crear(lista_t *lista);


// Devuelve false en caso de error. Avanza en las posiciones de la lista.
// Pre: la lista y el iterador se crearon.
// Post: se avanzó una posicion en la lista .
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor actual en el que el iterador esta parado.
// Pre: la lista y el iterador se crearon.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador esta parado al final, false de lo contrario.
// Pre: se creo el iterador y la lista.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador, la lista queda intacta.
// Pre: la lista y el iterador se crearon.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un dato a la lista en la posicion del iterador.
// Pre: se creo el iterador y la lista.
// Post: el iterador esta parado en la misma posicion y se agrandó la lista
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra el dato en el que el iterador esta parado.
// Pre: se creo el iterador y la lista.
// Post: Se borro el dato de la posicion del iterador. Se achico la lista y el
// iterador sigue en la misma posicion.
void *lista_iter_borrar(lista_iter_t *iter);


/* *****************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
void pruebas_lista_estudiante(void);

#endif  // _LISTA_H
