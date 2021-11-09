// Escribir una función que reciba dos cadenas de caracteres y retorne true si ambas palabras son anagramas entre sí, o false
// en caso contrario. Dos palabras son anagramas si y solo si una palabra se puede formar reordenando las letras de la otra.
// Indicar y justificar la complejidad de la función implementada. Ejemplos de uso:
// son_anagramas("iman", "mani") => True
// son_anagramas("sol", "losa") => False

bool son_anagramas(char* palabra1, char* palabra2) {
    size_t len1 = strlen(palabra1);
    size_t len2 = strlen(palabra2);
    if (len1 != len2) {
        return false;
    }
    hash_t* hash = hash_crear(NULL);
    bool resultado = true;
    for (size_t i = 0; i < len1; i++) {
        int valor = hash_pertenece(hash, palabra1[i]) ? hash_obtener(hash, palabra1[i]) + 1 : 1; 
        hash_guardar(hash, palabra1[i], valor);
    }
    for (size_t i = 0; i < len1; i++) {
        int valor = hash_pertenece(hash, palabra2[i]) ? hash_obtener(hash, palabra2[i]) - 1 : -1;
        if (valor < 0) {
            resultado = false;
            break;
        }
        hash_guardar(hash, palabra2[i], valor);
    }
    hash_destruir(hash);
    return resultado;
}

/* ::Aclaración:: ->> Se está utilizando al hash como si las claves fueran de tipo char y no char*
 */


/*  •{Complejidad de la función}•
 * Esta función es O(n), siendo n la cantidad de caracteres de la palabra
 * Es así debido a que se recorre la palabra 1 y se guarda en un hash el caracter
 * y su cantidad de apariciones, luego se recorre la palabra 2 y se va restando la
 * cantidad de apariciones de cada caracter según corresponda, así hasta terminar
 * el ciclo y dar true o cortar antes y devolver false.
 * (Contar los largos de cada cadena se puede tomar como O(n) por más que no sé
 * exactamente lo que hace la función strlen por dentro, pero para contar el largo
 * de una cadena no hay razones para creer que pueda ser diferente)
 * (Todo el resto de lo que se hace dentro y fuera de cada ciclo es O(1))
 * T(n) = 4 O(n) -> O(n) (4 O(n) debido a que se realizan dos ciclos que cada uno
 * repite n veces O(1) y dos veces O(n) para contar el largo de las cadenas)
*/