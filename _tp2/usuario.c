#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include <stdio.h>
#include "hash.h"




struct usuario {
    char* nombre;
    heap_t* posts;
    int pos_lista;
    hash_t* post;
};

typedef struct info_post_heap {
    int pos_usuario_heap;
    post_t* post;
} info_post_heap_t;

int distancia(int pos_usuario_heap, int pos_usuario_post){
    int distancia = pos_usuario_heap - pos_usuario_post;
    return distancia > 0 ? distancia : distancia * -1;
}

int afinidad(const void* usuario_post_1, const void* usuario_post_2) {
    info_post_heap_t* info_1 = (info_post_heap_t*) usuario_post_1;
    info_post_heap_t* info_2 = (info_post_heap_t*) usuario_post_2;

    int distancia_1 = distancia(info_1->pos_usuario_heap, get_pos_lista_usuario(info_1->post));
    int distancia_2 = distancia(info_2->pos_usuario_heap, get_pos_lista_usuario(info_2->post));

    // fprintf(stderr, "\nEs el heap del usuario de la línea %d\n", info_1->pos_usuario_heap);
    // fprintf(stderr, "Se compara el post de %s con el de %s\n", get_usuario(info_1->post), get_usuario(info_2->post));
    // fprintf(stderr, "La distancia de %s es -> %d | ", get_usuario(info_1->post), distancia_1);
    // fprintf(stderr, "La distancia de %s es -> %d\n", get_usuario(info_2->post), distancia_2);
    // fprintf(stderr, "La función retorna %d\n\n", (distancia_1 - distancia_2) * -1);
    
    size_t post_id_1 = get_post_id(info_1->post);
    size_t post_id_2 = get_post_id(info_2->post);

    return (distancia_1 - distancia_2) * -1 != 0 ? (distancia_1 - distancia_2) * -1 :
            post_id_1 > post_id_2 ? -1 : 1;
}


usuario_t* usuario_crear(char* nombre, int pos){
    usuario_t* usuario = malloc(sizeof(usuario_t));
    if (!usuario) return NULL;
    usuario->nombre = malloc(strlen(nombre) + 1);
    if (!usuario->nombre) {
        free(usuario);
        return NULL;
    }
    usuario->pos_lista = pos;
    strcpy(usuario->nombre, nombre);
    usuario->posts = heap_crear(afinidad);
    if(usuario->posts == NULL){
        free(usuario);
        return NULL; 
    }
    return usuario;
}

info_post_heap_t* info_post_crear(int pos_usuario_heap, post_t* post){
    info_post_heap_t* info_post = malloc(sizeof(info_post_heap_t));
    if (!info_post) return NULL;
    info_post->pos_usuario_heap = pos_usuario_heap;
    info_post->post = post;
    return info_post;
}

void info_post_destruir(void* _info_post){
    info_post_heap_t* info_post = (info_post_heap_t*) _info_post;
    free(info_post);
}

char* get_nombre(usuario_t* usuario){
    return usuario->nombre;
}

heap_t* get_posts(usuario_t* usuario){
    return usuario->posts;
}

int get_pos_lista(usuario_t* usuario){
    return usuario->pos_lista;
}


void usuario_destruir(void* _usuario){
    usuario_t* usuario = _usuario;
    if(!usuario) return;
    heap_destruir(usuario->posts, info_post_destruir);
    free(usuario->nombre);
    free(usuario);
}

void usuario_agregar_post(usuario_t* usuario, post_t* post){
    if(!usuario || !post) return;
    info_post_heap_t* info_post = info_post_crear(usuario->pos_lista, post);
    if(!info_post) return;
    heap_encolar(usuario->posts, info_post);
    // printf("usuario: %s, ver max : %s\n", get_nombre(usuario) ,get_post_txt(heap_ver_max(usuario->posts)));
}

post_t* sig_post(usuario_t* usuario){
    if(!usuario) return NULL;
    info_post_heap_t* info_post = heap_desencolar(usuario->posts);
    if(!info_post) return NULL;
    post_t* post = info_post->post;
    info_post_destruir(info_post);
    return post;
}

//ver prox