#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        FUNCIONES VISITAR
 *          (usadas en las pruebas del iterador interno)
 * *****************************************************************/

typedef struct aux {
    char txt[10];
    size_t num;
} aux_t;

aux_t* aux_crear() {
    aux_t* aux = malloc(sizeof(aux_t));
    if (aux == NULL) {
        return false;
    }
    aux->num = 0;
    return aux;
}

bool guardar_todos(void* dato, void* extra) {
    size_t pos = ((aux_t*)extra)->num;
    (((aux_t*)extra)->txt)[pos] = *(char*)dato;
    (((aux_t*)extra)->txt)[pos + 1] = '\0';
    ((aux_t*)extra)->num++;
    return true;
}


bool guardar_pares(void* dato, void* extra) {
    size_t pos = ((aux_t*)extra)->num;
    if (pos % 2 == 0) {
        (((aux_t*)extra)->txt)[pos / 2] = *(char*)dato;
        (((aux_t*)extra)->txt)[pos / 2 + 1] = '\0';
    }
    ((aux_t*)extra)->num++;
    return true;
}


bool guardar_primeros_3(void* dato, void* extra) {
    size_t pos = ((aux_t*)extra)->num;
    if (pos < 3) {
        (((aux_t*)extra)->txt)[pos] = *(char*)dato;
        (((aux_t*)extra)->txt)[pos + 1] = '\0';
        ((aux_t*)extra)->num++;
        return true;
    }
    return false;
}



bool imprimir(void* dato, void* extra) {
    printf("%c\n", *(char*) dato);
    return true;
}



/* ******************************************************************
 *                              PRUEBAS
 * *****************************************************************/

/* Pruebas para una lista vacía */
void pruebas_lista_vacia(){
    printf("༺ INICIO DE PRUEBAS CON UNA LISTA VACÍA ༻  \n");
    lista_t* lista = lista_crear();
    print_test("    ๛ Crear una lista", lista != NULL);
    print_test("    ๛ La lista está vacía", lista_esta_vacia(lista));

    /* Pruebo que el primero y ultimo de la lista es NULL */
    print_test("    ๛ Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("    ๛ Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);

     /* Pruebo que no se puede borrar nada */
    print_test("    ๛ No se puede borrar el primero", lista_borrar_primero(lista) == NULL);
    /* Destruyo la lista */
    lista_destruir(lista, NULL);
}

void pruebas_lista_algunos_elementos(){
    printf("༺ INICIO DE PRUEBAS CON UNA LISTA CON DOS ELEMENTOS ༻  \n");
    lista_t* lista_1 = lista_crear();
    int num[] = {1, 2, 3, 4, 5}; 
    int* valor = &num[0];
    int* valor_1 = &num[1];
    int* valor_2 = &num[2];
    int* valor_3 = &num[3];
    int* valor_4 = &num[4];
    
    print_test("    ๛ Inserto el primero",lista_insertar_primero(lista_1, valor));
    print_test("    ๛ Ver primero devuelve puntero al dato insertado", lista_ver_primero(lista_1) == valor);
    print_test("    ๛ Ver ultimo devuelve puntero al dato insertado", lista_ver_ultimo(lista_1) == valor);
    
    print_test("    ๛ Inserto en el primero un nuevo valor",lista_insertar_primero(lista_1, valor_1));
    print_test("    ๛ Ver primero devuelve puntero al dato insertado", lista_ver_primero(lista_1) == valor_1);
    print_test("    ๛ Ver ultimo devuelve puntero al dato anterior", lista_ver_ultimo(lista_1) == valor);
    
    print_test("    ๛ Inserto en el ultimo un nuevo valor",lista_insertar_ultimo(lista_1, valor_2));
    print_test("    ๛ Ver primero devuelve puntero al dato anterior", lista_ver_primero(lista_1) == valor_1);
    print_test("    ๛ Ver ultimo devuelve puntero al dato insertado", lista_ver_ultimo(lista_1) == valor_2);
    lista_destruir(lista_1, NULL);

    printf("     USO NUEVA LISTA \n");
    lista_t* lista_2 =lista_crear();
    
    print_test("    ๛ Inserto el ultimo",lista_insertar_ultimo(lista_2, valor_3));

    print_test("    ๛ Ver primero devuelve puntero al dato insertado", lista_ver_primero(lista_2) == valor_3);
    print_test("    ๛ Ver ultimo devuelve puntero al dato insertado", lista_ver_ultimo(lista_2) == valor_3);
    
    print_test("    ๛ Inserto en el ultimo un nuevo valor",lista_insertar_ultimo(lista_2,valor_4));
    print_test("    ๛ Ver primero devuelve puntero al dato anterior", lista_ver_primero(lista_2) ==valor_3);
    print_test("    ๛ Ver ultimo devuelve puntero al dato insertado", lista_ver_ultimo(lista_2) ==valor_4);
    print_test("    ๛ Borro el primero",lista_borrar_primero(lista_2));
    print_test("    ๛ El primero es el ultimo que agregue", lista_ver_primero(lista_2) ==valor_4);
    print_test("    ๛ El ultimo es el ultimo que agregue", lista_ver_ultimo(lista_2) ==valor_4);
    

    lista_destruir(lista_2, NULL);
}

