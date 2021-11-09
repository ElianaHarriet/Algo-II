// Para una implementación completa de Lista (como se implementó en el trabajo de TDA Lista), implementar una función
// void* borrar_ultimo_de_lista(lista_t* lista), que quite y devuelva el último elemento de la lista. En caso de que
// la lista esté vacía devuelve NULL. Indicar y justificar la complejidad de la función implementada.

void* borrar_ultimo_de_lista(lista_t* lista) {
    if (lista_esta_vacia(lista)) {
        return NULL;
    }
    lista_iter_t* iter1 = lista_iter_crear(lista);
    lista_iter_t* iter2 = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter1)) {
        lista_iter_avanzar(iter1);
        if (!lista_iter_al_final(iter1)) {
            lista_iter_avanzar(iter2);
        }
    }
    void* dato = lista_iter_borrar(iter2);
    lista_iter_destruir(iter1);
    lista_iter_destruir(iter2);
    return dato;
}

/* •{Complejidad de la función}•
 * Esta función es O(n), siendo n la cantidad de elementos de la lista.
 * Es así debido a que se debe recorrer con un iterador hasta el final 
 * de la lista, e ir avanzando otro iterador hasta que se llega al
 * último elemento
 * Ver si la lista está vacía, crear los iteradores, ver si está el iter1
 * al final, avanzar los iteradores, obtener el dato y borrarlo, destruir
 * los iteradores, y, finalemente, devolver el dato (o NULL) es todo O(1).
 * El while repite la operación de ir avanzando los iteradores, n veces,
 * es por eso que queda O(n).
 */
