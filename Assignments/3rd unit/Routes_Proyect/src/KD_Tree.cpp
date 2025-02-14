#include "../include/KD_Tree.h"
#include "../include/Node.h"
#include "../include/Ubication.h"
#include "../include/Route.h"
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
#include <functional>
#include <cmath>
#include <set>
#include <random>
#include <queue>
#include <map>
using namespace std;

template <typename T>
KD_Tree<T>::KD_Tree() : root(nullptr) {}

template <typename T>
KD_Tree<T>::~KD_Tree() {
    clear(root); // Liberar toda la memoria al destruir el árbol
}

template <typename T>
void KD_Tree<T>::clear(Node<T>* node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);  // Liberar el subárbol izquierdo
    clear(node->right); // Liberar el subárbol derecho
    delete node;        // Liberar el nodo actual
}

template <typename T>
Node<T>* KD_Tree<T>::insertRec(Node<T>* node, const T& data, const std::array<int, 2>& coords, int depth) {
    if (node == nullptr) {
        return new Node<T>(data, coords[0], coords[1]); // Crear un nuevo nodo
    }

    int axis = depth % 2; // Alternar entre eje X (0) y eje Y (1)

    if (coords[axis] < node->coords[axis]) {
        node->left = insertRec(node->left, data, coords, depth + 1);
    } else {
        node->right = insertRec(node->right, data, coords, depth + 1);
    }

    return node;
}

template <typename T>
void KD_Tree<T>::insert(const T& data, int x, int y) {
    root = insertRec(root, data, {x, y}, 0);
}

template <typename T>
void KD_Tree<T>::inOrderRec(Node<T>* node) const {
    if (node != nullptr) {
        inOrderRec(node->left);
        std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ")\n";
        inOrderRec(node->right);
    }
}

template <typename T>
void KD_Tree<T>::inOrder() const {
    inOrderRec(root);
}

template <typename T>
void KD_Tree<T>::load_ubicaciones(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando " << fileName << " ...." << std::endl;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string x_str, y_str, name;

        if (std::getline(stream, x_str, ',') &&
            std::getline(stream, y_str, ',') &&
            std::getline(stream, name, ',')) {
            int x = std::stoi(x_str);
            int y = std::stoi(y_str);
            Ubication ubication(x, y, name);

            insert(ubication, x, y);
        }
    }

    file.close();
}

template <typename T>
void KD_Tree<T>::load_routes(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando " << fileName << " ...." << std::endl;

    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string name, initialName, lastName, distance_str, speed_str;
        int initialX, initialY, lastX, lastY;

        if (std::getline(stream, name, ',') &&
            stream >> initialX && stream.ignore() &&
            stream >> initialY && stream.ignore() &&
            std::getline(stream, initialName, ',') &&
            stream >> lastX && stream.ignore() &&
            stream >> lastY && stream.ignore() &&
            std::getline(stream, lastName, ',') &&
            std::getline(stream, distance_str, ',') &&
            std::getline(stream, speed_str)) {
            
            int distance = std::stoi(distance_str);
            int speed = std::stoi(speed_str);

            Ubication initial(initialX, initialY, initialName);
            Ubication last(lastX, lastY, lastName);
            Route route(name, distance, initial, last, speed);


            insert(route, initialX, initialY);
        }
    }

    file.close();
}


template <typename T>
Node<T>* KD_Tree<T>::findNodeRec(Node<T>* node, const std::array<int, 2>& coords, int depth) const {
    if (node == nullptr || (node->coords[0] == coords[0] && node->coords[1] == coords[1])) {
        return node;
    }

    int axis = depth % 2;
    if (coords[axis] < node->coords[axis]) {
        return findNodeRec(node->left, coords, depth + 1);
    } else {
        return findNodeRec(node->right, coords, depth + 1);
    }
}

template <typename T>
Node<T>* KD_Tree<T>::findNode(int x, int y) const {
    return findNodeRec(root, {x, y}, 0);
}

template <typename T>
bool KD_Tree<T>::findNodeByNameRec(Node<T>* node, const std::string& name) const {
    if (node == nullptr) {
        return false; // Caso base: nodo nulo
    }

    // Verificar si la ruta en el nodo actual tiene el nombre buscado
    if (node->data.getName() == name) {
        return true; // Se encontró una ruta con el nombre especificado
    }

    // Recorrer el subárbol izquierdo y derecho
    return findNodeByNameRec(node->left, name) || findNodeByNameRec(node->right, name);
}

template <typename T>
bool KD_Tree<T>::findNodeByName(const std::string& name) const {
    return findNodeByNameRec(root, name); // Iniciar la búsqueda desde la raíz
}

//----------------------------------------------------------------------------------------------------------
//----------------------------Impresiones------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------

template <typename T>
void KD_Tree<T>::print_ubicaciones_rec(Node<T>* node) const {
    if (node == nullptr) {
        return;
    }

    print_ubicaciones_rec(node->left);
    std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ") -> " << node->data.getName() << std::endl;
    print_ubicaciones_rec(node->right);
}

template <typename T>
void KD_Tree<T>::print_ubicaciones() const {
    print_ubicaciones_rec(root);
}

template <typename T>
void KD_Tree<T>::print_routes_rec(Node<T>* node) const {
    if (node == nullptr) {
        return;
    }

    print_routes_rec(node->left);

    // Imprimir los datos de la ruta almacenada en el nodo
    const Route& route = node->data;
    std::cout << "Ruta: " << route.getName() << "\n"
              << "  - Inicio: (" << route.getInitialUbication().getX() << ", " << route.getInitialUbication().getY() << ") -> " << route.getInitialUbication().getName() << "\n"
              << "  - Fin: (" << route.getLastUbication().getX() << ", " << route.getLastUbication().getY() << ") -> " << route.getLastUbication().getName() << "\n"
              << "  - Distancia: " << route.getDistance() << "\n"
              << "  - Velocidad: " << route.getSpeed() << "\n"
              << "--------------------------------------------\n";

    print_routes_rec(node->right);
}

template <typename T>
void KD_Tree<T>::print_routes() const {
    print_routes_rec(root);
}

