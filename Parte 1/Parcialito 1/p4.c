// 4. Dado un array ordenado y un número N, implementar una función por división y
// conquista que permita encontrar la posición de la última aparición de N.
// Justificar el orden del algoritmo.
// Ejemplo:
// [1,2,2,2,3,3,4,4,4,5] N = 2 -> 3
// [1,2,2,2,3,3,4,4,4,5] N = 5 -> 9
// [1,2,2,2,3,3,4,4,4,5] N = 6 -> -1

int _pos_ult_n(int arreglo[], int n, size_t desde, size_t hasta) {
    if (desde == hasta) {
        return arreglo[desde] == n ? (int)desde : -1;
    }
    size_t mitad = (desde + hasta) / 2;
    if (arreglo[mitad] < n) {
        return _pos_ult_n(arreglo, n, mitad + 1, hasta);
    } else if (arreglo[mitad] == n) {
        return _pos_ult_n(arreglo, n, mitad, hasta);
    } else {
        return _pos_ult_n(arreglo, n, desde, mitad - 1);
    }
}

int pos_ult_n(int arreglo[], int n, size_t len) {
    if (arreglo[len - 1] < n || arreglo[0] > n) {
        return -1;
    }
    return _pos_ult_n(arreglo, n, 0, len);
}

/****************************************************************************\ 
                            •{Orden del algoritmo}•
                (Para un k, siendo k el largo del arreglo)
Llamadas recursivas -> 1 (Figuran 3, pero sólo se accede a 1)
El arreglo se parte a la mitad en cada llamada recursiva
Todo lo que no es llamada recursiva -> O(1)
T(k) = T(k/2) + O(1)
Por el teorema maestro: A = 1, B = 2, C = 0
log_{B}(A) = 0 = C -> T(k) = O(k^C log(k))
=> T(k) = O(log(k))
\****************************************************************************/