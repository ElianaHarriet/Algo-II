#ifndef COLA_FILTRAR
#define COLA_FILTRAR

#include "cola.h"

void cola_filtrar(cola_t* cola, bool (*filtro)(void*));

#endif
