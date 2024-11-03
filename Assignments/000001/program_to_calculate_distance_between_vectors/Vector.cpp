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
#include <cmath>
#include <cstdio>
#include "Vector.h"

Vector::Vector(int dimensions) : dimensions(dimensions) {
    components = new float[dimensions];
}

Vector::~Vector() {
    delete[] components;
}

float Vector::validateInput() {
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

int Vector::validateDimension() {
    int value;
    while (true) {
        printf("Ingrese el número de dimensiones del vector: ");
        if (scanf("%d", &value) == 1 && value > 0) {
            while (getchar() != '\n'); 
            return value;
        } else {
            while (getchar() != '\n'); 
            printf("Entrada invalida. Por favor, ingrese un numero entero positivo.\n");
        }
    }
}

void Vector::input() {
    printf("Ingrese los componentes del vector (dimensiones: %d):\n", dimensions);
    for (int i = 0; i < dimensions; ++i) {
        printf("Componente [%d]: ", i);
        components[i] = validateInput(); 
    }
}

void Vector::print() const {
    printf("(");
    for (int i = 0; i < dimensions; ++i) {
        printf("%.2f", components[i]);
        if (i < dimensions - 1) {
            printf(", "); 
        }
    }
    printf(")\n"); 
}

float Vector::distance(const Vector& other) const {
    if (dimensions != other.dimensions) {
        throw std::invalid_argument("Los vectores deben tener la misma cantidad de dimensiones.");
    }
    
    float sum = 0.0f;
    for (int i = 0; i < dimensions; ++i) {
        float diff = components[i] - other.components[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}
