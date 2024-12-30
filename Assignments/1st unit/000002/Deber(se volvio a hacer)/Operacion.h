/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  07/11/2024
Ultima fecha de modificacion:   10/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef OPERACION_H
#define OPERACION_H
# include <string>
# include <cstring>  
using namespace std;
class Operacion {
public:
    char ingresarChar(const char* msj);
    int ingresarInt(const char* msj);
    float ingresarFloat(const char* msj);
    double ingresarDouble(const char* msj);
    string ingresarString(const char* msj);
    void sumarEnteros(int valor1, int valor2);
    void sumarFlotantes(float valor1, float valor2);
};

#endif
