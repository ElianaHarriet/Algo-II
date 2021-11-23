#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "usuario.h"
#include "post.h"



/* *********************************************************************
 *                            STRUCTS
 * *********************************************************************/
typedef struct algo_gram {
    const hash_t* usuarios;
    usuario_t* logged;
    hash_t* posts;
    size_t ult_id;
    hash_t* hash_pos_usuarios;
} algo_gram_t;


/* *********************************************************************
 *                            IMPLEMENTACION
 * *********************************************************************/


// hash_t* hash_pos_usuarios(algo_gram_t* gram, FILE** archivo) {    // hash : eliana= 0 ......
//     hash_t* pos_usuarios = hash_crear(free);
//     if (!pos_usuarios) return NULL;
//     char* linea = NULL;
//     size_t tam;
//     char* linea = NULL;
//     size_t tam;
//     size_t i = 0;
//     while((getline(&linea, &tam, archivo)) != EOF){
//         size_t* pos = malloc(sizeof(size_t));
//         *pos = i;
//         hash_guardar(pos_usuarios, linea, pos);
//     }
//     return pos_usuarios;
// }




int open_file(char* name, FILE** archivo) {
    *archivo = fopen(name, "r");
    if (*archivo == NULL) {
        return -1;
    }
    return 0;
}

hash_t* obtener_usuarios(char* path){
    FILE* archivo;
    int val_archivo = open_file(path, &archivo);
    if (val_archivo == -1) {
        printf("Error: archivo fuente inaccesible\n");
        return NULL;
    }
    hash_t* usuarios = hash_crear(NULL);   ///usuario_destruir
    char* linea = NULL;
    size_t tam;
    int pos_lista = 0;
    while((getline(&linea, &tam, archivo)) != EOF){
        linea[strlen(linea) - 1] = '\0';
        usuario_t* usuario = usuario_crear(linea, pos_lista);
        // printf("%s\n", get_nombre(usuario));
        hash_guardar(usuarios, linea, usuario);
        pos_lista++;
    }
    free(linea);
    return usuarios;
}

algo_gram_t* algo_gram_crear(char* path) {
    algo_gram_t* algo = malloc(sizeof(algo_gram_t));
    if (!algo) return NULL;
    algo->usuarios = obtener_usuarios(path);
    algo->posts = hash_crear(NULL);
    algo->ult_id = 0;
    algo->logged = NULL;
    return algo;
}

bool login(algo_gram_t* gram, const hash_t* usuarios, char* nombre){
    if (gram->logged != NULL) {
        fprintf(stdout, "%s", "Error: Ya habia un usuario loggeado\n");
        return false;
    }
    usuario_t* usuario = hash_obtener(usuarios, nombre);
    if (!usuario) {
        fprintf(stdout,"%s","Error: usuario no existente\n");
        return false;
    }
    gram->logged = usuario;
    fprintf(stdout, "Hola %s\n", get_nombre(usuario));
    return true;
}

void logout(algo_gram_t* gram){
    if (gram->logged == NULL) {
        fprintf(stdout, "%s", "Error: no habia usuario loggeado\n");
        return;
    }
    fprintf(stdout, "Adios\n");
    gram->logged = NULL;
}

void publicar(algo_gram_t* gram, char* texto){
    if (gram->logged == NULL){
        fprintf(stdout, "%s", "Error: no habia usuario loggeado\n");
        return;
    }
    post_t* post = post_crear(gram->ult_id, texto, get_nombre(gram->logged), get_pos_lista(gram->logged));
    if(!post) return;
    hash_t* posts = gram->posts;
    char id[10];
    sprintf(id, "%zu", get_post_id(post));
    hash_guardar(posts, id, post);
    gram->ult_id++;
    hash_iter_t* iter_usuarios = hash_iter_crear(gram->usuarios);
    if(iter_usuarios == NULL) return;
    while (!hash_iter_al_final(iter_usuarios)) {
        usuario_t* usuario = hash_obtener(gram->usuarios, hash_iter_ver_actual(iter_usuarios));
        if (strcmp(get_nombre(usuario), get_nombre(gram->logged)) != 0) {
            usuario_agregar_post(usuario, post);
        }
        hash_iter_avanzar(iter_usuarios);
    }  
    hash_iter_destruir(iter_usuarios);
    fprintf(stdout, "Post publicado\n");
}

