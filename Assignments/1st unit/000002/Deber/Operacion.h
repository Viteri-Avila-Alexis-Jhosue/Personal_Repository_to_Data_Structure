/*
Universidad de las Fuerzas Armadas ESPE
Programa Para ingresar un solo tipo de dato
Alexis Viteri
Fecha de creacion:  07/11/2024
Ultima fecha de modificacion:   07/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef OPERACION_H
#define OPERACION_H

class Operacion {
public:
    char ingresarChar(char* msj);
    int ingresarInt(char* msj);
    float ingresarFloat(char* msj);
    double ingresarDouble(char* msj);
    void ingresarString(char* msj, char* cadena, int maxLength);
};

#endif
