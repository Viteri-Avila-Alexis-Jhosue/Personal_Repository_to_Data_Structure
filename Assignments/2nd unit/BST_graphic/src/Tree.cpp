/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles binarios
Alexis Viteri
Fecha de creacion:  11/01/2025
Ultima fecha de modificacion:   11/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Tree.h"
#include "../include/Node.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// Constructor
Tree::Tree() : root(nullptr) {}

// Destructor
Tree::~Tree() {
    deleteTree(root);
}

// Método auxiliar para liberar memoria
void Tree::deleteTree(Node* current) {
    if (current != nullptr) {
        deleteTree(current->getLeft());
        deleteTree(current->getRight());
        delete current;
    }
}

// Insertar nodo (público)
void Tree::insert(int id) {
    insertNode(root, id);
}

// Método auxiliar recursivo para insertar un nodo
void Tree::insertNode(Node*& current, int id) {
    if (current == nullptr) {
        current = new Node(id);
        cout << "\nNodo insertado correctamente.\n";
    } else if (id < current->getId()) {
        insertNode(current->getLeft(), id);
    } else if (id >= current->getId()) {
        insertNode(current->getRight(), id);
    } else {
        cout << "Error\n";
    }
}

// Buscar nodo (público)
Node* Tree::search(int id) {
    return searchNode(root, id);
}

// Método auxiliar recursivo para buscar un nodo
Node* Tree::searchNode(Node* current, int id) {
    if (current == nullptr || current->getId() == id) {
        return current;
    }
    if (id < current->getId()) {
        return searchNode(current->getLeft(), id);
    } else {
        return searchNode(current->getRight(), id);
    }
}

// Eliminar nodo (público)
bool Tree::remove(int id) {
    return deleteNode(root, id);
}

// Método auxiliar recursivo para eliminar un nodo
bool Tree::deleteNode(Node*& current, int id) {
    if (current == nullptr) {
        return false;
    }

    if (id < current->getId()) {
        return deleteNode(current->getLeft(), id);  // Corrección aquí también
    } else if (id > current->getId()) {
        return deleteNode(current->getRight(), id); // Corrección aquí también
    } else { 
        // Nodo encontrado
        if (current->getLeft() == nullptr && current->getRight() == nullptr) {
            delete current;
            current = nullptr;
        } else if (current->getLeft() == nullptr) {
            Node* temp = current;
            current = current->getRight();
            delete temp;
        } else if (current->getRight() == nullptr) {
            Node* temp = current;
            current = current->getLeft();
            delete temp;
        } else {
            Node* temp = findMin(current->getRight());
            current->setId(temp->getId());
            deleteNode(current->getRight(), temp->getId());
        }
        return true;
    }
}


// Método auxiliar para encontrar el nodo con el valor mínimo
Node* Tree::findMin(Node* current) {
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}

// Recorridos públicos
void Tree::displayInOrder() const {
    inOrderTraversal(root);
    cout << endl;
}

void Tree::displayPreOrder() const {
    preOrderTraversal(root);
    cout << endl;
}

void Tree::displayPostOrder() const {
    postOrderTraversal(root);
    cout << endl;
}

// Métodos auxiliares para los recorridos
void Tree::inOrderTraversal(Node* current) const {
    if (current != nullptr) {
        inOrderTraversal(current->getLeft());
        cout << current->getId() << " ";
        inOrderTraversal(current->getRight());
    }
}

void Tree::preOrderTraversal(Node* current) const {
    if (current != nullptr) {
        cout << current->getId() << " ";
        preOrderTraversal(current->getLeft());
        preOrderTraversal(current->getRight());
    }
}

void Tree::postOrderTraversal(Node* current) const {
    if (current != nullptr) {
        postOrderTraversal(current->getLeft());
        postOrderTraversal(current->getRight());
        cout << current->getId() << " ";
    }
}
//----------------------------------------------------------------------------------------------------------------
int Tree::getDepth(Node* current) const {
    if (current == nullptr) {
        return 0;
    }
    int leftDepth = getDepth(current->getLeft());
    int rightDepth = getDepth(current->getRight());
    return std::max(leftDepth, rightDepth) + 1;
}

void Tree::printTree() const {
    if (root == nullptr) {  
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    int depth = getDepth(root); 
    int rows = depth * 2 +1;
    int cols = depth * 12 ;

    std::vector<std::vector<std::string>> matrix(rows, std::vector<std::string>(cols, " "));

    printTreeP(root, matrix, cols / 2, 0, depth - 1);  

    // Imprimir de forma compacta reduciendo espacios adicionales
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            std::cout << std::setw(2) << (cell.empty() ? " " : cell);
        }
        std::cout << std::endl;
    }
}

void Tree::printTreeP(Node* current, std::vector<std::vector<std::string>>& matrix, int col, int row, int depth) const {
    if (current == nullptr || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
        return;
    }

    // Mostrar el valor del nodo
    matrix[row][col] = std::to_string(current->getId());

    int offset = std::max(1, int(pow(2, depth - 1) / 2));  


    // Imprimir conexiones con ramas
    if (current->getLeft() != nullptr) {
        matrix[row + 1][col - offset / 2] = "/";
        printTreeP(current->getLeft(), matrix, col - offset, row + 2, depth - 1);
    }
    if (current->getRight() != nullptr) {
        matrix[row + 1][col + offset / 2] = "\\";
        printTreeP(current->getRight(), matrix, col + offset, row + 2, depth - 1);
    }
}

int Tree::getRows(int depth) const {
    return depth * 2 - 1;  
}

int Tree::getCols(int depth) const {
    return pow(2, depth) - 1;  
}