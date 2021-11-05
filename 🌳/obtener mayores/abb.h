#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>
#include "lista.h"

/* Tipos de función para comparar claves y destruir datos. */
typedef int (*abb_comparar_clave_t)(const char *, const char *);
typedef void (*abb_destruir_dato_t)(void *);

typedef struct abb abb_t;
struct abb_iter;
typedef struct abb_iter abb_iter_t;

// TODO
lista_t* abb_mayores(const abb_t* abb, const char* clave);

/* Primitivas del mapa. */
abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);

lista_t* abb_obtener_claves(abb_t* abb);

/* Implementa el iterador interno.
   "visitar" es una función de callback que recibe la clave, el valor y un
   puntero extra, y devuelve true si se debe seguir iterando, false en caso
   contrario).
 */
void abb_in_order(abb_t *arbol,
                  bool visitar(const char *, void *, void *),
                  void *extra);

/* Primitivas del iterador externo. */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

bool abb_iter_in_avanzar(abb_iter_t *iter);

const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

bool abb_iter_in_al_final(const abb_iter_t *iter);

void abb_iter_in_destruir(abb_iter_t *iter);

#endif  // ABB_H