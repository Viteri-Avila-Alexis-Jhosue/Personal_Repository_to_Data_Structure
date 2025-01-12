/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Node.h"

// Constructor por defecto
Node::Node() : x(0.0), y(0.0), left(nullptr), right(nullptr) {}

// Constructor con parámetros
Node::Node(int xCoord, int yCoord) : x(xCoord), y(yCoord), left(nullptr), right(nullptr) {}

// Métodos getter
int Node::getX() const {
    return x;
}

int Node::getY() const {
    return y;
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}

// Métodos setter
void Node::setX(int xCoord) {
    x = xCoord;
}

void Node::setY(int yCoord) {
    y = yCoord;
}

void Node::setLeft(Node* leftNode) {
    left = leftNode;
}

void Node::setRight(Node* rightNode) {
    right = rightNode;
}

// Destructor
Node::~Node() {
    // Punteros left y right no se eliminan aquí porque pueden ser administrados externamente
}
