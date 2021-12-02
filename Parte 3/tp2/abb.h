#include <stdbool.h>
#include <stddef.h>
typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);


/* Crea un arbol*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

/* Guarda un elemento en el arbo, si la clave ya se encuentra en la
 * estructura, reemplaza el dato. De no poder guardarlo devuelve false.
 * Pre: La estructura arbo fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un elemento del arbol y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura arbol fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el valor de un elemento del arbol, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura arbol fue inicializada
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al arbol.
 * Pre: La estructura arbol fue inicializada
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del arbol.
 * Pre: La estructura arbol fue inicializada
 */
size_t abb_cantidad(const abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura arbol fue inicializada
 * Post: La estructura arbol fue destruida
 */
void abb_destruir(abb_t *arbol);


// Se llama a la función visitar para que se encargue de recorrer todos los
// los elementos del arbol hasta que dicha función devuelva falso. El parámetro
// extra es usado dentro de la función visitar a criterio de quien use el arbol.
// Pre: el arbol fue creado. visitar es una función capaz de realizar una acción
// a cada paso de la iteración. extra es un puntero genérico a un parametro o NULL.
// Post: se iteró el arbol al completo o hasta que la función visitar devolvió false
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


typedef struct abb_iter abb_iter_t;

// Crea iterador
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza iterador
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Comprueba si terminó la iteración
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador
void abb_iter_in_destruir(abb_iter_t* iter);

/* *****************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
void pruebas_lista_estudiante(void);