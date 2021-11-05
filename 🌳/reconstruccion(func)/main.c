// #include "main.h"
#include "ab.h"
#include "hash.h"
#include <stddef.h>
#include <string.h>

void reconstruir(ab_t* arbol, char* inorder, char dato){
    if (arbol == NULL) {
        return;
    }
    size_t ind_guardada = NULL;
    size_t ind_letra = NULL;
    for (size_t i = 0; i < strlen(inorder); i++) {
        if (inorder[i] == arbol->dato) {
            ind_guardada = i;
        }
        if (inorder[i] == dato) {
            ind_letra = i;
        }
        if (ind_guardada != NULL && ind_letra != NULL) {
            break;
        }
    }
    if (ind_letra > ind_guardada) {
        if (arbol->der) {
            reconstruir(arbol->der, inorder, dato);
        } else {
            arbol->der = ab_crear(dato);
        }
    } else {
        if (arbol->izq) {
            reconstruir(arbol->izq, inorder, dato);
        } else {
            arbol->izq = ab_crear(dato);
        }
    }
}


ab_t* ab_reconstruir(char* preorder, char* inorder) {
    size_t len = strlen(preorder);
    if (len == 0) {
        return NULL;
    }
    ab_t* arbol = ab_crear(preorder[0]);
    for (size_t j = 1; j < len; j++){
        reconstruir(arbol, inorder, preorder[j]);
    }
    return arbol;
}