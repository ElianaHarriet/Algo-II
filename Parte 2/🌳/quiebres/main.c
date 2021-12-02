// Definimos como quiebre en un árbol binario cuando ocurre que:
// un hijo derecho tiene un solo hijo, y es el izquierdo
// un hijo izquierdo tiene un solo hijo, y es el derecho

// Implementar una primitiva para el árbol binario size_t ab_quiebres(const ab_t*)
// que, dado un árbol binario, nos devuelva la cantidad de quiebres que tiene. La
// primitiva no debe modif icar el árbol.
#include "ab.h"

size_t _ab_quiebres(const ab_t* ab, char rama) {
    if (!ab) {
        return 0;
    }
    if (rama == 'd' && ab->izq && !ab->der) {
        return 1 + _ab_quiebres(ab->izq, 'i');
    }
    if (rama == 'i' && ab->der && !ab->izq) {
        return 1 + _ab_quiebres(ab->der, 'd');
    }
    return _ab_quiebres(ab->izq, 'i') + _ab_quiebres(ab->der, 'd');
}

size_t ab_quiebres(const ab_t* ab) {
    return _ab_quiebres(ab, 'c');
}