/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/KD_tree.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

KD_tree::KD_tree() : root(nullptr), dimension(2) {}

KD_tree::~KD_tree() {
    clear(root);
}

// Método para limpiar memoria del árbol
void KD_tree::clear(Node* current) {
    if (current) {
        clear(current->getLeft());
        clear(current->getRight());
        delete current;
    }
}

// Inserción de un nodo en el árbol
void KD_tree::insert(int x, int y) {
    Node* newNode = new Node(x, y);
    root = insert(root, newNode, 0);
}

Node* KD_tree::insert(Node* current, Node* newNode, int depth) {
    if (!current) return newNode;

    int axis = depth % dimension; // Alternar entre X (0) y Y (1)

    if ((axis == 0 && newNode->getX() < current->getX()) || 
        (axis == 1 && newNode->getY() < current->getY())) {
        current->setLeft(insert(current->getLeft(), newNode, depth + 1));
    } else {
        current->setRight(insert(current->getRight(), newNode, depth + 1));
    }

    return current;
}

void KD_tree::remove(int x, int y) {
    bool nodeDeleted = false;
    root = remove(root, x, y, 0, &nodeDeleted);
    if (nodeDeleted) {
        std::cout << "Nodo (" << x << ", " << y << ") eliminado correctamente.\n";
    } else {
        std::cout << "Nodo (" << x << ", " << y << ") no encontrado en el árbol.\n";
    }
}

Node* KD_tree::remove(Node* current, const int x, const int y, int depth, bool* nodeDeleted) {
    if (!current) return nullptr;

    int axis = depth % dimension;

    if (current->getX() == x && current->getY() == y) {
        *nodeDeleted = true;  // Indicar que se encontró y eliminó un nodo
        if (current->getRight()) {
            Node* minNode = findMin(current->getRight(), depth, axis);
            current->setX(minNode->getX());
            current->setY(minNode->getY());
            current->setRight(remove(current->getRight(), minNode->getX(), minNode->getY(), depth + 1, nodeDeleted));
        } else if (current->getLeft()) {
            Node* minNode = findMin(current->getLeft(), depth, axis);
            current->setX(minNode->getX());
            current->setY(minNode->getY());
            current->setRight(remove(current->getLeft(), minNode->getX(), minNode->getY(), depth + 1, nodeDeleted));
            current->setLeft(nullptr);
        } else {
            delete current;
            return nullptr;
        }
    } else if ((axis == 0 && x < current->getX()) || (axis == 1 && y < current->getY())) {
        current->setLeft(remove(current->getLeft(), x, y, depth + 1, nodeDeleted));
    } else {
        current->setRight(remove(current->getRight(), x, y, depth + 1, nodeDeleted));
    }

    return current;
}

// Encontrar el mínimo en una dimensión específica
Node* KD_tree::findMin(Node* current, int depth, int dim) {
    if (!current) return nullptr;

    int axis = depth % dimension;

    if (axis == dim) {
        if (!current->getLeft()) return current;
        return findMin(current->getLeft(), depth + 1, dim);
    }

    Node* leftMin = findMin(current->getLeft(), depth + 1, dim);
    Node* rightMin = findMin(current->getRight(), depth + 1, dim);

    Node* minNode = current;
    if (leftMin && ((dim == 0 && leftMin->getX() < minNode->getX()) ||
                    (dim == 1 && leftMin->getY() < minNode->getY()))) {
        minNode = leftMin;
    }
    if (rightMin && ((dim == 0 && rightMin->getX() < minNode->getX()) ||
                     (dim == 1 && rightMin->getY() < minNode->getY()))) {
        minNode = rightMin;
    }

    return minNode;
}

// Impresión en orden
void KD_tree::printInOrder() const {
    printInOrder(root);
    std::cout << std::endl;
}

void KD_tree::printInOrder(Node* current) const {
    if (current) {
        printInOrder(current->getLeft());
        std::cout << "(" << current->getX() << ", " << current->getY() << ") ";
        printInOrder(current->getRight());
    }
}

// Impresión preorden
void KD_tree::printPreOrder() const {
    printPreOrder(root);
    std::cout << std::endl;
}

void KD_tree::printPreOrder(Node* current) const {
    if (current) {
        std::cout << "(" << current->getX() << ", " << current->getY() << ") ";
        printPreOrder(current->getLeft());
        printPreOrder(current->getRight());
    }
}

// Impresión postorden
void KD_tree::printPostOrder() const {
    printPostOrder(root);
    std::cout << std::endl;
}

void KD_tree::printPostOrder(Node* current) const {
    if (current) {
        printPostOrder(current->getLeft());
        printPostOrder(current->getRight());
        std::cout << "(" << current->getX() << ", " << current->getY() << ") ";
    }
}

// Getter y Setter para la raíz
Node* KD_tree::getRoot() const {
    return root;
}

void KD_tree::setRoot(Node* rootNode) {
    root = rootNode;
}
//----------------------------------------------------------------------------------------------------------------
int KD_tree::getDepth(Node* current) const {
    if (current == nullptr) {
        return 0;
    }
    int leftDepth = getDepth(current->getLeft());
    int rightDepth = getDepth(current->getRight());
    return std::max(leftDepth, rightDepth) + 1;
}

void KD_tree::printTree() const {
    if (root == nullptr) {  
        std::cout << "El arbol esta vacio.\n";
        return;
    }
    int depth = getDepth(root); 
   int rows = (depth * 3) + 1;  // Aumentando el número de filas
    int cols = (depth * 10) + 2; // Aumentando el número de columnas

    std::vector<std::vector<std::string>> matrix(rows, std::vector<std::string>(cols, " "));

    printTreeP(root, matrix, cols / 2, 0, depth - 1);  

    // Imprimir de forma compacta con los nodos más cercanos pero bien distribuidos
    for (const auto& row : matrix) {
        for (const auto& cell : row) {
            // Ajustamos el tamaño de la salida con std::setw() y dejamos espacio entre los nodos
            std::cout << std::setw(4) << (cell.empty() ? " " : cell);  // Ajuste el tamaño
        }
        std::cout << std::endl;
    }
}

void KD_tree::printTreeP(Node* current, std::vector<std::vector<std::string>>& matrix, int col, int row, int depth) const {
    if (current == nullptr || row >= matrix.size() || col < 0 || col >= matrix[0].size()) {
        return;
    }

    // Mostrar el valor del nodo como enteros
    matrix[row][col] = "(" + std::to_string(current->getX()) + "," + std::to_string(current->getY()) + ")";
    
    int offset = std::max(3, int(pow(2, depth - 1) / 2));  // Aumentando el valor de offset

    // Imprimir conexiones con ramas
    if (current->getLeft() != nullptr) {
        // Colocamos la rama izquierda
        matrix[row + 1][col - offset] = "/";  
        printTreeP(current->getLeft(), matrix, col - offset, row + 2, depth - 1);
    }
    
    if (current->getRight() != nullptr) {
        // Colocamos la rama derecha
        matrix[row + 1][col + offset] = "\\";  
        printTreeP(current->getRight(), matrix, col + offset, row + 2, depth - 1);
    }
}

int KD_tree::getRows(int depth) const {
    return depth * 2 - 1;  // Ajuste de las filas según la profundidad
}

int KD_tree::getCols(int depth) const {
    return std::max(20, static_cast<int>(pow(2, depth)) * 6);  // Conversión explícita a int

}
