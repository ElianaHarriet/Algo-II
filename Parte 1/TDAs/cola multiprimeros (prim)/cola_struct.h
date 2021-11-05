#ifndef COLA_STR
#define COLA_STR

/* Definicion del tipo de datos para poder acceder desde la actividad*/

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} nodo_t;

struct cola {
    nodo_t *prim;
    nodo_t *ult;
};

#endif
