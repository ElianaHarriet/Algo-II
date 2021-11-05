// Implementar el TDA Fracción. Dicho TDA debe tener las siguientes primitivas,
// cuya documentación puede encontrarse en fraccion.h:
// fraccion_t* fraccion_crear(int numerador, int denominador);
// fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2);
// fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2);
// char* fraccion_representacion(fraccion_t* fraccion);
// int fraccion_parte_entera(fraccion_t* fraccion);
// void fraccion_destruir(fraccion_t* fraccion);
// Nota: considerar que se puede utilizar la función sprintf para generar la
// representación de la fracción. Por ejemplo: sprintf(buffer, "%d/%d", num1, num2).
#include <stdlib.h>
#include <stdio.h> // sprintf
#include "fraccion.h"

typedef struct fraccion {
    int numerador;
    int denominador;
} fraccion_t;

// ༺ Auxiliares ༻ //

int _max(int num1, int num2) {
    return num1 > num2 ? num1 : num2;
}

int _min(int num1, int num2) {
    return num1 < num2 ? num1 : num2;
}

int _maximo_comun_divisor(int num1, int num2) {
    int mcd = 0;
    int a = _max(num1, num2);
    int b = _min(num1, num2);
    do {
        mcd = b;
        b = a % b;
        a = mcd;
    } while(b != 0);
    return mcd;
}

fraccion_t* _simplificar(fraccion_t* fraccion) {
    int mcd = _maximo_comun_divisor(fraccion->numerador, fraccion->denominador);
    int num = fraccion->numerador / mcd;
    int den = fraccion->denominador / mcd;
    fraccion_destruir(fraccion);
    fraccion_t* simplificada;
    do {
        simplificada = fraccion_crear(num, den);
    } while (simplificada == NULL);
    return simplificada;
}

// ༺༻ //

fraccion_t* fraccion_crear(int numerador, int denominador) {
    fraccion_t* fraccion = malloc(sizeof(fraccion_t));

    if (fraccion == NULL || denominador == 0) {
        return NULL;
    }
    fraccion->numerador = numerador;
    fraccion->denominador = denominador;
    return fraccion;
}

void fraccion_destruir(fraccion_t* fraccion) {
    free(fraccion);
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {
    int denominador = f1->denominador * f2->denominador;
    int numerador = (denominador / f1->denominador) * f1->numerador +
                    (denominador / f2->denominador) * f2->numerador;
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    fraccion_t* fraccion;
    do {
        fraccion = fraccion_crear(numerador, denominador);
    } while (fraccion == NULL);
    return fraccion;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
    int denominador = f1->denominador * f2->denominador;
    int numerador = f1->numerador * f2->numerador;
    fraccion_destruir(f1);
    fraccion_destruir(f2);
    fraccion_t* fraccion;
    do {
        fraccion = fraccion_crear(numerador, denominador);
    } while (fraccion == NULL);
    return fraccion;
}

int fraccion_parte_entera(fraccion_t* fraccion) {
    return fraccion->numerador / fraccion->denominador;
}

char* fraccion_representacion(fraccion_t* fraccion) {
    fraccion_t* simplificada = _simplificar(fraccion);
    char* cadena = malloc(sizeof(char) * 15);
    if (simplificada->denominador == 1) {
        sprintf(cadena, "%i", simplificada->numerador);
    } else {
        sprintf(cadena, "%i/%i", simplificada->numerador, simplificada->denominador);
    }
    return cadena;
}
