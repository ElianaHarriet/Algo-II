#include <stdlib.h>
#include <stdbool.h>

// Implementar un algoritmo en C que reciba un arreglo de enteros de tamaño nn, ordenado
// ascendentemente y sin elementos repetidos, y determine en O(log n) si es mágico.
// Un arreglo es mágico si existe algún valor i tal que 0 <= i y arr[i] = i.

// Ejemplos:
// A = [ -3, 0, 1, 3, 7, 9 ] es mágico porque A[3] = 3.
// B = [ 1, 2, 4, 6, 7, 9 ] no es mágico porque B[i] != i para todo i.
bool _arreglo_es_magico(int arr[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return arr[desde] == desde;
    }

    size_t medio = (desde + hasta) / 2;
    if (arr[medio] == medio) {
        return true;
    } else if (arr[medio] < medio) {
        return _arreglo_es_magico(arr, medio + 1, hasta);
    } else {
        return _arreglo_es_magico(arr, desde, medio - 1);
    }
}

bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n);
}


// Implementar, por división y conquista, una función que determine el mínimo de un arreglo.
int _minimo(int arreglo[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return arreglo[desde];
    }

    size_t medio = (desde + hasta) / 2;
    int min_izq = _minimo(arreglo, desde, medio);
    int min_der = _minimo(arreglo, medio + 1, hasta);

    return min_izq <= min_der ? min_izq : min_der;
}

int minimo(int arreglo[], size_t n) {
    return _minimo(arreglo, 0, n);
}

// Implementar, por división y conquista, una función que dado un arreglo y su largo, determine
// si el mismo se encuentra ordenado.
bool _arreglo_ordenado(int arreglo[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return true;
    }

    size_t medio = (desde + hasta) / 2;
    bool ord_izq = _arreglo_ordenado(arreglo, desde, medio);
    bool ord_der = _arreglo_ordenado(arreglo, medio + 1, hasta);
    bool ord_uni = arreglo[medio] <= arreglo[medio + 1];

    return ord_izq && ord_uni && ord_der;
}

bool arreglo_ordenado(int arr[], size_t n) {
    return _arreglo_ordenado(arr, 0, n);
} // T(n) = 2 T(n/2) + O(1) =>> Por teorema maestro T(n) = O(n)

// Implementar, por división y conquista, una función que dado un arreglo sin elementos repetidos y casi
// ordenado (todos los elementos se encuentran ordenados, salvo uno), obtenga el elemento fuera de lugar.
int _elemento_desordenado(int arreglo[], size_t desde, size_t hasta) {
    if (desde + 1 == hasta) {
        return arreglo[desde];
    }
    
    size_t medio = (desde + hasta) / 2;
    if (!_arreglo_ordenado(arreglo, desde, medio)) {
        int desord = _elemento_desordenado(arreglo, desde, medio);
    } else {
        int desord_der = _elemento_desordenado(arreglo, medio, hasta);    
    }
}

int elemento_desordenado(int arr[], size_t n) {
    return _elemento_desordenado(arr, 0, n);
} // T(n) = T(n/2) + O(n/2) = T(n/2) + O(n) =>> Por teorema maestro •{T(n) = O(n)}•

// Se tiene un arreglo tal que [1, 1, 1, …, 0, 0, …] (es decir, unos seguidos de ceros). Se pide una función de
// orden O(log(n)) que encuentre el índice del primer 0. Si no hay ningún 0 (solo hay unos), debe devolver -1.
int _primer_cero(int arreglo[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return (int)desde;
    }

    size_t medio = (desde + hasta) / 2;
    if (arreglo[medio] == 1) {
        return _primer_cero(arreglo, medio + 1, hasta);
    } else {
        return _primer_cero(arreglo, desde, medio);
    }    
}

int primer_cero(int arreglo[], size_t n) {
    if (arreglo[n - 1] == 1) {
        return -1;
    }
    return _primer_cero(arreglo, 0, n);
} // T(n) = T(n/2) + O(1) =>> Por teorema maestro •{T(n) = O(log(n))}•

// Implementar un algoritmo que, por división y conquista, permita obtener la parte entera de la raíz cuadrada
// de un número n, en tiempo O(log n). Por ejemplo, para n = 10 debe devolver 3, y para n = 25 debe devolver 5.
size_t _raiz_entera(size_t n, size_t desde, size_t hasta) {
    if (desde == hasta) {
        return desde;
    }

    size_t medio = (desde + hasta) / 2;
    size_t cuadrado = medio * medio;
    size_t cuadrado_sig = (medio + 1) * (medio + 1);

    if (cuadrado == n || (cuadrado < n && n < cuadrado_sig)) {
        return medio;
    } else if (cuadrado < n) {
        return _raiz_entera(n, medio + 1, hasta);
    } else {
        return _raiz_entera(n, desde, medio - 1);
    }
}

