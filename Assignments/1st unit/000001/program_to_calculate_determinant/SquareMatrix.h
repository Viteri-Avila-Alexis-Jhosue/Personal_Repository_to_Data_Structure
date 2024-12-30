/*
Universidad de las Fuerzas Armadas ESPE
Programa para sumar dos fracciones
Alexis Viteri
Fecha de creacion:  03/10/2024
Ultima fecha de modificacion:   03/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

class SquareMatrix {
private:
    int size;          
    float** data;      

    float determinantRecursive(float** matrix, int n) const;  

public:
    SquareMatrix(int size);          
    ~SquareMatrix();                 

    void input();                     
    void display() const;            
    float determinant() const;        

    static float validateInput();     
    static int validateSize();        
};

#endif // SQUAREMATRIX_H
