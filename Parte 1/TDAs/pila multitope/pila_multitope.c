// Implementar la primitiva de la pila void** pila_multitop(const pila_t* pila, size_t n),
// que devuelve un arreglo de tamaño n con los n topes de la pila (los primeros n elementos
// si estos fueran desapilados), sin utilizar estructuras auxiliares. Completar el arreglo
// a devolver con NULL cuando el n recibido por parámetro sea mayor a la cantidad de
// elementos de la pila. Indicar el orden de complejidad de la primitiva. 
#include "pila.h"
#include <stdio.h>

void** pila_multitop(const pila_t* pila, size_t n) {
    if (n == 0) {
        return NULL;
    }
    void** multi = malloc(sizeof(void*) * n);
    for (int i = 0; i < n; i++) {
        if (i < pila->cantidad) {
            multi[i] = pila->datos[pila->cantidad - i - 1];
        } else {
            multi[i] = NULL;
        }
    }
    return multi;
} // T(n) = O(n)






// int main() {
//     pila_t* pila = pila_crear();
//     int valor1 = 0;
//     int valor2 = 1;
//     int valor3 = 2;
//     int valor4 = 3;
//     int valor5 = 4;

//     pila_apilar(pila, &valor1);
//     pila_apilar(pila, &valor2);
//     pila_apilar(pila, &valor3);
//     pila_apilar(pila, &valor4);
//     pila_apilar(pila, &valor5);

//     void** multi = pila_multitop(pila, 3);
//     printf("[");
//     for (int i = 0; i < 3; i++) {
//         printf(i != 2 ? "%d, " : "%d", *(int*)multi[i]);
//     }
//     printf("]\n");
//     return 0;
// }