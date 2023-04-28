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
    
    size_t izq = _ab_quiebres(ab->izq, 'i');
    size_t der = _ab_quiebres(ab->der, 'd');
    size_t quiebre = (rama == 'd' && ab->izq && !ab->der) || (rama == 'i' && ab->der && !ab->izq) ? 1 : 0;

    return izq + der + quiebre;
}

size_t ab_quiebres(const ab_t* ab) {
    return _ab_quiebres(ab, 'c');
}
