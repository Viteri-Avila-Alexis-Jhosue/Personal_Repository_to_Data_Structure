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
#include <limits>
#include <stdio.h>
#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = new float*[rows]; 
    for (int i = 0; i < rows; ++i) {
        data[i] = new float[cols]; 
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i]; 
    }
    delete[] data; 
}

float validateInput() {
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

int Matrix::validateDimension() {
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

void Matrix::input() {
    printf("Ingrese los elementos de la matriz %d x %d:\n", rows, cols);
    int count = 0; 
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("Elemento [%d][%d]: ", i, j);
            data[i][j] = validateInput();
            count++;
            printf("Avance: %d/%d, Faltantes: %d\n", count, rows * cols, (rows * cols) - count);
        }
    }
}

void Matrix::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf(" [ %.2f ] ", data[i][j]);
        }
        printf("\n");
    }
}

Matrix Matrix::add(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Las matrices deben tener las mismas dimensiones para ser sumadas.");
    }

    Matrix result(rows, cols); 
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j]; 
        }
    }
    return result;
}
