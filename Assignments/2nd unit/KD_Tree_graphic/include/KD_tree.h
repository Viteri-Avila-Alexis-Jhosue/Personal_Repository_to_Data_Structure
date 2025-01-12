/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#ifndef KD_TREE_H
#define KD_TREE_H

#include "Node.h"
#include <vector>

class KD_tree {
private:
    Node* root; // Nodo raíz
    int dimension; // Dimensión del árbol (2 en este caso)

    // Métodos privados para operaciones recursivas
    Node* insert(Node* current, Node* newNode, int depth);
    Node* remove(Node* current, const int x, const int y, int depth, bool* nodeDeleted);
    Node* findMin(Node* current, int depth, int dim);
    void printInOrder(Node* current) const;
    void printPreOrder(Node* current) const;
    void printPostOrder(Node* current) const;
    void printTreeP(Node* current, std::vector<std::vector<std::string>>& matrix, int col, int row, int depth) const;
    int getDepth(Node* current) const;
    int getRows(int depth) const;
    int getCols(int depth) const;

public:
    // Constructor
    KD_tree();

    // Destructor
    ~KD_tree();

    // Métodos públicos
    void insert(int x, int y);
    void remove(int x, int y);
    Node* getRoot() const;
    void setRoot(Node* rootNode);
    void printInOrder() const;
    void printPreOrder() const;
    void printPostOrder() const;

    // Limpieza del árbol
    void clear(Node* current);
    void printTree() const;
};

#endif // KD_tree_H
