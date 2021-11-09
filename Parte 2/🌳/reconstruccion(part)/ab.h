#ifndef AB_H
#define AB_H

#include <stddef.h>
// #include "lista.h"

typedef struct ab ab_t;

struct ab {
    ab_t* izq;
    ab_t* der;
    char dato;
};

ab_t* ab_crear(char dato);

// A implementar
ab_t* arbol_con_recorridos();

// void ab_destruir(ab_t* ab);

// // para las pruebas
// lista_t* ab_pre_order(ab_t* ab);
// lista_t* ab_in_order(ab_t* ab);

#endif