void ver_posts(algo_gram_t* gram){
    if (gram->logged == NULL){
        fprintf(stdout, "%s", "Usuario no loggeado o no hay mas posts para ver\n");
        return;
    }
    usuario_t* usuario = gram->logged;
    heap_t* posts = get_posts(usuario);
    if(heap_esta_vacio(posts)){
        fprintf(stdout, "%s", "Usuario no loggeado o no hay mas posts para ver\n");
        return;
    }
    post_t* post = sig_post(gram->logged);
    char like[20];
    sprintf(like, "Likes: %zu", get_post_cant_likes(post));
    char texto[300];
    sprintf(texto, "%s dijo: %s", get_usuario(post), get_post_txt(post));
    char post_id[20];
    sprintf(post_id, "Post ID %zu", get_post_id(post));
    fprintf(stdout, "%s\n%s\n%s\n", like, texto,post_id);
    return;
}

void dar_like(algo_gram_t* gram, char* id){
    if (gram->logged == NULL || !hash_pertenece(gram->posts, id)){
        fprintf(stdout, "%s", "Error: Usuario no loggeado o Post inexistente\n");
        return;
    }
    post_t* post = hash_obtener(gram->posts, id);
    post_likear(post, get_nombre(gram->logged));
    fprintf(stdout, "Post likeado\n");
}

void mostrar_likes(algo_gram_t* gram, char* id) {
    if (!hash_pertenece(gram->posts, id)) {
        fprintf(stdout, "%s", "Error: Post inexistente o sin likes\n");
        return;
    }
    post_t* post = hash_obtener(gram->posts, id);
    if (get_post_cant_likes(post) == 0) {
        fprintf(stdout, "%s", "Error: Post inexistente o sin likes\n");
        return;
    }
    post_mostrar_likes(post);
}

void imprimir_hash(const hash_t* hash){
    hash_iter_t* iter = hash_iter_crear(hash);
    while(!hash_iter_al_final(iter)){
        printf("(hash clave) actual hash iter -> %s\n", hash_iter_ver_actual(iter));
        printf("(hash valor) usuario nombre -> %s\n", get_nombre(hash_obtener(hash, hash_iter_ver_actual(iter))));
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
}

int main(int argc, char* argv[]){
    // printf("%s\n", "Bienvenido a AlgoGram");
    if(argc != 2){
        fprintf(stdout, "%s", "Error: Cantidad de argumentos invalida\n");
        return -1;
    }
    algo_gram_t* gram = algo_gram_crear(argv[1]);
    // imprimir_hash(gram->usuarios);
    if(gram == NULL){
        fprintf(stdout, "%s", "Error: No se pudo crear el algo_gram\n");
        return -1;
    }
    if(!gram->usuarios){
        fprintf(stdout, "%s", "Error: No se pudo cargar los usuarios\n");
        return -1;
    }
    char* linea = NULL;
    size_t capacidad = 0;
    ssize_t leidos = getline(&linea, &capacidad, stdin);
    linea[strlen(linea) - 1] = '\0';
    while (leidos > 0) {
        if (strcmp("login", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* nombre = linea;
            login(gram, gram->usuarios, nombre); // -> da un bool (por si fuera necesario)
        } else if (strcmp("logout", linea) == 0) {
            logout(gram);
        } else if (strcmp("publicar", linea) == 0){
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* texto = linea;
            publicar(gram, texto);
        } else if (strcmp("likear_post", linea) == 0) {
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* id = linea;
            dar_like(gram, id);
        } else if(strcmp("mostrar_likes", linea) == 0){
            leidos = getline(&linea, &capacidad, stdin);
            linea[strlen(linea) - 1] = '\0';
            char* id = linea;
            mostrar_likes(gram, id);
        } else if(strcmp("ver_siguiente_feed", linea) == 0){
            ver_posts(gram);
        }
        leidos = getline(&linea, &capacidad, stdin);
        linea[strlen(linea) - 1] = '\0';
    }
    free(linea);
}

// gcc -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c
