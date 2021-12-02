#ifndef POST_H
#define POST_H

typedef struct post post_t;

post_t* post_crear(size_t id, char* txt, char* usuario, int pos_lista_usuario);

size_t get_post_id(post_t* post);

size_t get_post_cant_likes(post_t* post);

char* get_usuario(post_t* post);

char* get_post_txt(post_t* post);

int get_pos_lista_usuario(post_t* post);

void post_destruir(void* _post);

void post_likear(post_t* post, char* usuario);

void post_mostrar_likes(post_t* post);

#endif // POST_H