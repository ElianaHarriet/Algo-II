// /* crea una copia (memoria dinamica) de la cadena pasada por parametro */
// char* strdup(const char* org) {
//     char* cpy = malloc(sizeof(char) * (strlen(org) + 1));
//     if (!cpy) return NULL;
//     strcpy(cpy, org);
//     return cpy;
// }

campo_hash_t* campo_crear(const char* clave, void* dato) {
    campo_hash_t* campo = malloc(sizeof(campo_hash_t));
    if (campo == NULL) {
        return NULL;
    }
    campo->clave = strdup(clave);
    campo->dato = dato;
    campo->num_fhash = 1;
    return campo;
}

size_t contrasena(const char* clave, size_t num_fhash, size_t tam_tabla){
    if (num_fhash == 1 ){
        return h1(clave, tam_tabla);
    }
    return h2(clave, tam_tabla);
}

bool _hash_guardar(hash_t* hash, const char* clave, void* dato, size_t num_fhash, const char* original){
    campo_hash_t* campo = campo_crear(clave, dato);
    if (campo == NULL) {
        return false;
    }
    size_t contra =  contrasena(clave, num_fhash, hash->tam_tabla);
    campo_hash_t actual = hash->tabla[contra];
    if(actual.clave == NULL){
        actual = *campo;
        return true;
    }
    if (actual.clave == original){
        return false;
    }
    size_t hash_fun = actual.num_fhash;
    size_t nueva_fun = (hash_fun + 1) % 2 + 1;
    bool guardo = _hash_guardar(hash, actual.clave, actual.dato, nueva_fun, original);
    hash->tabla[contra] = *campo;
    return guardo;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    return _hash_guardar(hash, clave, dato, 1, clave);
}