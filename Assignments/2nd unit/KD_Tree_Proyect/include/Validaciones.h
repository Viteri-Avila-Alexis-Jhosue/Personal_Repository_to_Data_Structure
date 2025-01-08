#ifndef VALIDACIONES_H
#define VALIDACIONES_H
#include <iostream>

using namespace std;

class Validaciones
{
public:
    
    string ingresarString(const string &msj);
    bool validarCedula(const string &cedula);
    bool validarCorreo(const string &correo);
    string ingresarCedula(const string &msj);
    string ingresarCorreo(const string &msj);
    string ingresarPlaca(const string &msj);
    string ingresarFecha(const string &msj);
    string ingresarHora(const string &msj);
};
#endif // VALIDACIONES_H
