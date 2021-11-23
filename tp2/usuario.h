#ifndef USUARIO_H
#define USUARIO_H
#include "heap.h"
#include "post.h"

typedef struct usuario usuario_t;

usuario_t* usuario_crear(char* nombre, int pos); 

char* get_nombre(usuario_t* usuario);

heap_t* get_posts(usuario_t* usuario);

int get_pos_lista(usuario_t* usuario);

void usuario_destruir(void* _usuario);

void usuario_agregar_post(usuario_t* usuario, post_t* post);

post_t* sig_post(usuario_t* usuario);

#endif  // USUARIO_H