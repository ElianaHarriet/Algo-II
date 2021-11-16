#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.



/* ******************************************************************
 *                        FUNCIÓN COMPARAR
 * *****************************************************************/

int devolver_max(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

static void prueba_crear_heap_vacio() {  
    printf("\nPRUEBA CREAR HEAP VACIO\n");
    heap_t* heap = heap_crear(NULL);
    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap está vacío", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba ver el maximo da NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba no se puede desencolar", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
}

static void prueba_heap_valores_null() {
    printf("\nPRUEBA HEAP CON VALORES NULL\n");
    heap_t* heap = heap_crear(devolver_max);
    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap insertar NULL", heap_encolar(heap, NULL) == true);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba ver el maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba heap desencolar NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    heap_destruir(heap, NULL);
}

static void prueba_heap_encolar() {
    printf("\nPRUEBA HEAP CON VALORES\n");  
    heap_t* heap = heap_crear(devolver_max);
    int valor_5_a = 5, valor_6 = 6, valor_3 = 3;
    int valor_7 = 7, valor_10 = 10, valor_8 = 8;
    int valor_5_b = 5, valor_9 = 9, valor_2 = 2;

    print_test("Prueba encolar_valores: ", heap_encolar(heap, &valor_5_a));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);  
    print_test("Encolar valor_6 da true", heap_encolar(heap, &valor_6));
    print_test("Encolar valor_3 da true", heap_encolar(heap, &valor_3));
    print_test("Encolar valor_7 da true", heap_encolar(heap, &valor_7));
    print_test("Encolar valor_10 da true", heap_encolar(heap, &valor_10));
    print_test("Encolar valor_8 da true", heap_encolar(heap, &valor_8));
    print_test("Encolar valor_5_b da true", heap_encolar(heap, &valor_5_b));
    print_test("Encolar valor_9 da true", heap_encolar(heap, &valor_9));
    print_test("Encolar valor_2 da true", heap_encolar(heap, &valor_2));
    print_test("Prueba heap la cantidad de elementos es 9", heap_cantidad(heap) == 9);
    print_test("Prueba ver el maximo es 10", heap_ver_max(heap) == &valor_10);

    heap_destruir(heap, NULL);
}

static void prueba_heap_desencolar() {
    printf("\nPRUEBA HEAP CON VALORES\n");  
    heap_t* heap = heap_crear(devolver_max);
    int valor_5_a = 5, valor_6 = 6, valor_3 = 3;
    int valor_7 = 7, valor_10 = 10, valor_8 = 8;
    int valor_5_b = 5, valor_9 = 9, valor_2 = 2;
    heap_encolar(heap, &valor_5_a);
    heap_encolar(heap, &valor_6);
    heap_encolar(heap, &valor_3);
    heap_encolar(heap, &valor_7);
    heap_encolar(heap, &valor_10);
    heap_encolar(heap, &valor_8);
    heap_encolar(heap, &valor_5_b);
    heap_encolar(heap, &valor_9);
    heap_encolar(heap, &valor_2);
    print_test("Prueba desencolar valor_10", heap_desencolar(heap) == &valor_10);
    print_test("Prueba desencolar valor_9", heap_desencolar(heap) == &valor_9);
    print_test("Prueba desencolar valor_8", heap_desencolar(heap) == &valor_8);
    print_test("Prueba desencolar valor_7", heap_desencolar(heap) == &valor_7);
    print_test("Prueba desencolar valor_6", heap_desencolar(heap) == &valor_6);
    print_test("Prueba desencolar valor_5_b", heap_desencolar(heap) == &valor_5_b);
    print_test("Prueba desencolar valor_5_a", heap_desencolar(heap) == &valor_5_a);
    print_test("Prueba desencolar valor_3", heap_desencolar(heap) == &valor_3);
    print_test("Prueba desencolar valor_2", heap_desencolar(heap) == &valor_2);

    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba ver el maximo es NULL", heap_ver_max(heap) == NULL);
    heap_destruir(heap, NULL);
}

