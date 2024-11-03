/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int rows;   
    int cols;   
    float** data; 

public:
    Matrix(int rows, int cols);
    ~Matrix(); 

    void input(); 
    void display() const; 
    Matrix add(const Matrix& other) const; 
    static int validateDimension();
};

#endif // MATRIX_H
