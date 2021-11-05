#include "cola.h"
#include "testing.h"
#include <stdio.h>

/* ******************************************************************
 *                      FUNCIÓN DE DESTRUCCIÓN
 *                   (usada en la última prueba)
 * *****************************************************************/

// Destruye sólo la cola y no los datos de dentro 
void _cola_destruir(void* cola) {
    cola_destruir((cola_t*)cola, NULL);
}

/* ******************************************************************
 *                              PRUEBAS
 * *****************************************************************/

/* Pruebas para una cola vacía */
static void pruebas_cola_vacia(void) {
    printf("༺ INICIO DE PRUEBAS CON UNA COLA VACÍA ༻  \n");

    /* Variables a utilizar */
    cola_t* cola = cola_crear();

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una cola", cola != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(cola));

    /* Pruebo que ver el primero de la cola devuelva NULL */
    print_test("    ๛ Ver primero devuelve NULL", cola_ver_primero(cola) == NULL);

    /* Pruebo que desencolar también devuelva NULL */
    print_test("    ๛ Desencolar devuelve NULL", cola_desencolar(cola) == NULL);

    /* Destruyo la cola */
    cola_destruir(cola, NULL);
}

void pruebas_cola_algunos_elementos(void) {
    printf("༺ INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS ༻  \n");

    /* Variables a utilizar */
    cola_t* cola = cola_crear();
    int num[5] ; 
    int* valor1 = &num[0];
    int* valor2 = &num[1];
    int* valor3 = &num[2];
    int* valor4 = &num[3];
    int* valor5 = &num[4];

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una cola", cola != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(cola));

    /* Pruebo que encolar los 5 valores devuelva true
        y que en el transcurso el primero siga siendo el mismo */
    print_test("    ๛ Encolar valor1", cola_encolar(cola, valor1) == true);
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);
    print_test("    ๛ Encolar valor2", cola_encolar(cola, valor2) == true);
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);
    print_test("    ๛ Encolar valor3", cola_encolar(cola, valor3) == true);
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);
    print_test("    ๛ Encolar valor4", cola_encolar(cola, valor4) == true);
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);
    print_test("    ๛ Encolar valor5", cola_encolar(cola, valor5) == true);
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);

    /* Pruebo que permita encolar al elemento NULL y se comporte correctamente */
    print_test("    ๛ Encolar NULL", cola_encolar(cola, NULL) == true);
    print_test("    ๛ La cola no está vacía", !cola_esta_vacia(cola));

    /* Pruebo que desencolar me devuelva los 5 valores en el orden correcto
        y que en el transcurso los primeros vayan cambiando a los adecuados */
    print_test("    ๛ Ver el primero devuelve valor1", cola_ver_primero(cola) == valor1);
    print_test("    ๛ Desencolar devuelve valor1", cola_desencolar(cola) == valor1);
    print_test("    ๛ Ver el primero devuelve valor2", cola_ver_primero(cola) == valor2);
    print_test("    ๛ Desencolar devuelve valor2", cola_desencolar(cola) == valor2);
    print_test("    ๛ Ver el primero devuelve valor3", cola_ver_primero(cola) == valor3);
    print_test("    ๛ Desencolar devuelve valor3", cola_desencolar(cola) == valor3);
    print_test("    ๛ Ver el primero devuelve valor4", cola_ver_primero(cola) == valor4);
    print_test("    ๛ Desencolar devuelve valor4", cola_desencolar(cola) == valor4);
    print_test("    ๛ Ver el primero devuelve valor5", cola_ver_primero(cola) == valor5);
    print_test("    ๛ Desencolar devuelve valor5", cola_desencolar(cola) == valor5);

    /* Pruebo que la cola no esté vacía */
    print_test("    ๛ La cola no está vacía", !cola_esta_vacia(cola));

    /* Continúo hasta vaciarla y pruebo que esté vacía */
    print_test("    ๛ Ver el primero devuelve NULL", cola_ver_primero(cola) == NULL);
    print_test("    ๛ Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(cola));

    /* Compruebo que se comporte como una cola recién creada */
    print_test("    ๛ Ver el primero en cola vacía devuelve NULL", cola_ver_primero(cola) == NULL);
    print_test("    ๛ Desencolar en cola vacía devuelve NULL", cola_desencolar(cola) == NULL);

    /* Destruyo la cola */
    cola_destruir(cola, NULL);
}