static void prueba_heap_encolar_desencolar() {
    printf("\nPRUEBA HEAP ENCOLAR Y DESENCOLAR\n");  
    heap_t* heap = heap_crear(devolver_max);
    int valor_5_a = 5, valor_6 = 6, valor_3 = 3;
    int valor_7 = 7, valor_10 = 10, valor_8 = 8;
    int valor_5_b = 5;
    heap_encolar(heap, &valor_5_a);
    print_test("Prueba desencolar valor_5_a", heap_desencolar(heap) == &valor_5_a);
    heap_encolar(heap, &valor_6);
    heap_encolar(heap, &valor_3);
    print_test("Prueba desencolar valor_6", heap_desencolar(heap) == &valor_6);
    heap_encolar(heap, &valor_7);
    heap_encolar(heap, &valor_10);
    print_test("Prueba desencolar valor_10", heap_desencolar(heap) == &valor_10);
    heap_encolar(heap, &valor_8);
    print_test("Prueba desencolar valor_8", heap_desencolar(heap) == &valor_8);
    print_test("Prueba desencolar valor_7", heap_desencolar(heap) == &valor_7);
    print_test("Prueba desencolar valor_3", heap_desencolar(heap) == &valor_3);
    print_test("Prueba no se puede desencolar", heap_desencolar(heap) == NULL);
    heap_encolar(heap, &valor_5_b);
    print_test("Prueba desencolar valor_5_b", heap_desencolar(heap) == &valor_5_b);
    print_test("Prueba ver maximo = NULL", heap_ver_max(heap) == NULL);
    heap_destruir(heap, NULL);

}

static void prueba_arreglo_heapify() {
    printf("\nPRUEBA HEAPIFY\n");
    int valor_5_a = 5;
    int valor_6 = 6;
    int valor_3 = 3;
    int valor_7 = 7;
    int valor_10 = 10;
    int valor_8 = 8;
    int valor_5_b = 5;
    int valor_9 = 9;
    int valor_2 = 2;
    void* arreglo[] = {&valor_5_a, &valor_6, &valor_3, &valor_7, &valor_10, &valor_8, &valor_5_b, &valor_9, &valor_2};
    size_t tam = 9;
    heap_t* heap = heap_crear_arr(arreglo, tam, devolver_max);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_10);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_9);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_8);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_7);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_6);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_5_b);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_5_a);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_3);
    print_test("Prueba desencolar", heap_desencolar(heap) == &valor_2);
    print_test("Prueba desencolar", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
}


static void prueba_heapsort() {
    printf("\nPRUEBA HEAPSORT\n");
    int valor_6 = 6;
    int valor_3 = 3;
    int valor_7 = 7;
    int valor_10 = 10;
    int valor_8 = 8;
    int valor_5 = 5;
    int valor_9 = 9;
    int valor_2 = 2;
    void* arreglo[] = {&valor_6, &valor_3, &valor_7, &valor_10, &valor_8, &valor_5, &valor_9, &valor_2};
    size_t tam = 8;
    void* arreglo_ordenado[] = {&valor_2, &valor_3, &valor_5, &valor_6, &valor_7, &valor_8, &valor_9, &valor_10};
    heap_sort(arreglo, tam, devolver_max);
    bool ok = true;
    for (size_t i = 0; i < tam; i++) {
        ok = arreglo[i] == arreglo_ordenado[i];
        if (!ok) break;
    }
    print_test("Prueba heapsort", ok);
}

static void prueba_volumen() {
    printf("\nPRUEBA VOLUMEN\n");
    heap_t* heap = heap_crear(devolver_max);
    
    int arreglo[100001];
    bool ok = true;
    for (int i = 0; i < 100001 ;i++) {
        arreglo[i] = i;
        ok = heap_encolar(heap,&arreglo[i]);
        if (!ok) break;
    }
    print_test("Prueba heap encolar", ok);
    for(int i = 0; i < 100001; i++) {
        ok = heap_desencolar(heap) == &arreglo[100000-i];
        if (!ok) break;
    }
    print_test("Prueba heap desencolar", ok);
    heap_destruir(heap, NULL);
}


void pruebas_heap_estudiante() {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_heap_vacio();
    prueba_heap_valores_null();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_heap_encolar_desencolar();
    prueba_arreglo_heapify();
    prueba_heapsort();
    prueba_volumen(); 
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_heap_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif