/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  31/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef FRACTION_H
#define FRACTION_H
    
class Fraction {
private:
    float numerator;   
    float denominator; 

public:
    Fraction(float numerator = 0.0, float denominator = 1.0); 
    static float validate();
    Fraction add(const Fraction& other);
    void print() const; 
};

#endif // FRACTION_H

