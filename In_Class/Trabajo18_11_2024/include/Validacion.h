/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  17/11/2024
Ultima fecha de modificacion:   17/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
#include <cstring>

#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)  
    #else
        #define DLL_EXPORT __declspec(dllimport) 
    #endif
#else
    #define DLL_EXPORT
#endif

using namespace std;

class DLL_EXPORT Validacion {
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
