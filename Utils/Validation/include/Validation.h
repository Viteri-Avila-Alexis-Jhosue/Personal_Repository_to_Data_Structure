/*
Universidad de las Fuerzas Armadas ESPE
Libreria para la validacion del ingreso de datos
Alexis Viteri
Fecha de creacion:  20/11/2024
Ultima fecha de modificacion:   20/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef VALIDATION_H
#define VALIDATION_H

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

class DLL_EXPORT Validation {
public:
    char ingresarChar(const char* msj);
    int ingresarInt(const char* msj);
    float ingresarFloat(const char* msj);
    double ingresarDouble(const char* msj);
    string ingresarString(const char* msj);
    string ingresarStringConEspacios(const char* msj);
};

#endif
