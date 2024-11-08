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

    int i = operacion.ingresarInt("Ingrese un numero entero:");
    printf("El numero entero ingresado es: %d\n", i);

    float f = operacion.ingresarFloat("Ingrese un numero flotante:");
    printf("El numero flotante ingresado es: %f\n", f);

    double d = operacion.ingresarDouble("Ingrese un numero double:");
    printf("El numero double ingresado es: %lf\n", d);

    char s[100]; 
    operacion.ingresarString("Ingrese un texto:", s, sizeof(s));
    printf("El texto ingresado es: %s\n", s);

    return 0;
}
