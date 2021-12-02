/*
Dado un arreglo de enteros y un número K, se desearía que todos los elementos del arreglo sean menores o iguales a K.
Aquellos números que sean mayores a K deberían combinarse de la siguiente forma: buscar los dos números más grandes del
vector, sacarlos y generar uno nuevo de la forma “Nuevo número = 2 x segundo-más-grande - número-más-grande”. Por
ejemplo, si K = 10 y los números más grandes del arreglo son 15 y 12: 2 * 12 - 15 = 9. Los números combinados pueden
volver a ser combinados con otros en caso de ser necesario (en el ejemplo no lo es), aplicando la misma lógica hasta que el
número resultante sea menor o igual a K.
Implementar una función que reciba un arreglo de enteros, su largo y un número K, y devuelva la cantidad de combinaciones
que deberían ser necesarias para que el arreglo tenga todos los números menores o iguales a K como se indica. El arreglo
original debe quedar en el estado original. En caso de no poderse combinar todos los elementos para que todos los elementos
sean menores o iguales a K, devolver -1. Determinar y justificar la complejidad del algoritmo implementado. Aclaración: la
función sólo debe devolver cuántas combinaciones se deberían hacer, no debe devolver cómo quedarían los elementos al final.
Ejemplo: Entrada: [11, 14, 8, 19, 42, 12, 5, 1, 9]; K = 9:
[11, 14, 8, 19, 42, 12, 5, 1, 9] - (19, 42) -> 2 * 19 - 42 = -4
[11, 14, 8, 12, 5, 1, 9, -4] - (12, 14) -> 2 * 12 - 14 = 10
[11, 8, 5, 1, 9, -4, 10] - (10, 11) -> 10 * 2 - 11 = 9
[8, 5, 1, 9, -4, 9]
Notar que si K = 8, no se podría resolver el problema (debemos devolver -1). Esto es porque los dos 9s se combinarían para
formar un nuevo 9, que luego no se podría combinar con otro número.
*/

int mayor(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int combinaciones(int *arreglo, int largo, int k) {
    heap_t *heap = heap_crear_arr((void*)arreglo, largo, mayor); // -> O(N)
    int i = 0;
    while (*(int*)heap_ver_max(heap) > k) { // -> ver_max -> O(1)
        int a = *(int*)heap_desencolar(heap); // -> O(log N)
        int b = *(int*)heap_desencolar(heap); // -> O(log N)
        int nuevo = (2 * b) - a;
        heap_encolar(heap, &nuevo); // -> O(log N)
        i++;
        if (b <= k) { // Si b <= k, a no se puede combinar con otro número
            heap_destruir(heap, NULL);
            return -1;
        }
    }
    heap_destruir(heap, NULL);
    return i;
}

/*
 * -> {Orden del algoritmo} <-
 * (siendo N la cantidad de elementos del arreglo)
 * O(N log(N)) => Debido a que el heap_crear_arr es O(N) (se hace una única vez), el heap_desencolar es O(log N) (se hace x veces)
 * y el heap_encolar es O(log N) (se hace x veces). Puedo asumiendo que el heap_destruir es O(1) ya que no debe destruir datos (la
 * función de destrucción es null), pero en el caso en que no fuera O(1) y fuera O(N) no cambia mucho ya que se hace una única vez
 * y en comparación con el ciclo no modifica el orden.
 * El ciclo repite operaciones O(log N) por cada iteración, se itera x veces. Ese x tiende a aumentar a medida que el largo es mayor,
 * por lo que el algoritmo resulta en O(N log(N))
 */