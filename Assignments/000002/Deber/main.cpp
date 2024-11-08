/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  07/11/2024
Ultima fecha de modificacion:   07/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include "Operacion.h"    
#include "Operacion.cpp"  

using namespace std;

int main() {
    Operacion operacion;

    char c = operacion.ingresarChar("Ingrese un caracter:");
    printf("El caracter ingresado es: %c\n", c);

    int i = operacion.ingresarInt("Ingrese un número entero:");
    printf("El número entero ingresado es: %d\n", i);

    float f = operacion.ingresarFloat("Ingrese un número flotante:");
    printf("El número flotante ingresado es: %f\n", f);

    double d = operacion.ingresarDouble("Ingrese un número double:");
    printf("El número double ingresado es: %lf\n", d);

    char s[100]; 
    operacion.ingresarString("Ingrese un texto:", s, sizeof(s));
    printf("El texto ingresado es: %s\n", s);

    return 0;
}
