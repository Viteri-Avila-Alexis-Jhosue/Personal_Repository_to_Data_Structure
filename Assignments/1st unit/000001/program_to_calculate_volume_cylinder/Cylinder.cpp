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
#include <cmath>
#include "Cylinder.h"

Cylinder::Cylinder(float r, float h) : radius(r), height(h) {}

float Cylinder::calculateVolume() const {
    return M_PI * radius * radius * height; 
}

float Cylinder::validateInput() {
    float value;
    while (true) {
        if (scanf("%f", &value) == 1 && value > 0) {
            while (getchar() != '\n'); 
            return value;
        } else {
            while (getchar() != '\n'); 
            printf("Entrada invalida, ingrese un numero positivo  ");
        }
    }
}
