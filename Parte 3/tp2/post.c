#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include "post.h"
#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"



struct post {
    size_t id;
    char* txt;
    char* usuario;
    size_t cant_likes;
    abb_t* usuarios_like;
    int pos_lista_usuario;
};

post_t* post_crear(size_t id, char* txt, char* usuario, int pos_lista_usuario) {
    post_t* post = malloc(sizeof(post_t));
    if (!post) return NULL;
    post->id = id;
    post->txt = strdup(txt);
    post->cant_likes = 0;
    post->usuario = usuario;
    post->usuarios_like = abb_crear(strcmp, NULL);
    post->pos_lista_usuario = pos_lista_usuario;
    if (!post->usuarios_like) {
        free(post);
        return NULL;
    }
    return post;
}

size_t get_post_id(post_t* post) {
    return post->id;
}

size_t get_post_cant_likes(post_t* post) {
    return post->cant_likes;
}

char* get_usuario(post_t* post) {
    return post->usuario;
}

char* get_post_txt(post_t* post) {
    return post->txt;
}

int get_pos_lista_usuario(post_t* post) {
    return post->pos_lista_usuario;
}

void post_destruir(void* _post) {
    post_t* post = _post;
    if (!post) return;
    free(post->txt);
    abb_destruir(post->usuarios_like);
    free(post);
}

void post_likear(post_t* post, char* usuario) {
    if (abb_pertenece(post->usuarios_like, usuario)) return;
    abb_guardar(post->usuarios_like, usuario, NULL);
    post->cant_likes++;
}

bool imprimir_usuario(const char* clave, void* dato, void* extra) {
    printf("\t%s\n", clave);
    return true;
}

void post_mostrar_likes(post_t* post) {
    fprintf(stdout, "El post tiene %zu likes:\n", post->cant_likes);
    abb_in_order(post->usuarios_like, imprimir_usuario, NULL);
}
