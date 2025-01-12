/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles binarios
Alexis Viteri
Fecha de creacion:  11/01/2025
Ultima fecha de modificacion:   11/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Node.h"

// Constructor
Node::Node(int id) : id(id), left(nullptr), right(nullptr) {}

// Getters
int Node::getId() const {
    return id;
}

Node*& Node::getLeft() {
    return left;
}

Node*& Node::getRight()  {
    return right;
}

// Setters
void Node::setId(int id) {
    this->id = id;
}

void Node::setLeft(Node* left) {
    this->left = left;
}

void Node::setRight(Node* right) {
    this->right = right;
}
