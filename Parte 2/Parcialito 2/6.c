// Dado un árbol binario que tiene como datos números enteros, implementar una primitiva que reemplace el valor de todos
// los nodos del árbol de manera tal que cada nodo X tenga como valor la cantidad de nodos que existen en la sub-rama
// de ese nodo X. En otras palabras, para cada nodo el valor resultante representa su cantidad de hijos, nietos, bis-nietos,
// bis-bis-nietos, etc. Ayuda: para la raíz, este valor es igual a la cantidad de elementos en el árbol, menos 1. Para las hojas,
// el valor es de 0, ya que no tiene descendientes. ¿Cuál es el orden de la primitiva implementada? ¿Qué tipo de recorrido
// utilizaste? La estructura de cada nodo es la siguiente:
// typedef struct ab_t {
// int valor;
// struct ab_t* izq;
// struct ab_t* der
// } ab_t;

void _reemplazar(ab_t* arbol) {
    if (arbol == NULL) {
        return;
    }
    
    int izq = arbol->izq == NULL ? 0 : arbol->izq->valor + 1;
    int der = arbol->der == NULL ? 0 : arbol->der->valor + 1;
    arbol->valor = izq + der;
}

void reemplazar(ab_t* arbol) {
    _reemplazar(arbol->izq);
    _reemplazar(arbol->der);
    _reemplazar(arbol);
}

/* •{Orden de la primitiva}•
 * El orden de la primitiva es O(n), siendo n la cantidad de nodos
 * que tiene el árbol.
 * Se debe a que el reemplazo hay que hacerlo en todos los nodos del
 * árbol.
 * 
 * •{Tipo de recorrido}•
 * El tipo de recorrido utilizado es postorder debido a que se va
 * reemplazando el valor desde las hojas hasta la raíz.
 * Esto es así debido a que se va usando el valor que tiene cada hijo
 * para calcular el valor de su padre, hasta llegar a la raíz.
 */