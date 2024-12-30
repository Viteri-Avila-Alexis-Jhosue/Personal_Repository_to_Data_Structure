/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  07/11/2024
Ultima fecha de modificacion:   07/11/2024
Estructura de Datos
NRC:  1978
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cctype> 
#include <cstring>  
#include "Operacion.h"

using namespace std;

char Operacion::ingresarChar(char* msj) {
    char c;
    printf("%s\n", msj);
    while (true) {
        c = getch();  
        if (isalpha(c)) {  
            printf("%c\n", c);  
            return c;
        }
    }
}

int Operacion::ingresarInt(char* msj) {
    char cad[10];
    char c;
    int i = 0;
    int valor;

    printf("%s\n", msj);
    while ((c = getch()) != '\r') {  
        if (c >= '0' && c <= '9') {  
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0';  
    valor = atoi(cad);  
    printf("\n");
    return valor;
}

float Operacion::ingresarFloat(char* msj) {
    char cad[20];
    char c;
    int i = 0;
    float valor;

    printf("%s\n", msj);
    while ((c = getch()) != '\r') {  
        if ((c >= '0' && c <= '9') || c == '.') {  
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0'; 
    valor = atof(cad);  
    printf("\n");
    return valor;
}

double Operacion::ingresarDouble(char* msj) {
    char cad[20];
    char c;
    int i = 0;
    double valor;

    printf("%s\n", msj);
    while ((c = getch()) != '\r') {  
        if ((c >= '0' && c <= '9') || c == '.') {  
            printf("%c", c);
            cad[i++] = c;
        }
    }
    cad[i] = '\0';  
    valor = atof(cad); 
    printf("\n");
    return valor;
}

void Operacion::ingresarString(char* msj, char* cadena, int maxLength) {
    char c;
    int i = 0;

    printf("%s\n", msj);
    while ((c = getch()) != '\r' && i < maxLength - 1) {  
        if (c != 8) {  
            printf("%c", c);  
            cadena[i++] = c;  
        }
    }
    cadena[i] = '\0';  
    printf("\n");
}
