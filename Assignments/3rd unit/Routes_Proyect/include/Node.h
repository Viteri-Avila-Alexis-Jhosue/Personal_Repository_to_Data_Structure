#ifndef NODE_H
#define NODE_H

#include <memory>
#include <array>

template <typename T>
class Node {
public:
T data;                      // Datos almacenados en el nodo
std::array<int, 2> coords;   // Coordenadas (x, y) del nodo
Node<T>* left;               // Puntero al hijo izquierdo
Node<T>* right;              // Puntero al hijo derecho

    Node(const T& data, int x, int y);
};

#include "../src/Node.cpp"
#endif // Node_H
