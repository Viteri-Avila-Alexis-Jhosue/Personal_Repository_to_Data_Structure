/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  31/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <limits> 
#include "Fraction.h"

Fraction::Fraction(float numerator, float denominator) : numerator(numerator), denominator(denominator) {
    if (denominator == 0.0f) {
        printf("El denominador no puede ser cero, se aplicara denominador = 1");
        this->denominator = 1.0f;
    }
}

Fraction Fraction::add(const Fraction& other) {
    float newNumerator = numerator * other.denominator + other.numerator * denominator;
    float newDenominator = denominator * other.denominator;
    
    return Fraction(newNumerator, newDenominator);
}
float Fraction::validate() {
    float value;
    while (true) {
        printf("Ingrese un numero: ");
        if (scanf("%f", &value) == 1) {
            while (getchar() != '\n'); 
            return value;
        } else {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, ingrese un numero.\n");
        }
    }
}
void Fraction::print() const {
    printf("%f / %f ",numerator, denominator);
}
