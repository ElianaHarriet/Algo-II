#include "tp0.h"
#include <stdio.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0){
        return -1;
    }

    int pos_max = 0;
    for (int i = 1; i < n; i++) {
        if (vector[i] > vector[pos_max]) {
            pos_max = i;
        }
    }
    return pos_max;
}

int comparar(int vector1[], int n1, int vector2[], int n2) {
    for (int i = 0; i < n1 && i < n2; i++) {
        // vector1 es más corto que vector2 o el valor en la posición i
        //                      de vector1 es más chico que el de vector2
        if (vector1[i] < vector2[i]) {
            return -1;
        }
        if (vector1[i] > vector2[i]) {
            return 1;
        }
    }

    int menor;
    menor = n1 < n2 ? -1 : 
            n1 > n2 ?  1 : 0;
    return menor;
}

void seleccion(int vector[], int n) {
    for (int i = 0; i < n; i++) {
        int pos_max = maximo(vector, n - i);
        swap(&vector[n - i - 1], &vector[pos_max]);
    }
}