void pruebas_cola_volumen(int x) {
    printf("༺ INICIO DE PRUEBAS DE VOLUMEN (%d elementos) ༻  \n", x);

    /* Variables a utilizar */
    cola_t* cola = cola_crear();
    char abc[6];
    char* valorA = &abc[0];
    char* valorB = &abc[1];
    char* valorC = &abc[2];
    char* valorD = &abc[3];
    char* valorE = &abc[4];

    /* Pruebo que se cree correctamente */
    print_test("    ๛ Crear una cola", cola != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(cola));

    /* Pruebo encolar x cantidad de elementos */
    bool aux;
    int i;
    for (i = 0; i < x / 5; i++) {
            aux = cola_encolar(cola, valorA) == true && cola_ver_primero(cola) == valorA
                && cola_encolar(cola, valorB) == true && cola_ver_primero(cola) == valorA
                && cola_encolar(cola, valorC) == true && cola_ver_primero(cola) == valorA
                && cola_encolar(cola, valorD) == true && cola_ver_primero(cola) == valorA
                && cola_encolar(cola, valorE) == true && cola_ver_primero(cola) == valorA
                && !cola_esta_vacia(cola);
            if (!aux) {
                break;
            }
    }
    char cadena[50];
    sprintf(cadena, "    ๛ Encolar %d elementos", x);
    print_test(cadena, i == x / 5);

    /* Pruebo desencolar hasta que esté vacia comprobando
        que se desapilen los elementos correctos*/
    while (!cola_esta_vacia(cola)) {
            aux = cola_desencolar(cola) == valorA && cola_desencolar(cola) == valorB
                && cola_desencolar(cola) == valorC && cola_desencolar(cola) == valorD
                && cola_desencolar(cola) == valorE;
    }  
    sprintf(cadena, "    ๛ Desencolar %d elementos", x);
    print_test(cadena, aux);
    print_test("    ๛ La cola queda vacía", cola_esta_vacia(cola));    

    /* Destruyo la cola */
    cola_destruir(cola, NULL);
}

