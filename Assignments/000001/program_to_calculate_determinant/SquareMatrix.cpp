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
#include <stdexcept>
#include "SquareMatrix.h"

SquareMatrix::SquareMatrix(int size) : size(size) {
    data = new float*[size];
    for (int i = 0; i < size; ++i) {
        data[i] = new float[size];
    }
}

SquareMatrix::~SquareMatrix() {
    for (int i = 0; i < size; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

float SquareMatrix::validateInput() {
    float value;
    while (true) {
        if (scanf("%f", &value) == 1) {
            while (getchar() != '\n'); 
            return value;
        } else {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, ingrese un numero: ");
        }
    }
}

int SquareMatrix::validateSize() {
    int value;
    while (true) {
        if (scanf("%d", &value) == 1 && value > 0) {
            while (getchar() != '\n');
            return value;
        } else {
            while (getchar() != '\n');
            printf("Entrada invalida. Por favor, ingrese un numero entero positivo: ");
        }
    }
}

void SquareMatrix::input() {
    printf("Ingrese los elementos de la matriz %d x %d:\n", size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("Elemento [%d][%d]: ", i, j);
            data[i][j] = validateInput();
        }
    }
    printf("Matriz ingresada:\n");
    display();
}

void SquareMatrix::display() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("[%.2f] ", data[i][j]);
        }
        printf("\n");
    }
}

float SquareMatrix::determinantRecursive(float** matrix, int n) const {
    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    float det = 0;
    for (int col = 0; col < n; ++col) {
        float** subMatrix = new float*[n - 1];
        for (int i = 0; i < n - 1; ++i) {
            subMatrix[i] = new float[n - 1];
        }

        for (int i = 1; i < n; ++i) {
            int sub_j = 0;
            for (int j = 0; j < n; ++j) {
                if (j == col) continue;
                subMatrix[i - 1][sub_j] = matrix[i][j];
                sub_j++;
            }
        }

        float cofactor = (col % 2 == 0 ? 1 : -1) * matrix[0][col];
        det += cofactor * determinantRecursive(subMatrix, n - 1);

        for (int i = 0; i < n - 1; ++i) {
            delete[] subMatrix[i];
        }
        delete[] subMatrix;
    }
    return det;
}

float SquareMatrix::determinant() const {
    return determinantRecursive(data, size);
}
