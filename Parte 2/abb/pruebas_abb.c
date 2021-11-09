#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "abb.h"


/* ******************************************************************
 *                        FUNCIONES VISITAR
 *          (usadas en las pruebas del iterador interno)
 * *****************************************************************/

typedef struct aux {
    char txt[60];
} aux_t;

aux_t* aux_crear() {
    aux_t* aux = malloc(sizeof(aux_t));
    if (aux == NULL) {
        return false;
    }
    aux->txt[0] = '\0';
    return aux;
}


//guarda todas las claves
bool guardar_todos(const char* clave, void* dato, void* extra) {
    aux_t* aux = extra;
    strcat(aux->txt, clave);
    return true;
}

bool guardar_pares(const char* clave, void* dato, void* extra) {
    aux_t* aux = extra;
    if (*(int*)dato % 2 == 0) {
        strcat(aux->txt, clave);
    }
    return true;
}

bool guardar_menores_a_18(const char* clave, void* dato, void* extra) {
    aux_t* aux = extra;
    if (*(int*)dato < 18) {
        strcat(aux->txt, clave);
        return true;
    }
    return false;
}


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_abb_vacio() { // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA CREAR ABB VACIO\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_abb_insertar() {  // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA INSERTAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "manzana", *valor1 = "rojo";
    char *clave2 = "pera", *valor2 = "verde";
    char *clave3 = "banana", *valor3 = "amarillo";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_reemplazar() { // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA REEMPLAZAR\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "manzana", *valor1a = "rojo", *valor1b = "red";
    char *clave2 = "banana", *valor2a = "amarillo", *valor2b = "yellow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir() { // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA REEMPLAZAR CON DESTRUIR\n");
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_clave_vacia() { // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA ABB CLAVE VACIA\n");
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null() { // ¡FUNCIONA! valgrind //
    printf("\nPRUEBA ABB VALOR NULL\n");
    abb_t* abb = abb_crear(strcmp, NULL);


    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    abb_destruir(abb);
}



int devolver_max(const char* clave_1, const char* clave_2) {
    int num_1 = atoi(clave_1);
    int num_2 = atoi(clave_2);
    return num_1 > num_2 ? 1 : num_1 < num_2 ? -1 : 0;
}


static void prueba_abb_borrar() {
    printf("\nPRUEBA ABB BORRAR\n");
    abb_t* abb = abb_crear(devolver_max, NULL);
    char *clave_0 = "0", *clave_1 = "1", *clave_2 = "2", *clave_3 = "3", *clave_4 = "4", *clave_5 = "5", *clave_6 = "6",
    *clave_7 = "7", *clave_9 = "9", *clave_15 = "15" , *clave_20 = "20", *clave_18 = "18", *clave_16 = "16", *clave_19 = "19",
    *clave_17 = "17", *clave_28 = "28", *clave_25 = "25", *clave_29 = "29", *clave_26 = "26";
    
    int valor_0 = 0, valor_1 = 1, valor_2 = 2, valor_3 = 3, valor_4 = 4, valor_5 = 5, valor_6 = 6, valor_7 = 7, valor_9 = 9, valor_15 = 15,
    valor_20 = 20, valor_18 = 18, valor_16 = 16, valor_19 = 19, valor_17 = 17, valor_28 = 28, valor_25 = 25, valor_29 = 29, valor_26 = 26;

    abb_guardar(abb, clave_15, &valor_15);

    abb_guardar(abb, clave_9, &valor_9);
    abb_guardar(abb, clave_3, &valor_3);
    abb_guardar(abb, clave_1, &valor_1);
    abb_guardar(abb, clave_0, &valor_0);
    abb_guardar(abb, clave_2, &valor_2);
    abb_guardar(abb, clave_5, &valor_5);
    abb_guardar(abb, clave_4, &valor_4);
    abb_guardar(abb, clave_6, &valor_6);
    abb_guardar(abb, clave_7, &valor_7);


    abb_guardar(abb, clave_20, &valor_20);
    abb_guardar(abb, clave_18, &valor_18);
    abb_guardar(abb, clave_16, &valor_16);
    abb_guardar(abb, clave_17, &valor_17);
    abb_guardar(abb, clave_19, &valor_19);
    abb_guardar(abb, clave_28, &valor_28);
    abb_guardar(abb, clave_25, &valor_25);
    abb_guardar(abb, clave_26, &valor_26);
    abb_guardar(abb, clave_29, &valor_29);
    
    print_test("Prueba abb la cantidad de elementos es 19", abb_cantidad(abb) == 19);
    print_test("Prueba borrar 7",abb_borrar(abb, clave_7) == &valor_7);
    print_test("Prueba borrar 16",abb_borrar(abb, clave_16) == &valor_16);
    print_test("Prueba abb la cantidad de elementos es 17", abb_cantidad(abb) == 17);
    print_test("Prueba borrar 20",abb_borrar(abb, clave_20) == &valor_20);
    print_test("Prueba borrar 25",abb_borrar(abb, clave_25) == &valor_25);
    print_test("Prueba abb la cantidad de elementos es 15", abb_cantidad(abb) == 15);
    print_test("Prueba borrar 3",abb_borrar(abb, clave_3) == &valor_3);
    print_test("Prueba borrar 4",abb_borrar(abb, clave_4) == &valor_4);
    print_test("Prueba borrar 15",abb_borrar(abb, clave_15) == &valor_15);
    print_test("Prueba borrar 5",abb_borrar(abb, clave_5) == &valor_5);
    print_test("Prueba borrar 1",abb_borrar(abb, clave_1) == &valor_1);

    // AGREGO UNO//
    print_test("Prueba agregar valor_8", abb_guardar(abb, clave_7, &valor_7));
    print_test("Prueba abb la cantidad de elementos es 11", abb_cantidad(abb) == 11);
    
    print_test("Prueba borrar algo que no esta",abb_borrar(abb, clave_5) == NULL);

    print_test("Prueba borrar 17",abb_borrar(abb, clave_17) == &valor_17);
    print_test("Prueba borrar 18",abb_borrar(abb, clave_18) == &valor_18);
    print_test("Prueba borrar 28",abb_borrar(abb, clave_28) == &valor_28);
    print_test("Prueba borrar 29",abb_borrar(abb, clave_29) == &valor_29);
    print_test("Prueba borrar 26",abb_borrar(abb, clave_26) == &valor_26);
    print_test("Prueba borrar 7",abb_borrar(abb, clave_7) == &valor_7);
    print_test("Prueba abb la cantidad de elementos es 5", abb_cantidad(abb) == 5);
    print_test("Prueba borrar 0",abb_borrar(abb, clave_0) == &valor_0);
    print_test("Prueba borrar 19",abb_borrar(abb, clave_19) == &valor_19);
    print_test("Prueba borrar 6",abb_borrar(abb, clave_6) == &valor_6);
    print_test("Prueba borrar 2",abb_borrar(abb, clave_2) == &valor_2);
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba borrar 9",abb_borrar(abb, clave_9) == &valor_9);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


static void prueba_abb_iter_externo() {
    printf("\nPRUEBA ITERADOR EXTERNO\n");
    
    abb_t* abb = abb_crear(devolver_max, NULL);
    char *clave_0 = "0", *clave_1 = "1", *clave_2 = "2", *clave_3 = "3", *clave_4 = "4", *clave_5 = "5", *clave_6 = "6",
    *clave_7 = "7", *clave_9 = "9", *clave_15 = "15" , *clave_20 = "20", *clave_18 = "18", *clave_16 = "16", *clave_19 = "19",
    *clave_17 = "17", *clave_28 = "28", *clave_25 = "25", *clave_29 = "29", *clave_26 = "26";
    
    int valor_0 = 0, valor_1 = 1, valor_2 = 2, valor_3 = 3, valor_4 = 4, valor_5 = 5, valor_6 = 6, valor_7 = 7, valor_9 = 9, valor_15 = 15,
    valor_20 = 20, valor_18 = 18, valor_16 = 16, valor_19 = 19, valor_17 = 17, valor_28 = 28, valor_25 = 25, valor_29 = 29, valor_26 = 26;

    abb_guardar(abb, clave_15, &valor_15);

    abb_guardar(abb, clave_9, &valor_9);
    abb_guardar(abb, clave_3, &valor_3);
    abb_guardar(abb, clave_1, &valor_1);
    abb_guardar(abb, clave_0, &valor_0);
    abb_guardar(abb, clave_2, &valor_2);
    abb_guardar(abb, clave_5, &valor_5);
    abb_guardar(abb, clave_4, &valor_4);
    abb_guardar(abb, clave_6, &valor_6);
    abb_guardar(abb, clave_7, &valor_7);

    abb_guardar(abb, clave_20, &valor_20);
    abb_guardar(abb, clave_18, &valor_18);
    abb_guardar(abb, clave_16, &valor_16);
    abb_guardar(abb, clave_17, &valor_17);
    abb_guardar(abb, clave_19, &valor_19);
    abb_guardar(abb, clave_28, &valor_28);
    abb_guardar(abb, clave_25, &valor_25);
    abb_guardar(abb, clave_26, &valor_26);
    abb_guardar(abb, clave_29, &valor_29);

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba iterador externo crear", iter);
    print_test("Prueba iterador externo esta al final", !abb_iter_in_al_final(iter));
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_0) == 0);
    print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter));
    print_test("Prueba iterador externo esta al final", !abb_iter_in_al_final(iter));
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_1) == 0);
    print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter)); //2
    print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter)); //3
    print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter)); //5
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_4) == 0);
    for (int i = 0; i < 5; i++) {
        print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter));
    }
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_15) == 0);
    for (int i = 0; i < 5; i++) {
        print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter));
    }
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_20) == 0);
    for (int i = 0; i < 4; i++) {
        print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter));
    }
    print_test("Prueba iterador externo ver actual", strcmp(abb_iter_in_ver_actual(iter), clave_29) == 0);
    print_test("Todavía no está al final", !abb_iter_in_al_final(iter));
    print_test("Prueba iterador externo avanzar", abb_iter_in_avanzar(iter));
    print_test("Prueba iterador externo esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba iterador externo ver actual es NULL", abb_iter_in_ver_actual(iter) == NULL);
    
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_volumen() {
    abb_t* abb = abb_crear(devolver_max, NULL);

    // Genero 1000 números para insertar en el árbol y luego los guardo
    char (*claves)[7] = malloc(7 * 1000);
    int* valores[1000];
    srand(2050);
    bool ok = true;
    for (int i = 0; i < 1000; i++) {
        valores[i] = malloc(sizeof(int));
        int num = rand() % 500000;
        sprintf(claves[i], "%d", num);
        *valores[i] = num;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if(!ok) break;
    }
    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == 1000);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < 1000; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) {
            break;
        }
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) {
            break;
        }
    }
    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == 1000);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < 1000; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }
    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el árbol y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(devolver_max, free);

    /* Inserta 1000 parejas en el abb */
    ok = true;
    for (size_t i = 0; i < 1000; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el árbol - debería liberar los enteros */
    abb_destruir(abb);
}

