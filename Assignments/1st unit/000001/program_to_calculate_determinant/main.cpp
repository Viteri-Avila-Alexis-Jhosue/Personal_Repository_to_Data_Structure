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
#include <stdio.h>
#include "SquareMatrix.h"

int main() {
    int size;
    printf("Ingrese el tamanio de la matriz cuadrada (n x n): ");
    size = SquareMatrix::validateSize();

    SquareMatrix matrix(size);
    matrix.input();

    try {
        float det = matrix.determinant();
        printf("El determinante de la matriz es: %.2f\n", det);
    } catch (const std::exception& e) {
        printf("Error al calcular el determinante: %s\n", e.what());
    }

    return 0;
}
