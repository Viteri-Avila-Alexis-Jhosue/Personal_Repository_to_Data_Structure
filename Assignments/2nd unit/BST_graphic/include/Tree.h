/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles binarios
Alexis Viteri
Fecha de creacion:  11/01/2025
Ultima fecha de modificacion:   11/01/2025
Estructura de Datos
NRC:  1978
*/
#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

class Tree {
private:
    Node* root;

    // Métodos auxiliares para operaciones recursivas
    void insertNode(Node*& current, int id);
    bool deleteNode(Node*& current, int id);
    Node* findMin(Node* current);
    void inOrderTraversal(Node* current) const;
    void preOrderTraversal(Node* current) const;
    void postOrderTraversal(Node* current) const;
    Node* searchNode(Node* current, int id);
    void deleteTree(Node* current);
    void printTreeP(Node* current, std::vector<std::vector<std::string>>& matrix, int col, int row, int depth) const;
    int getDepth(Node* current) const;
    int getRows(int depth) const;
    int getCols(int depth) const;

public:
    // Constructor y Destructor
    Tree();
    ~Tree();

    // Operaciones CRUD básicas
    void insert(int id);              // Insertar nodo (Create)
    bool remove(int id);              // Eliminar nodo (Delete)
    Node* search(int id);             // Buscar nodo (Read)

    // Métodos para mostrar el árbol
    void displayInOrder() const;
    void displayPreOrder() const;
    void displayPostOrder() const;
     // Método para imprimir el árbol de forma visual
    void printTree() const;

};

#endif // TREE_H