size_t raiz_entera(size_t n) {
    return _raiz_entera(n, 0, n/2); 
}

// Se tiene un arreglo de N >= 3 elementos en forma de pico, esto es: estrictamente creciente hasta una
// determinada posición p, y estrictamente decreciente a partir de ella (con 0 < p < N - 1).

// Por ejemplo, en el arreglo [1, 2, 3, 1, 0, -2] la posición del pico es p = 2.
// Se pide: implementar un algoritmo de división y conquista de orden O(log(n)) que encuentre la posición
// p del pico: size_t posicion_pico(int v[], size_t ini, size_t fin);. La función será invocará inicialmente
// como: posicion_pico(v, 0, n-1), y tiene como pre-condición que el arreglo tenga forma de pico.
size_t posicion_pico(int v[], size_t desde, size_t hasta) {
    if (desde == hasta) {
        return desde;
    }
    size_t medio = (desde + hasta) / 2;
    if (v[medio - 1] < v[medio] && v[medio] > v[medio + 1]) {
        return medio;
    } else if (v[medio - 1] < v[medio]) {
        return posicion_pico(v, medio, hasta);
    } else {
        return posicion_pico(v, desde, medio);
    }
}

// Implementar una función (que utilice división y conquista) de orden O(n logn) que dado un arreglo de
// n números enteros devuelva true o false según si existe algún elemento que aparezca más de la mitad de
// las veces.
// Ejemplos:
// [1, 2, 1, 2, 3] -> false
// [1, 1, 2, 3] -> false
// [1, 2, 3, 1, 1, 1] -> true
// [1] -> true
// Aclaración: Este ejercicio puede resolverse, casi trivialmente, ordenando el arreglo con un algoritmo
// eficiente, o incluso se puede realizar más rápido utilizando una tabla de hash. Para hacer interesante
// el ejercicio, resolver sin ordenar el arreglo, sino puramente división y conquista.
bool _mas_de_mitad(int* arreglo, size_t mitad, size_t n) {
    int menores[n];
    int iguales[n];
    int mayores[n];
    size_t a = 0;
    size_t b = 0;
    size_t c = 0;
    
    for (size_t i = 0; i < n; i++) {
        if (arreglo[i] < arreglo[0]) {
            menores[a] = arreglo[i];
            a++;
        } else if (arreglo[i] == arreglo[0]) {
            iguales[b] = arreglo[i];
            b++;
        } else {
            mayores[c] = arreglo[i];
            c++;
        }
    }
    return b > mitad ? true :
           a > c ? _mas_de_mitad(&menores, mitad, a) :
           c > a ? _mas_de_mitad(&mayores, mitad, c) : false;
}

bool mas_de_mitad(int* arr, size_t n) {
    return _mas_de_mitad(arr, n / 2, n);
}

// Tenemos un arreglo de tamaño 2n de la forma {C1, C2, C3, … Cn, D1, D2, D3, … Dn}, tal que la cantidad
// total de elementos del arreglo es potencia de 2 (por ende, n también lo es). Implementar un algoritmo
// de División y Conquista que modifique el arreglo de tal forma que quede con la forma 
// {C1, D1, C2, D2, C3, D3, …, Cn, Dn}, sin utilizar espacio adicional (obviando el utilizado por la
// recursividad). ¿Cual es la complejidad del algoritmo?
// Pista: Pensar primero cómo habría que hacer si el arreglo tuviera 4 elementos ({C1, C2, D1, D2}).
// Luego, pensar a partir de allí el caso de 8 elementos, etc… para encontrar el patrón.
void _alternar(int* arreglo, size_t desde, size_t hasta, size_t cuarto) {
    int aux;
    if (desde + 4 == hasta) {
        aux = arreglo[desde + 1];
        arreglo[desde + 1] = arreglo[desde + 2];
        arreglo[desde + 2] = aux;
    } else {
      size_t mitad = cuarto * 2;
      for (int i = 0; i < cuarto; i++) {
          aux = arreglo[desde + cuarto + i];
          arreglo[desde + cuarto + i] = arreglo[desde + mitad + i];
          arreglo[desde + mitad + i] = aux;
      }
      _alternar(arreglo, desde, desde + mitad, cuarto / 2);
      _alternar(arreglo, desde + mitad, hasta, cuarto / 2);
    }
}

void alternar(int* arreglo, size_t n) {
    if (n > 1) {
        _alternar (arreglo, 0, 2 * n, n / 2);
    }
} // T(n) = 2.T(n/2) + O(n/4) -> T(n) = 2.T(n/2) + O(n) -> Por el teorema maestro •{ T(n) = O(n.log(n)) }•