void static pruebas_iterador_interno() {
    abb_t* abb = abb_crear(devolver_max, NULL);
    char *clave_0 = "0", *clave_1 = "1", *clave_2 = "2", *clave_3 = "3", *clave_4 = "4", *clave_5 = "5", *clave_6 = "6",
    *clave_7 = "7", *clave_9 = "9", *clave_15 = "15" , *clave_20 = "20", *clave_18 = "18", *clave_16 = "16", *clave_19 = "19",
    *clave_17 = "17", *clave_28 = "28", *clave_25 = "25", *clave_29 = "29", *clave_26 = "26";
    
    int valor_0 = 0, valor_1 = 1, valor_2 = 2, valor_3 = 3, valor_4 = 4, valor_5 = 5, valor_6 = 6, valor_7 = 7, valor_9 = 9, valor_15 = 15,
    valor_20 = 20, valor_18 = 18, valor_16 = 16, valor_19 = 19, valor_17 = 17, valor_28 = 28, valor_25 = 25, valor_29 = 29, valor_26 = 26;
    abb_guardar(abb, clave_15, &valor_15);
    abb_guardar(abb, clave_9, &valor_9);
    abb_guardar(abb, clave_3, &valor_3);
    abb_guardar(abb, clave_1, &valor_1);
    abb_guardar(abb, clave_0, &valor_0);
    abb_guardar(abb, clave_2, &valor_2);
    abb_guardar(abb, clave_5, &valor_5);
    abb_guardar(abb, clave_4, &valor_4);
    abb_guardar(abb, clave_6, &valor_6);
    abb_guardar(abb, clave_7, &valor_7);

    abb_guardar(abb, clave_20, &valor_20);
    abb_guardar(abb, clave_18, &valor_18);
    abb_guardar(abb, clave_16, &valor_16);
    abb_guardar(abb, clave_17, &valor_17);
    abb_guardar(abb, clave_19, &valor_19);
    abb_guardar(abb, clave_28, &valor_28);
    abb_guardar(abb, clave_25, &valor_25);
    abb_guardar(abb, clave_26, &valor_26);
    abb_guardar(abb, clave_29, &valor_29);

    
    aux_t* todos = aux_crear();
    char* guardado = "01234567915161718192025262829";
    abb_in_order(abb, guardar_todos, todos);
    print_test("Prueba abb iterador interno guardar todos", strcmp(todos->txt, guardado) == 0);
    free(todos);

    aux_t* pares = aux_crear();
    abb_in_order(abb, guardar_pares, pares);
    print_test("Prueba abb iterador interno guardar pares ", strcmp(pares->txt, "02461618202628") == 0);
    free(pares);

    aux_t* primeros = aux_crear();
    abb_in_order(abb, guardar_menores_a_18, primeros);
    print_test("Prueba abb iterador interno guardar primeros ", strcmp(primeros->txt, "012345679151617") == 0);
    free(primeros);

    abb_destruir(abb);
}

