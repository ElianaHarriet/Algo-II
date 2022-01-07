// 2. Una agencia de superheroes está buscando armar el mejor equipo de superhéroes del mundo, llamado los Assemblers. Quieren
// quedarse con los mejores 100 superhéroes del mundo (lo cuál está definido por una función de comparación). Implementar en
// C una función que reciba una lista con todos los superhéroes del mundo (supongamos, punteros a heroe_t), una cantidad
// k y una función de comparación, y nos devuelva los mejores k héroes. El orden del algoritmo debe ser O(n + k log n),
// siendo n la cantidad de héroes en total y k la cantidad de héroes que se quieren reclutar. Justificar el orden del algoritmo
// implementado.
#include "lista.h"
#include "heap.h"

lista_t* assemblers(lista_t* heroes, size_t k, cmp_func_t cmp) {
	if (k >= lista_largo(heroes)) return heroes;					// O(1)
	// Asumo que no se quiere un orden particular en la lista que se devuelve

	heroes_t* arr[k]; 												// O(1)
	lista_iter_t* iter = lista_iter_crear(heroes); 					// O(1)
	size_t i = 0; 													// O(1)
	while (!lista_iter_al_final(iter)) { 							// N veces O(1) -> O(N)
		arr[i] = lista_iter_ver_actual(iter); 						// O(1)
		lista_iter_avanzar(iter); 									// O(1)
		i++; 														// O(1)
	}
	heap_t* heap = heap_crear_arr(arr, lista_largo(heroes), cmp); 	// O(N) (Ya que usa heapify el cual es O(N))

	/* Heap de máximos, asumo que la cmp me devuelve si el primero
	 * es mayor (mejor) que el segundo. Por lo tanto, en el tope del
	 * heap estará siempre el mayor (mejor) héroe del heap.
	 */

	lista_t* definitivos = lista_crear(); 							// O(1)
	if (!definitivos) {
		heap_destruir(heap, NULL); 									// O(1)
		lista_iter_destruir(iter); 									// O(1)
		return NULL; 												// O(1)
	}

	for (i = 0; i < k; i++) { 										// K veces O(log N) -> O(K log N)
		heroes_t* heroe = heap_desencolar(heap); 					// O(log N)
		// Asumo que es un heap de heroes_t* en lugar de void*
		
		lista_insertar_ultimo(definitivos, heroe); 					// O(1)
	}
	heap_destruir(heap, NULL); 										// O(1)
	lista_iter_destruir(iter); 										// O(1)
	return definitivos;
}

// Orden del algoritmo: O(N) * 2 + O(K log N) -> O(N + K log N) ✓
