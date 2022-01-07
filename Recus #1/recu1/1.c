// Implementar un algoritmo que reciba una cadena conformada por paréntesis, llaves y/o corchetes (de apertura y cierre),
// y determine si la expresión dada por dicha cadena se encuentra balanceada. Esto quiere decir, que cada apertura tenga
// su correspondiente cierre en el orden también correspondiente. El algoritmo debe ejecutar en tiempo lineal a la cantidad
// de caracteres de la cadena. Justifica la complejidad del algoritmo implementado. Pista: pensar en utilizar alguna de las
// estructuras vistas en clase. Ejemplos:
// [(]) --> false
// (())} --> false
// {(} --> false
// [({}{}[(){}])] --> true
#include <stdbool.h>
#include "pila.h"
#include <stdlib.h>

bool balanceado(char* cadena, size_t n) {
    pila_t* pila = pila_crear();

    for (size_t i = 0; i < n; i++) {
        char c = cadena[i];
        if (c == '(' || c == '[' || c == '{') {
            pila_apilar(pila, &c);
        } else {
            if (pila_esta_vacia(pila)) {
                pila_destruir(pila);
                return false;
            }
            char desapilado = *(char*) pila_desapilar(pila);
            if (c == ')' && desapilado != '(') {
                pila_destruir(pila);
                return false;
            }
            if (c == ']' && desapilado != '[') {
                pila_destruir(pila);
                return false;
            }
            if (c == '}' && desapilado != '{') {
                pila_destruir(pila);
                return false;
            }
    }
    
    bool vacia = pila_esta_vacia(pila);
    pila_destruir(pila);
    return vacia;
}

/* {Complejidad del algoritmo} *
 * (Siendo N la cantidad de elementos en la cadena)
 * Crear una pila -> O(1)
 * Dentro del ciclo:
 *  Ver caracter, si es una apertura -> apilar -> O(1)
 *  Ver caracter, si es una cierre -> desapilar y evaluar si es correcto -> O(1)
 * Ciclo for -> repite N veces O(1) => O(N)
 * Ver si está vacía la pila -> O(1)
 * Destruir la pila -> O(1)
 * =>> O(N) Lineal
 */
