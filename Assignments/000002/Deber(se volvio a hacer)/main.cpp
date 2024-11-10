/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  07/11/2024
Ultima fecha de modificacion:   10/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>   
#include "Operacion.h"  

using namespace std;

int main() {
    Operacion operacion;
    string s = operacion.ingresarString("Ingrese su nombre:");
    printf("Hola : %s\n", s.c_str());
    char c = operacion.ingresarChar("Ingrese un caracter:");
    printf("El caracter ingresado es: %c\n", c);

    int i = operacion.ingresarInt("Ingrese el primer numero entero:");
    printf("El numero entero ingresado es: %d\n", i);
    int i2 = operacion.ingresarInt("Ingrese el otro numero entero:");
    printf("El numero entero ingresado es: %d\n", i2);
    operacion.sumarEnteros(i,i2);

    float f = operacion.ingresarFloat("\nIngrese el primer numero flotante:");
    printf("El numero flotante ingresado es: %f\n", f);
    float f2 = operacion.ingresarFloat("Ingrese otro numero flotante:");
    printf("El numero flotante ingresado es: %f\n", f2);
    operacion.sumarFlotantes(f,f2);

    double d = operacion.ingresarDouble("\nIngrese un numero double:");
    printf("El numero double ingresado es: %lf\n", d);

    return 0;
}