void pruebas_iterador_interno() {
    printf("༺ INICIO DE PRUEBAS CON EL ITERADOR INTERNO ༻  \n");
    
    /* Variables a utilizar */
    lista_t* lista = lista_crear();
    char letra[] = {'A', 'B', 'C', 'D', 'E'}; 
    char* valor1 = &letra[0];
    char* valor2 = &letra[1];
    char* valor3 = &letra[2];
    char* valor4 = &letra[3];
    char* valor5 = &letra[4];

    /* Agrego elementos a la lista */
    lista_insertar_ultimo(lista, valor1);
    lista_insertar_ultimo(lista, valor2);
    lista_insertar_ultimo(lista, valor3);
    lista_insertar_ultimo(lista, valor4);
    lista_insertar_ultimo(lista, valor5);

    /* Pruebo guardar todos los datos de la lista en una cadena */
    char* todos = "ABCDE";
    aux_t* guardados = aux_crear();
    lista_iterar(lista, guardar_todos, guardados);
    print_test("    ๛ Prueba con función visitar que pasa por todos los elementos", strcmp(todos, guardados->txt) == 0);
    free(guardados);

    /* Pruebo guardar todos los datos en posiciones pares pares de la lista en una cadena */
    char* datos = "ACE";
    aux_t* pares = aux_crear();
    lista_iterar(lista, guardar_pares, pares);
    print_test("    ๛ Prueba con función visitar que pasa por todos los elementos pares", strcmp(datos, pares->txt) == 0);
    free(pares);

    /* Pruebo guardar los primeros datos de la lista en una cadena */
    char* prim = "ABC";
    aux_t* primeros = aux_crear();
    lista_iterar(lista, guardar_todos, primeros);
    print_test("    ๛ Prueba con función visitar que pasa por los primeros 3 elementos", strcmp(prim, primeros->txt));
    free(primeros);


    lista_destruir(lista, NULL);
}

