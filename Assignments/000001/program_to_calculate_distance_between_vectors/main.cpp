/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include "Vector.h"

int main() {
    int dimensions = Vector::validateDimension(); 
    Vector vector1(dimensions);
    vector1.input(); 
    printf("Vector 1: ");
    vector1.print(); 

    Vector vector2(dimensions);
    vector2.input(); 
    printf("Vector 2: ");
    vector2.print(); 

    float distance = vector1.distance(vector2);
  
    printf("La distancia entre los dos vectores es: %.2f\n", distance);

    return 0;
}
