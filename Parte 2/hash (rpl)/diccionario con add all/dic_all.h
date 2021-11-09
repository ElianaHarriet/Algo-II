#ifndef DIC_ALL_H
#define DIC_ALL_H

#include <stdbool.h>

typedef struct dic_all dic_all_t;

dic_all_t* dic_all_crear();

bool dic_all_guardar(dic_all_t* dic, const char* clave, int dato);

int dic_all_obtener(dic_all_t* dic, const char* clave);

int dic_all_borrar(dic_all_t* dic, const char* clave);

bool dic_all_add(dic_all_t* dic, const char* clave, int valor);

void dic_all_add_all(dic_all_t* dic, int valor);

void dic_all_destruir(dic_all_t* dic);

#endif