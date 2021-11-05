#ifndef COMPOSICION_H
#define COMPOSICION_H

#include <stdbool.h>
#include <stddef.h>

struct composicion;

typedef struct composicion composicion_t;

typedef double (*funcion_t)(double);

composicion_t* composicion_crear();

void composicion_destruir(composicion_t*);

bool composicion_agregar_funcion(composicion_t*, funcion_t);

double composicion_aplicar(composicion_t*, double);

#endif // COMPOSICION_H