void pruebas_iterador_externo(){
    printf("\n༺ INICIO DE PRUEBAS CON EL ITERADOR EXTERNO ༻  \n");
    
    /* Variables a utilizar */
    lista_t* lista1 = lista_crear();
    int num[] = {1, 2, 3, 4, 5}; 
    int* valor1 = &num[0];
    int* valor2 = &num[1];
    int* valor3 = &num[2];
    int* valor4 = &num[3];
    int* valor5 = &num[4];
    lista_iter_t* iterador = lista_iter_crear(lista1);

    /* Prueba sin agregar*/
    printf("     CON UNA LISTA VACÍA\n");
    print_test("    ๛ Ver actual da NULL", lista_iter_ver_actual(iterador) == NULL);
    print_test("    ๛ Avanzar da false", !lista_iter_avanzar(iterador));
    print_test("    ๛ Ver si está al final da true", lista_iter_al_final(iterador));
    print_test("    ๛ Insertar al elemento valor1 da true", lista_iter_insertar(iterador, valor1));     ///
    print_test("    ๛ El iterador está parado en el elemento actual", lista_iter_ver_actual(iterador) == valor1);
    print_test("    ๛ Ver si está al final da false", !lista_iter_al_final(iterador));
    print_test("    ๛ Agregar otro elemento da true", lista_iter_insertar(iterador, valor2));   ////
    print_test("    ๛ El primer elemento es valor2", lista_ver_primero(lista1) == valor2);
    print_test("    ๛ Ver el último da valor1", lista_ver_ultimo(lista1) == valor1);
    print_test("    ๛ Avanzar el iterador da true", lista_iter_avanzar(iterador));
    print_test("    ๛ Agregar a valor3 da true", lista_iter_insertar(iterador, valor3));
    print_test("    ๛ El último elemento sigue siendo valor1", lista_ver_ultimo(lista1) == valor1);
    print_test("    ๛ Borrar el elemento devuelve a valor3", lista_iter_borrar(iterador) == valor3);
    print_test("    ๛ Ahora el iterador está parado en el valor1", lista_iter_ver_actual(iterador) == valor1);
    printf("     USO UN NUEVO ITERADOR \n");
    lista_iter_t* iterador2 = lista_iter_crear(lista1);
    int valor6 = 6;
    print_test("    ๛ Insertar al elemento valor6 da true", lista_iter_insertar(iterador2, &valor6));
    print_test("    ๛ Avanzar da true", lista_iter_avanzar(iterador2));
    print_test("    ๛ Ver actual da valor2", lista_iter_ver_actual(iterador2) == valor2);
    print_test("    ๛ Avanzo iterador2 ", lista_iter_avanzar(iterador2));
    print_test("    ๛ Los dos estan parados en el mismo ", lista_iter_ver_actual(iterador2) == lista_iter_ver_actual(iterador));
    print_test("    ๛ Avanzar el iterador da true", lista_iter_avanzar(iterador));
    print_test("    ๛ Ver si está al final da true", lista_iter_al_final(iterador));
    print_test("    ๛ Avanzar el iterador da falso", !lista_iter_avanzar(iterador));
    lista_iter_destruir(iterador);
    lista_destruir(lista1, NULL);
    lista_iter_destruir(iterador2);


    /* Creo una lista y agrego elementos */
    printf("\n     USO UNA NUEVA LISTA \n");
    lista_t* lista = lista_crear();
    lista_insertar_ultimo(lista, valor1);
    printf("    ๛ Inserto ultimo valor1 \n");
    lista_insertar_ultimo(lista, valor2);
    printf("    ๛ Inserto ultimo valor2 \n");

    lista_iter_t* iterador_2 = lista_iter_crear(lista);

    print_test("    ๛ Ver actual da valor1", lista_iter_ver_actual(iterador_2) == valor1);
    print_test("    ๛ El iterador no esta al FINAL", !lista_iter_al_final(iterador_2));
    print_test("    ๛ BORRO el valor1",lista_iter_borrar(iterador_2)== valor1);
    print_test("    ๛ Ver actual da valor2", lista_iter_ver_actual(iterador_2) == valor2);
    print_test("    ๛ El iterador no esta al FINAL", !lista_iter_al_final(iterador_2));
    print_test("    ๛ Inserto un valor", lista_iter_insertar(iterador_2, valor3));    ///
    print_test("    ๛ Avanzo al siguiente",lista_iter_avanzar(iterador_2));
    print_test("    ๛ Ver actual da valor2", lista_iter_ver_actual(iterador_2) == valor2);
    print_test("    ๛ Borro a valor2",lista_iter_borrar(iterador_2) == valor2);
    print_test("    ๛ Ver actual da NULL", lista_iter_ver_actual(iterador_2) == NULL);
    print_test("    ๛ Avanzar da false", !lista_iter_avanzar(iterador_2));
    print_test("    ๛ Inserto otro valor", lista_iter_insertar(iterador_2, valor4));
    print_test("    ๛ Ver actual da valor4",lista_iter_ver_actual(iterador_2) == valor4);
    print_test("    ๛ Avanzo al siguiente",lista_iter_avanzar(iterador_2));
    print_test("    ๛ El iterador esta al final", lista_iter_al_final(iterador_2));
    print_test("    ๛ Inserto en el final", lista_iter_insertar(iterador_2, valor5));
    print_test("    ๛ Ver actual da el insertado", lista_iter_ver_actual(iterador_2) == valor5);
    print_test("    ๛ Borro el valor5", lista_iter_borrar(iterador_2) == valor5);
    print_test("    ๛ Iterador esta en el final", lista_iter_al_final(iterador_2));

    lista_iter_destruir(iterador_2);
    lista_destruir(lista, NULL);
}

