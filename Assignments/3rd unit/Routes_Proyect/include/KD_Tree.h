#ifndef KD_TREE_H
#define KD_TREE_H

#include "Node.h"
#include "Route.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <set>

template <typename T>
class KD_Tree {
private:
    void clear(Node<T>* node); // Liberar memoria recursivamente
    Node<T>* root; // Puntero a la raíz del árbol

    // Funciones auxiliares
    Node<T>* insertRec(Node<T>* node, const T& data, const std::array<int, 2>& coords, int depth);
    void inOrderRec(Node<T>* node) const;
    void print_ubicaciones_rec(Node<T>* node) const;
    void print_routes_rec(Node<T>* node) const;
    Node<T>* findNodeRec(Node<T>* node, const std::array<int, 2>& coords, int depth) const;
    bool findNodeByNameRec(Node<T>* node, const std::string& name) const;

public:
    KD_Tree();
    ~KD_Tree();

    // Funciones públicas
    void insert(const T& data, int x, int y);
    void inOrder() const;
    void load_ubicaciones(const std::string& fileName);
    void load_routes(const std::string& fileName);
    void print_ubicaciones() const;
    Node<T>* findNode(int x, int y) const;
    bool findNodeByName(const std::string& name) const;
    void print_routes() const;
};

#include "../src/KD_Tree.cpp"

#endif // KD_TREE_H