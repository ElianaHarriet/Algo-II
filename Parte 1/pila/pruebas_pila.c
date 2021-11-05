#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                              PRUEBAS
 * *****************************************************************/

/* Pruebas para una pila vacía */
static void pruebas_pila_vacia(void) {
    printf("༺ INICIO DE PRUEBAS CON UNA PILA VACÍA ༻\n");

    /* Variables a utilizar */
    pila_t* pila = pila_crear();

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una pila", pila != NULL);
    print_test("    ๛ La pila está vacía", pila_esta_vacia(pila));

    /* Pruebo que ver el tope de la pila devuelva NULL */
    print_test("    ๛ Ver tope devuelve NULL", pila_ver_tope(pila) == NULL);

    /* Pruebo que desapilar también devuelva NULL */
    print_test("    ๛ Desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    /* Destruyo la pila */
    pila_destruir(pila);
}

void pruebas_pila_algunos_elementos(void) {
    printf("༺ INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS ༻ \n");

    /* Variables a utilizar */
    pila_t* pila = pila_crear();
    int num[5] ; 
    int* valor1 = &num[0];
    int* valor2 = &num[1];
    int* valor3 = &num[2];
    int* valor4 = &num[3];
    int* valor5 = &num[4];

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una pila", pila != NULL);
    print_test("    ๛ La pila está vacía", pila_esta_vacia(pila));

    /* Pruebo que apilar los 5 valores devuelva true
        y que en el transcurso los topes vayan cambiando a los adecuados */
    print_test("    ๛ Apilar valor1", pila_apilar(pila, valor1) == true);
    print_test("    ๛ Ver tope devuelve valor1", pila_ver_tope(pila) == valor1);
    print_test("    ๛ Apilar valor2", pila_apilar(pila, valor2) == true);
    print_test("    ๛ Ver tope devuelve valor2", pila_ver_tope(pila) == valor2);
    print_test("    ๛ Apilar valor3", pila_apilar(pila, valor3) == true);
    print_test("    ๛ Ver tope devuelve valor3", pila_ver_tope(pila) == valor3);
    print_test("    ๛ Apilar valor4", pila_apilar(pila, valor4) == true);
    print_test("    ๛ Ver tope devuelve valor4", pila_ver_tope(pila) == valor4);
    print_test("    ๛ Apilar valor5", pila_apilar(pila, valor5) == true);
    print_test("    ๛ Ver tope devuelve valor5", pila_ver_tope(pila) == valor5);

    /* Pruebo que permita apilar al elemento NULL y se comporte correctamente*/
    print_test("    ๛ Apilar NULL", pila_apilar(pila, NULL) == true);
    print_test("    ๛ Ver tope devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("    ๛ La pila no está vacía", !pila_esta_vacia(pila));
    print_test("    ๛ Desapilar NULL", pila_desapilar(pila) == NULL);

    /* Pruebo que desapilar me devuelva los 5 valores en el orden correcto
        y que en el transcurso los topes vayan cambiando a los adecuados */
    print_test("    ๛ Ver tope devuelve valor5", pila_ver_tope(pila) == valor5);
    print_test("    ๛ Desapilar devuelve valor5", pila_desapilar(pila) == valor5);
    print_test("    ๛ Ver tope devuelve valor4", pila_ver_tope(pila) == valor4);
    print_test("    ๛ Desapilar devuelve valor4", pila_desapilar(pila) == valor4);
    print_test("    ๛ Ver tope devuelve valor3", pila_ver_tope(pila) == valor3);
    print_test("    ๛ Desapilar devuelve valor3", pila_desapilar(pila) == valor3);
    print_test("    ๛ Ver tope devuelve valor2", pila_ver_tope(pila) == valor2);
    print_test("    ๛ Desapilar devuelve valor2", pila_desapilar(pila) == valor2);

    /* Pruebo que la pila no esté vacía */
    print_test("    ๛ La pila no está vacía", !pila_esta_vacia(pila));

    /* Continúo hasta vaciarla y pruebo que esté vacía */
    print_test("    ๛ Ver tope devuelve valor1", pila_ver_tope(pila) == valor1);
    print_test("    ๛ Desapilar devuelve valor1", pila_desapilar(pila) == valor1);
    print_test("    ๛ La pila está vacía", pila_esta_vacia(pila));

    /* Compruebo que se comporte como una pila recién creada */
    print_test("    ๛ Ver tope en pila vacía devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("    ๛ Desapilar en pila vacía devuelve NULL", pila_desapilar(pila) == NULL);

    /* Destruyo la pila */
    pila_destruir(pila);
}

void pruebas_pila_volumen(int x) {
    printf("༺ INICIO DE PRUEBAS DE VOLUMEN (%d elementos) ༻ \n", x * 15);

    /* Variables a utilizar */
    pila_t* pila = pila_crear();
    char abc[6];
    char* valorA = &abc[0];
    char* valorB = &abc[1];
    char* valorC = &abc[2];
    char* valorD = &abc[3];
    char* valorE = &abc[4];

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una pila", pila != NULL);
    print_test("    ๛ La pila está vacía", pila_esta_vacia(pila));

    /* Pruebo apilar x veces el tamaño inicial de la pila */
    bool aux;
    int i;
    for (i = 0; i < 3 * x; i++) {
            aux = pila_apilar(pila, valorA) == true && pila_ver_tope(pila) == valorA
                && pila_apilar(pila, valorB) == true && pila_ver_tope(pila) == valorB
                && pila_apilar(pila, valorC) == true && pila_ver_tope(pila) == valorC
                && pila_apilar(pila, valorD) == true && pila_ver_tope(pila) == valorD
                && pila_apilar(pila, valorE) == true && pila_ver_tope(pila) == valorE
                && !pila_esta_vacia(pila);
            if (!aux) {
                break;
            }
    }
    char cadena[50];
    sprintf(cadena, "    ๛ Apilar %d veces el tamaño de la pila", x);
    print_test(cadena, i == 3 * x);

    /* Pruebo desapilar hasta que esté vacia comprobando
        que se desapilen los elementos correctos*/
    while (!pila_esta_vacia(pila)) {
            aux = pila_desapilar(pila) == valorE && pila_desapilar(pila) == valorD
                && pila_desapilar(pila) == valorC && pila_desapilar(pila) == valorB
                && pila_desapilar(pila) == valorA;
    }  
    sprintf(cadena, "    ๛ Desapilar %d veces el tamaño de la pila", x);
    print_test(cadena, aux);
    print_test("    ๛ La pila queda vacía", pila_esta_vacia(pila));    

    /* Destruyo la pila */
    pila_destruir(pila);
}


void pruebas_pila_estudiante() {
    pruebas_pila_vacia();
    pruebas_pila_algunos_elementos();
    for (int i = 5; i <= 500; i *= 100) {
        pruebas_pila_volumen(i);
    }
}


#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
