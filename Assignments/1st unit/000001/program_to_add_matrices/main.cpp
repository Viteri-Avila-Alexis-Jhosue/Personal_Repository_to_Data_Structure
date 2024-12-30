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
#include <cstdio>
#include <stdio.h>
#include "Matrix.h"

int main() {
    int rows, cols;

    printf("Ingrese el numero de filas de la matriz: ");
    rows = Matrix::validateDimension(); 
    printf("Ingrese el numero de columnas de la matriz: ");
    cols = Matrix::validateDimension(); 

    Matrix matrix1(rows, cols);
    matrix1.input(); 

    Matrix matrix2(rows, cols);
    matrix2.input(); 

    Matrix result = matrix1.add(matrix2); 

    printf("La suma de las matrices es:\n");
    result.display(); 

    return 0;
}
