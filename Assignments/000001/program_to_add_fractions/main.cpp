/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/11/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <limits> 
#include "Fraction.h"

int main() {
    float num1, den1, num2, den2; 

    printf("Ingrese la primera fraccion (numerador): \t");
    num1 =  Fraction::validate();
    printf("Ingrese la primera fraccion (denominador): \t");
    den1= Fraction::validate();
    Fraction frac1(num1, den1);

    printf("\nIngrese la segunda fraccion (numerador): \t");
    num2 =  Fraction::validate();
    printf("Ingrese la segunda fraccion (denominador): \t");
    den2 =  Fraction::validate();
    Fraction frac2(num2, den2);

    Fraction result = frac1.add(frac2);

    printf("\nLa suma de las fracciones es: ");
    result.print();

    return 0;
}
