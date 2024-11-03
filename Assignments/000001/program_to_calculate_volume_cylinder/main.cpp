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
#include "Cylinder.h"

int main() {
    float radius, height;

    printf("Ingrese el radio del cilindro:   ");
    radius = Cylinder::validateInput();

    printf("Ingrese la altura del cilindro:   ");
    height = Cylinder::validateInput();
    Cylinder cylinder(radius, height);

    float volume = cylinder.calculateVolume();
    printf("El volumen del cilindro es:  %.2f\n", volume);

    return 0;
}