static void pruebas_cola_en_cola(void) {
    printf("༺ INICIO DE PRUEBAS ENCOLANDO COLAS DENTRO DE OTRA ༻  \n");

    /* Variables a utilizar */
    cola_t* cola = cola_crear();
    cola_t* subcola1 = cola_crear();
    cola_t* subcola2 = cola_crear();
    cola_t* subcola3 = cola_crear();
    cola_t* subsubcola1 = cola_crear();
    cola_t* subsubcola2 = cola_crear();
    cola_t* subsubcola3 = cola_crear();


    /* Pruebo que se cree correctamente cada una */
    print_test("    ๛ Crear una cola", cola != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(cola));
    print_test("    ๛ Crear una cola", subcola1 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subcola1));   
    print_test("    ๛ Crear una cola", subcola2 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subcola2));   
    print_test("    ๛ Crear una cola", subcola2 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subcola2));
    print_test("    ๛ Crear una cola", subsubcola1 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subsubcola1));   
    print_test("    ๛ Crear una cola", subsubcola2 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subsubcola2));   
    print_test("    ๛ Crear una cola", subsubcola2 != NULL);
    print_test("    ๛ La cola está vacía", cola_esta_vacia(subsubcola2));     

    /* Pruebo que se puedan encolar todas las colas dentro de la primera y se comporte correctamente */
    print_test("    ๛ Encolarse a si misma", cola_encolar(cola, cola));
    print_test("    ๛ La cola no está vacía", !cola_esta_vacia(cola));
    print_test("    ๛ Ver el primero devuelve la misma cola", cola_ver_primero(cola) == cola);
    print_test("    ๛ Encolar en cola principal a subsubcola1", cola_encolar(cola, subsubcola1));
    print_test("    ๛ Encolar en cola principal a subsubcola2", cola_encolar(cola, subsubcola2));
    print_test("    ๛ Encolar en cola principal a subsubcola3", cola_encolar(cola, subsubcola3));
    print_test("    ๛ Encolar en cola principal a subcola1", cola_encolar(cola, subcola1));
    print_test("    ๛ Encolar en cola principal a subcola2", cola_encolar(cola, subcola2));
    print_test("    ๛ Encolar en cola principal a subcola3", cola_encolar(cola, subcola3));
    print_test("    ๛ Ver el primero devuelve la misma cola", cola_ver_primero(cola) == cola);
    
    /* Pruebo que desencolarse a si misma y a las 3 subsubcolas funcione correctamente */
    print_test("    ๛ Desencolarse a si misma", cola_desencolar(cola) == cola);
    print_test("    ๛ La cola no está vacía", !cola_esta_vacia(cola));
    print_test("    ๛ Ver el primero devuelve a subsubcola1", cola_ver_primero(cola) == subsubcola1);
    print_test("    ๛ Desencolar de la cola principal devuelve a subsubcola1", cola_desencolar(cola) == subsubcola1);
    print_test("    ๛ Desencolar de la cola principal devuelve a subsubcola2", cola_desencolar(cola) == subsubcola2);
    print_test("    ๛ Desencolar de la cola principal devuelve a subsubcola3", cola_desencolar(cola) == subsubcola3);    
    print_test("    ๛ Ver el primero devuelve a subcola1", cola_ver_primero(cola) == subcola1);
    print_test("    ๛ La cola no está vacía", !cola_esta_vacia(cola));

    /* En colo en cada subcola a las 3 subsubcolas */
    print_test("    ๛ Encolar en subcola1 a subsubcola1", cola_encolar(subcola1, subsubcola1));
    print_test("    ๛ Encolar en subcola1 a subsubcola2", cola_encolar(subcola1, subsubcola2));
    print_test("    ๛ Encolar en subcola1 a subsubcola3", cola_encolar(subcola1, subsubcola3));
    print_test("    ๛ Encolar en subcola2 a subsubcola1", cola_encolar(subcola2, subsubcola1));
    print_test("    ๛ Encolar en subcola2 a subsubcola2", cola_encolar(subcola2, subsubcola2));
    print_test("    ๛ Encolar en subcola2 a subsubcola3", cola_encolar(subcola2, subsubcola3));
    print_test("    ๛ Encolar en subcola3 a subsubcola1", cola_encolar(subcola3, subsubcola1));
    print_test("    ๛ Encolar en subcola3 a subsubcola2", cola_encolar(subcola3, subsubcola2));
    print_test("    ๛ Encolar en subcola3 a subsubcola3", cola_encolar(subcola3, subsubcola3));

    /* Destruyo las colas */
    printf("    ⚠ DESTRUCCIÓN DE COLAS CON COLAS DENTRO ⚠ ");
    cola_destruir(cola, _cola_destruir);
    cola_destruir(subsubcola1, NULL);
    cola_destruir(subsubcola2, NULL);
    cola_destruir(subsubcola3, NULL);
    print_test("", true); // usado para darle el OK a que se destruyeron sin errores
                         // de ejecución debido a la destrucción de las colas
}


void pruebas_cola_estudiante() {
    pruebas_cola_vacia();
    pruebas_cola_algunos_elementos();
    for (int i = 30; i <= 25000; i *= 50) {
        pruebas_cola_volumen(i);
    }
    pruebas_cola_en_cola();
}


#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