void pruebas_iterador_externo_volumen(){

    printf("\n༺ INICIO DE PRUEBAS VOLUMEN DEL ITERADOR EXTERNO ༻  \n");
    int arreglo[100000];
    lista_t* lista = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista);
    for (int i=0;i<99999;i++){
        arreglo[i] = i;
        lista_iter_insertar(iterador, &arreglo[i]);
        if(i<99998){
        lista_iter_avanzar(iterador);
        }
    }
    printf("     AGREGO 100000 ELEMENTOS A LA LISTA \n ");
    print_test("    ๛ Ver actual da el elemento del arreglo[999998]", lista_iter_ver_actual(iterador) == &arreglo[99998]);
    print_test("    ๛ Avanzar da true", lista_iter_avanzar(iterador));
    print_test("    ๛ El iterador esta al final", lista_iter_al_final(iterador));

    lista_destruir(lista,NULL);
    lista_iter_destruir(iterador);
}

void prueba_adicional(){
    printf("\n༺ INICIO DE PRUEBAS ADICIONALES ༻  \n");

    /* Variables a utilizar */
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int num[] = {1, 2, 3, 4, 5}; 
    int* a = &num[0];
    int* b = &num[1];
    int* c = &num[2];

    // Insertar en lista vacía:
    print_test("    ๛ Inserta con el iterador al principio de lista vacia", lista_iter_insertar(iter, a) );
    print_test("    ๛ No está al final", ! lista_iter_al_final(iter) );

    // Inserción al final
    print_test("    ๛ Avanza después de insertar", lista_iter_avanzar(iter) );
    print_test("    ๛ Avanzar devuelve false", !lista_iter_avanzar(iter) );
    print_test("    ๛ Inserción con el iterador al final", lista_iter_insertar(iter, b) );
    lista_iter_destruir(iter);
    print_test("    ๛ Inserta uno mas luego del insertado", lista_insertar_ultimo(lista, c));

    lista_iter_t *jter = lista_iter_crear(lista);
    print_test("    ๛ Creacion de un nuevo iterador", jter);
    print_test("    ๛ Avanzo en el segundo iterador", lista_iter_avanzar(jter));
    print_test("    ๛ Ver actual con el iterador", lista_iter_ver_actual(jter) == b );
    lista_iter_destruir(jter);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante() {
    pruebas_lista_vacia();
    pruebas_lista_algunos_elementos();
    pruebas_iterador_interno();
    pruebas_iterador_externo();
    pruebas_iterador_externo_volumen();   
    prueba_adicional(); 
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif


// gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c

//  valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
