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
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib> 
#include "Operacion.h"

using namespace std;

char Operacion::ingresarChar(const char* msj) {
    char c;
    printf("%s", msj);
    while (true) {
        c = getch();
        if (isalpha(c)) {
            printf("%c", c);
            return c;
        } else if (c == 8) {
            printf("\b \b");
        }
    }
}

int Operacion::ingresarInt(const char* msj) {
    char cad[10];
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i++] = '\0';
    valor = atoi(cad);
    return valor;
}

void Operacion::sumarEnteros(int valor1, int valor2){
    int resultado = valor1+valor2;
    printf("El resultado es %d", resultado);

}
void Operacion::sumarFlotantes(float valor1, float valor2){
    float resultado = valor1+valor2;
    printf("La respuessta es %f", resultado);
}

float Operacion::ingresarFloat(const char* msj) {
    char cad[10];
    char c;
    int i = 0;
    float valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == 46) {
            bool aux = false;
            for (int j = 0; cad[j] != '\0'; j++) {
                if (cad[j] == 46){
                    aux = true;
                    break;
                }
            }
            if(aux == false){
                printf("%c", c);
                cad[i++] = c;
            }
        }
    }
    cad[i++] = '\0';
    for (int j = 0; cad[j] != '\0'; j++) {
        valor = atof(cad);
    }
    return valor;
}

double Operacion::ingresarDouble(const char* msj) {
    char cad[20];
    char c;
    int i = 0;
    double valor = 0;
    printf("%s", msj);
    bool puntoDecimal = false;
    while((c = getch()) != 13){
        if (c >= '0' && c <= '9'){
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == '.' && !puntoDecimal) {
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0';
    valor = atof(cad);
    return valor;
}

string Operacion::ingresarString(const char *msj) {
    char cad[10];
    char c;
    int i = 0;
    string cadena1;
    printf("%s", msj);
    while ((c = getch()) != 13) {
        if (isalpha(c)) {
            printf("%c", c);
            cad[i++] = c;
        } else if (c == 8) {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    cadena1 = cad;  // Aquí se debería asignar la cadena correcta
    return cadena1;
}
