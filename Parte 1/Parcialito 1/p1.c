// 1. Dada una pila, implementar una función que devuelva el largo de la misma,
// la pila debe quedar en su estado original. Justificar el orden del algoritmo.

int len_pila(pila_t* pila) {
    pila_t* aux = pila_crear();
    int len = 0;
    while (!pila_esta_vacia(pila)) {
        pila_apilar(aux, pila_desapilar(pila));
        len++;
    }
    while (!pila_esta_vacia(aux)) {
        pila_apilar(pila, pila_desapilar(aux));
    }
    return len;
}

/****************************************************************************\ 
                            •{Orden del algoritmo}•
(Para un n, siendo n la cantidad de elementos en la pila)
Crear pila aux -> O(1)
Inicializar variable len -> O(1)
Primer while -> se ejecuta n veces
    Ver si la pila está vacía, apilar, desapilar e incrementar a len -> O(1)
    ->> n.O(1) ->> O(n)
Segundo while -> se ejecuta n veces
    Ver si la pila está vacía, apilar y desapilar -> O(1)
    ->> n.O(1) ->> O(n)

Total =>   T(n) = O(1) + O(1) + O(n) + O(n)
O(1) << O(n) -> = 2.O(n)
Finalmente => T(n) = O(n) -> Lineal
\****************************************************************************/