static void pruebas_aux() {
    printf("\nINICIO DE PRUEBAS AUXILIARES\n");
    abb_t* abb = abb_crear(devolver_max, NULL);
    char *clave_1 = "1", *clave_2 = "2", *clave_3 = "3", *clave_4 = "4", *clave_5 = "5", *clave_6 = "6", *clave_7 = "7";
    int valor_1 = 1, valor_2 = 2, valor_3 = 3, valor_4 = 4, valor_5 = 5, valor_6 = 6, valor_7 = 7;


    abb_guardar(abb, clave_1, &valor_1);
    abb_guardar(abb, clave_2, &valor_2);
    abb_guardar(abb, clave_3, &valor_3);
    abb_guardar(abb, clave_4, &valor_4);
    abb_guardar(abb, clave_5, &valor_5);
    abb_guardar(abb, clave_6, &valor_6);
    abb_guardar(abb, clave_7, &valor_7);
    
    abb_guardar(abb, clave_5, &valor_1);
    abb_guardar(abb, clave_3, &valor_2);
    abb_guardar(abb, clave_7, &valor_3);
    abb_guardar(abb, clave_1, &valor_4);
    abb_guardar(abb, clave_6, &valor_5);    
    abb_guardar(abb, clave_4, &valor_6);
    abb_guardar(abb, clave_2, &valor_7);

    print_test("Obtener clave_5 da valor_1", abb_obtener(abb, clave_5) == &valor_1);
    print_test("Obtener clave_3 da valor_2", abb_obtener(abb, clave_3) == &valor_2);
    print_test("Obtener clave_7 da valor_3", abb_obtener(abb, clave_7) == &valor_3);
    print_test("Obtener clave_1 da valor_4", abb_obtener(abb, clave_1) == &valor_4);
    print_test("Obtener clave_6 da valor_5", abb_obtener(abb, clave_6) == &valor_5);
    print_test("Obtener clave_4 da valor_6", abb_obtener(abb, clave_4) == &valor_6);
    print_test("Obtener clave_2 da valor_7", abb_obtener(abb, clave_2) == &valor_7);

    abb_destruir(abb);

}


/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/

void pruebas_abb_estudiante() {
    prueba_crear_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_borrar();
    prueba_abb_iter_externo();
    prueba_abb_volumen();
    pruebas_iterador_interno();
    pruebas_aux();
    printf("¡Hola corrector automático!\n");
}



#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_abb_estudiante();
    return 0;  // Indica si falló alguna prueba.
}

#endif