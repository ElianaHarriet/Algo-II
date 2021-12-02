#ifndef ALGOGRAM_H
#define ALGOGRAM_H
#include "hash.h"


typedef struct algo_gram algo_gram_t;

/* *********************************************************************
 *                               ALGOGRAM
 * *********************************************************************/

/* Crea un algo_gram_t vacio.
 */
algo_gram_t* algo_gram_crear(char* path);

/* Devuelve el hash con todos los usuarios del algo_gram_t pasado
 * pasado por parámetro.
 */
hash_t* get_usuarios(algo_gram_t* gram);

/* A partir de un nombre, se lo busca en el algogram, y si
 * lo encuentra, se loguea
 */
void login(algo_gram_t* gram, const hash_t* usuarios, char* nombre);

/* Sale del usuario logueado en algogram
 */
void logout(algo_gram_t* gram);


/* A partir del usuario logueado en algogram, publica un mensaje a su
 * nombre y lo agrega en los heaps de los otros usuarios teniendo en cuenta
 * la prioridad de este con los otros
 */
void publicar(algo_gram_t* gram, char* texto);

/* Se muestra el siguiente de todos los posteos que le quedan por ver al usuario
 * logueado, con la forma:
    Post id: n
    usuario_x dijo: <texto posteo_x>
    Likes: k
*/
void ver_posts(algo_gram_t* gram);

/* Se da like a un posteo dado el id del post, y se agrega el nombre del usuario
 * que le dio likea los likes del post
 */
void dar_like(algo_gram_t* gram, char* id);

/* Se muestran todos los likes de un post dado el id con los nombres de los
 * usuarios que le hayan dado like de la forma:
    El post tiene n likes:
    usuario_1
    usuario_2
    usuario_3
    usuario_4 ...
 */
void mostrar_likes(algo_gram_t* gram, char* id);

/* Destruye el algo_gram_t pasado por parámetro.
 */
void algo_gram_destruir(algo_gram_t* gram);

#endif  // ALGOGRAM_H