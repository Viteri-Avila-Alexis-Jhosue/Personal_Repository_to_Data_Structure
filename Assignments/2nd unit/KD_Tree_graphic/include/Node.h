/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#ifndef NODE_H
#define NODE_H

#include <iostream>

class Node {
private:
    int x; // Coordenada X
    int y; // Coordenada Y
    Node* left;  // Hijo izquierdo
    Node* right; // Hijo derecho

public:
    // Constructor por defecto
    Node();

    // Constructor con parámetros
    Node(int xCoord, int yCoord);

    // Métodos getter
    int getX() const;
    int getY() const;
    Node* getLeft() const;
    Node* getRight() const;

    // Métodos setter
    void setX(int xCoord);
    void setY(int yCoord);
    void setLeft(Node* leftNode);
    void setRight(Node* rightNode);

    // Destructor
    ~Node();
};

#endif // NODE_H
