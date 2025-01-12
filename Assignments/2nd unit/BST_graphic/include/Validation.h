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

using namespace std;

class Validation {
public:
    char ingresarChar(const char* msj);
    int ingresarInt(const char* msj);
    float ingresarFloat(const char* msj);
    double ingresarDouble(const char* msj);
    string ingresarString(const char* msj);
    string ingresarStringConEspacios(const char* msj);
};

#endif
