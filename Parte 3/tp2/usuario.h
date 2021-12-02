#ifndef USUARIO_H
#define USUARIO_H
#include "heap.h"
#include "post.h"

typedef struct usuario usuario_t;

/* *********************************************************************
 *                       PRIMITIVAS DE USUARIO
 * *********************************************************************/

/* Crea un usuario.
 * Pre: Recibe un nombre de usuario y la posición del usuario en <usuarios.txt>.
 * Post: Devuelve un usuario.
 */
usuario_t* usuario_crear(char* nombre, int pos); 

/* Devuelve el nombre del usuario.
 * Pre: Recibe un usuario.
 */
char* get_nombre(usuario_t* usuario);

/* Devuelve un heap con los posts del feed del usuario.
 * Pre: Recibe un usuario.
 * Post: Devuelve un heap con los posts que el usuario no vio todavía.
 */
heap_t* get_posts(usuario_t* usuario);

/* Devuelve la posición del usuario en <usuarios.txt>.
 * Pre: Recibe un usuario.
 */
int get_pos_lista(usuario_t* usuario);

/* Destruye un usuario.
 * Pre: Recibe un usuario.
 */
void usuario_destruir(void* _usuario);

/* Agrega un post al heap de posts del usuario.
 * Pre: Recibe un usuario y un post.
 * Post: El heap de posts del usuario se actualiza.
 */
void usuario_agregar_post(usuario_t* usuario, post_t* post);

/* Devuelve el siguiente post del feed del usuario.
 * Pre: Recibe un usuario.
 */
post_t* sig_post(usuario_t* usuario);

#endif  // USUARIO_H