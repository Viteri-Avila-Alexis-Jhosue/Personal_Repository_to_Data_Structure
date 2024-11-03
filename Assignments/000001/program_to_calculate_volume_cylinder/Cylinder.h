/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef CYLINDER_H
#define CYLINDER_H

class Cylinder {
private:
    float radius; 
    float height; 

public:
    Cylinder(float radius, float height);
    float calculateVolume() const;
    static float validateInput(); 
};

#endif // CYLINDER_H
