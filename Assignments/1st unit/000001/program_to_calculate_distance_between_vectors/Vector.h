/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef VECTOR_H
#define VECTOR_H

class Vector {
private:
    int dimensions;
    float* components; 

public:
    Vector(int dimensions);
    ~Vector();
    static int validateDimension();
    void input();
    float distance(const Vector& other) const;
    void print() const; 

private:
    float validateInput(); 
};

#endif // VECTOR_H
