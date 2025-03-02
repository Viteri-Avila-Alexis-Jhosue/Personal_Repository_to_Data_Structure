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
#include <conio.h>
#include <regex>
#include "../include/Validation.h"

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
    while (true) {
        c = getch();
        if (c == 13 && i > 0) {  // Enter key and input is not empty
            break;
        } else if (c >= '0' && c <= '9') {
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
    while (true) {
        c = getch();
        if (c == 13 && i > 0) {  // Enter key and input is not empty
            break;
        } else if (c >= '0' && c <= '9') {
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
    while (true) {
        c = getch();
        if (c == 13 && i > 0) {  // Enter key and input is not empty
            break;
        } else if (c >= '0' && c <= '9') {
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
    while (true) {
        c = getch();
        if (c == 13 && i > 0) {  // Enter key and input is not empty
            break;
        } else if (isalpha(c)) {
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
    
    while (true) {
        c = getch();
        if (c == 13 && i > 0) {  // Enter key and input is not empty
            break;
        } else if (isalpha(c) || isspace(c)) {  // Allow letters and spaces
            printf("%c", c);
            cad[i++] = c;  
            cad = (char*)realloc(cad, (i + 1) * sizeof(char));  
        } else if (c == 8) {  // Backspace key
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


string Validation::ingresarHora(const string &msj)
{
    string hora;
    char c;
    const regex pattern(R"(\d{2}:\d{2}:\d{2})"); // Formato: hh:mm:ss

    cout << msj;

    while (true)
    {
        c = _getch(); // Captura el carácter sin mostrar el eco en consola

        if (isdigit(c) && hora.length() < 8) // Dígitos (solo las ocho posiciones)
        {
            hora += c;
            cout << c; // Muestra el dígito

            // Agrega automáticamente los dos puntos después de 2 y 5 dígitos
            if (hora.length() == 2 || hora.length() == 5)
            {
                hora += ':';
                cout << ':'; // Muestra el colon
            }
        }
        else if (c == '\b' && !hora.empty()) // Retroceso para borrar
        {
            if (hora.back() == ':') // Evitar borrar los dos puntos
            {
                hora.pop_back();
                cout << "\b \b"; // Borra el dos puntos de la consola
            }
            else
            {
                hora.pop_back();
                cout << "\b \b"; // Borra el carácter de la consola
            }
        }
        else if (c == '\r') // Enter para confirmar
        {
            if (hora.length() == 8 && regex_match(hora, pattern)) // Validación final
            {
                break;
            }
            else
            {
                cout << "\nFormato inválido. Ingrese nuevamente: ";
                hora.clear();
                cout << msj;
            }
        }
        else // Cualquier otro símbolo no permitido
        {
            cout << "\a"; // Sonido de alerta para caracteres no válidos
        }
    }

    cout << endl;
    return hora;
}
