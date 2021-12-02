#ifndef POST_H
#define POST_H

typedef struct post post_t;

/* *********************************************************************
 *                       PRIMITIVAS DE POST
 * *********************************************************************/

/* Crea un post.
 * Recibe el id, el texto, quién lo posteó y la posición de dicho usuario en <usuarios.txt>.
 * Post: Devuelve un post con los atributos pasados por parámetro.
 */
post_t* post_crear(size_t id, char* txt, char* usuario, int pos_lista_usuario);

/* Devuelve el id del post.
 * Pre: Recibe un post.
 */
size_t get_post_id(post_t* post);

/* Devuelve la cantidad de likes del post.
 * Pre: Recibe un post.
 */
size_t get_post_cant_likes(post_t* post);

/* Devuelve quién lo posteó.
 * Pre: Recibe un post.
 */
char* get_usuario(post_t* post);

/* Devuelve el texto del post.
 * Pre: Recibe un post.
 */
char* get_post_txt(post_t* post);

/* Devuelve la posición del usuario en <usuarios.txt>.
 * Pre: Recibe un post.
 */
int get_pos_lista_usuario(post_t* post);

/* Likea el post.
 * Pre: Recibe un post y quién lo likea.
 * Post: Se actualiza el post.
 */
void post_likear(post_t* post, char* usuario);

/* Imprime la cantidad de likes del post y quiénes le dieron like.
 * Pre: Recibe un post.
 */
void post_mostrar_likes(post_t* post);

/* Destruye el post.
 * Pre: Recibe un post.
 */
void post_destruir(void* _post);

#endif // POST_H