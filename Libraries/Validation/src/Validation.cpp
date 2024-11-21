/*
Universidad de las Fuerzas Armadas ESPE
Libreria para la validacion del ingreso de datos
Alexis Viteri
Fecha de creacion:  20/11/2024
Ultima fecha de modificacion:   20/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib> 
#include "Validation.h"

using namespace std;

char Validation::ingresarChar(const char* msj) {
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

int Validation::ingresarInt(const char* msj) {
    char* cad = new char[1]; 
    char c;
    int i = 0;
    int valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13) {  
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char)); 
        } else if (c == 8) {  
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    valor = atoi(cad);  
    delete[] cad;  
    return valor;
}

float Validation::ingresarFloat(const char* msj) {
    char* cad = new char[1];  
    char c;
    int i = 0;
    float valor = 0;
    printf("%s", msj);
    while((c = getch()) != 13) {  
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        } else if (c == 8) {  
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == 46) {  
            bool aux = false;
            for (int j = 0; cad[j] != '\0'; j++) {
                if (cad[j] == 46) {
                    aux = true;
                    break;
                }
            }
            if(aux == false) {
                printf("%c", c);
                cad[i++] = c;
                cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
            }
        }
    }
    cad[i++] = '\0';
    valor = atof(cad);  
    delete[] cad;  
    return valor;
}

double Validation::ingresarDouble(const char* msj) {
    char* cad = new char[1];  
    char c;
    int i = 0;
    double valor = 0;
    bool puntoDecimal = false;
    printf("%s", msj);
    while((c = getch()) != 13) {  
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        } else if (c == 8) {  
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (c == '.' && !puntoDecimal) {
            puntoDecimal = true;
            printf("%c", c);
            cad[i++] = c;
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        }
    }
    cad[i] = '\0';
    valor = atof(cad);  
    delete[] cad;  
    return valor;
}

string Validation::ingresarString(const char *msj) {
    char* cad = new char[1];  
    char c;
    int i = 0;
    string cadena1;
    printf("%s", msj);
    while ((c = getch()) != 13) {  
        if (isalpha(c)) {
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        } else if (c == 8) {  
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    cad[i] = '\0';
    cadena1 = cad;  
    delete[] cad;  
    return cadena1;
}

string Validation::ingresarStringConEspacios(const char* msj) {
    char* cad = new char[1]; 
    char c;
    int i = 0;
    string cadena1;
    printf("%s", msj);
    
    while ((c = getch()) != 13) {  // 13 es el código de enter
        if (isalpha(c) || isspace(c)) {  // Permitir letras y espacios
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        } else if (c == 8) {  // 8 es el código para la tecla backspace
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        }
    }
    
    cad[i] = '\0';  
    cadena1 = cad;  
    delete[] cad;  
    return cadena1;  
}
