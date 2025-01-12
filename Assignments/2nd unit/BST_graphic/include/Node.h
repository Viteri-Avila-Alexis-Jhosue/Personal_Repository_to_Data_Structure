/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles binarios
Alexis Viteri
Fecha de creacion:  11/01/2025
Ultima fecha de modificacion:   11/01/2025
Estructura de Datos
NRC:  1978
*/
#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    int id;
    Node* left;
    Node* right;

public:
    // Constructor
    Node(int id);

    // Getters
    int getId() const;
    Node*& getLeft();
    Node*& getRight();

    // Setters
    void setId(int id);
    void setLeft(Node* left);
    void setRight(Node* right);
};
#endif // NODE_H
