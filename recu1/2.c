// 2. Dado un array ordenado de 0s y 1s, implementar una función por división y conquista que permita
// determinar la cantidad de 1s. Justificar el orden del algoritmo. Ejemplos:
// [0,0,0,0,1] -> 1
// [0,0,1,1,1] -> 3
// [0,0,0,0,0] -> 0
#include <stdlib.h>
#include <stdio.h>

int _cant_uno(int arreglo[], size_t desde, size_t hasta, size_t len) {
	if (desde == hasta) {
		return (int)len - (int)desde;
	}

	size_t medio = (desde + hasta) / 2;
	if (arreglo[medio] == 0) {
		return _cant_uno(arreglo, medio + 1, hasta, len);
	} else {
		return _cant_uno(arreglo, desde, medio, len);
	}	
}

int cant_uno(int arreglo[], size_t n) {
	if (arreglo[n - 1] == 0) {
		return 0;
	}
	return _cant_uno(arreglo, 0, n, n);
}

int main() {
	int arr1[] = {0, 0, 0, 0, 1};
	int arr2[] = {0, 0, 1, 1, 1};
	int arr3[] = {0, 0, 0, 0, 0};
	int arr4[] = {1, 1, 1, 1, 1};
	printf("arr1 -> %d\n", cant_uno(arr1, 5));
	printf("arr2 -> %d\n", cant_uno(arr2, 5));
	printf("arr3 -> %d\n", cant_uno(arr3, 5));
	printf("arr4 -> %d\n", cant_uno(arr4, 5));
}

/****************************************************************************\ 
							•{Orden del algoritmo}•
				(Para un k, siendo k el largo del arreglo)
Llamadas recursivas -> 1 (Figuran 3, pero sólo se accede a 1)
El arreglo se parte a la mitad en cada llamada recursiva
Todo lo que no es llamada recursiva -> O(1)
T(k) = T(k/2) + O(1)
Po rel teorema maestro: A = 1, B = 2, C = 0
log_{B}(A) = 0 = C -> T(k) = O(k^C log(k))
=> T(k) = O(log(k))
\****************************************************************************/