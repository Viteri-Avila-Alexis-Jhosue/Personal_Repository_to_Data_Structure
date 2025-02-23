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
        std::string initial_hour, last_hour, level_str;

        // Leer campos comunes
        if (std::getline(stream, name, ',') &&
            stream >> initialX && stream.ignore() &&
            stream >> initialY && stream.ignore() &&
            std::getline(stream, initialName, ',') &&
            stream >> lastX && stream.ignore() &&
            stream >> lastY && stream.ignore() &&
            std::getline(stream, lastName, ',') &&
            std::getline(stream, distance_str, ',') &&
            std::getline(stream, speed_str, ',')) {

            int distance = std::stoi(distance_str);
            int speed = std::stoi(speed_str);

            // Crear ubicaciones
            Ubication initial(initialX, initialY, initialName);
            Ubication last(lastX, lastY, lastName);

            // Verificar si hay datos de tráfico adicionales
            if (std::getline(stream, initial_hour, ',') &&
                std::getline(stream, last_hour, ',') &&
                std::getline(stream, level_str)) {

                // Crear el objeto Trafic si los datos están presentes
                int level = std::stoi(level_str);
                Trafic trafic(initial_hour, last_hour, level);

                std::cout << "Ruta con trafico: " << name << std::endl;
                Route route(name, distance, initial, last, speed, trafic);
                insert(route, initialX, initialY);
            } else {
                std::cout << "Ruta sin trafico: " << name << std::endl;
                Route route(name, distance, initial, last, speed);
                insert(route, initialX, initialY);
            }
        } else {
            std::cerr << "Error: Formato de línea incorrecto en el archivo." << std::endl;
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

template <typename T>
T* KD_Tree<T>::getNodeByNameRec(Node<T>* node, const std::string& name) const {
    if (node == nullptr) {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si la ruta en el nodo actual tiene el nombre buscado
    if (node->data.getName() == name) {
        return &(node->data); // Retornar un puntero al dato del nodo
    }

    // Buscar en el subárbol izquierdo
    T* foundInLeft = getNodeByNameRec(node->left, name);
    if (foundInLeft != nullptr) {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameRec(node->right, name);
}

template <typename T>
T* KD_Tree<T>::getNodeByName(const std::string& name) const {
    return getNodeByNameRec(root, name); // Iniciar la búsqueda desde la raíz
}

template <typename T>
T* KD_Tree<T>::getNodeByNameAndCoordinatesRec(Node<T>* node, const std::string& name, int x, int y) const {
    if (node == nullptr) {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si el nodo actual coincide en nombre y coordenadas
    if (node->data.getName() == name && node->data.getInitialUbication().getX() == x && node->data.getInitialUbication().getY() == y) {
        return &(node->data); // Retornar un puntero al dato del nodo si se cumplen ambas condiciones
    }

    // Buscar en el subárbol izquierdo
    T* foundInLeft = getNodeByNameAndCoordinatesRec(node->left, name, x, y);
    if (foundInLeft != nullptr) {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameAndCoordinatesRec(node->right, name, x, y);
}

template <typename T>
T* KD_Tree<T>::getNodeByNameAndCoordinates(const std::string& name, int x, int y) const {
    return getNodeByNameAndCoordinatesRec(root, name, x, y); // Iniciar la búsqueda desde la raíz
}

template <typename T>
T* KD_Tree<T>::getNodeByNameAndLastCoordinatesRec(Node<T>* node, const std::string& name, int x, int y) const {
    if (node == nullptr) {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si el nodo actual coincide en nombre y coordenadas
    if (node->data.getName() == name && node->data.getLastUbication().getX() == x && node->data.getLastUbication().getY() == y) {
        return &(node->data); // Retornar un puntero al dato del nodo si se cumplen ambas condiciones
    }

    // Buscar en el subárbol izquierdo
    T* foundInLeft = getNodeByNameAndLastCoordinatesRec(node->left, name, x, y);
    if (foundInLeft != nullptr) {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameAndLastCoordinatesRec(node->right, name, x, y);
}

template <typename T>
T* KD_Tree<T>::getNodeByNameAndLastCoordinates(const std::string& name, int x, int y) const {
    return getNodeByNameAndLastCoordinatesRec(root, name, x, y); // Iniciar la búsqueda desde la raíz
}

template <typename T>
void KD_Tree<T>::aplicarTraficoEntreUbicaciones(const std::string& routeName, int x1, int y1, int x2, int y2, const Trafic& trafic) {
    // Obtener el tramo inicial
    T* tramoInicial = getNodeByNameAndCoordinates(routeName, x1, y1);
    T* tramoFinal = getNodeByNameAndLastCoordinates(routeName, x2, y2);
    T* tramoActual = tramoInicial;
    while (tramoActual && tramoActual != tramoFinal) {
        // Aplicar tráfico al tramo actual
        tramoActual->agregar_trafico(trafic);

        tramoActual->guardar_en_archivo();
        tramoActual = obtenerSiguienteTramo(routeName, tramoActual);
        
    }

    // Aplicar tráfico al tramo final
    tramoFinal->agregar_trafico(trafic);
    tramoFinal->guardar_en_archivo();
}

template <typename T>
T* KD_Tree<T>::obtenerSiguienteTramo(const std::string& routeName, T* tramoActual) {
    // Obtener la ubicación final del tramo actual
    Ubication lastUbication = tramoActual->getLastUbication();
    return getNodeByNameAndCoordinates(routeName, lastUbication.getX(), lastUbication.getY());
}

template <typename T>
T* KD_Tree<T>::obtenerUbicacionInicial(const std::string& routeName) const {
    Node<T>* current = root;
    T* ubicacionInicial = nullptr;

    // Recorre todos los nodos del árbol buscando la ubicación inicial
    std::function<void(Node<T>*)> buscarUbicacionInicial = [&](Node<T>* node) {
        if (!node) return;

        T data = node->getData();
        if (data.getName() == routeName) {
            bool esInicial = true;

            // Verificar que no sea la ubicación final de otro tramo de la misma ruta
            std::function<void(Node<T>*)> verificarFinales = [&](Node<T>* verificarNode) {
                if (!verificarNode) return;
                if (verificarNode->getData().getName() == routeName &&
                    verificarNode->getData().getLastUbication().getX() == data.getInitialUbication().getX() &&
                    verificarNode->getData().getLastUbication().getY() == data.getInitialUbication().getY()) {
                    esInicial = false;
                }
                verificarFinales(verificarNode->getLeft());
                verificarFinales(verificarNode->getRight());
            };

            verificarFinales(root);

            if (esInicial) {
                ubicacionInicial = &node->getData();
                return;
            }
        }

        buscarUbicacionInicial(node->getLeft());
        buscarUbicacionInicial(node->getRight());
    };

    buscarUbicacionInicial(current);
    return ubicacionInicial;
}

template <typename T>
T* KD_Tree<T>::obtenerUbicacionFinal(const std::string& routeName) const {
    Node<T>* current = root;
    T* ubicacionFinal = nullptr;

    // Recorre todos los nodos del árbol buscando la ubicación final
    std::function<void(Node<T>*)> buscarUbicacionFinal = [&](Node<T>* node) {
        if (!node) return;

        T data = node->getData();
        if (data.getName() == routeName) {
            bool esFinal = true;

            // Verificar que no sea la ubicación inicial de otro tramo de la misma ruta
            std::function<void(Node<T>*)> verificarIniciales = [&](Node<T>* verificarNode) {
                if (!verificarNode) return;
                if (verificarNode->getData().getName() == routeName &&
                    verificarNode->getData().getInitialUbication().getX() == data.getLastUbication().getX() &&
                    verificarNode->getData().getInitialUbication().getY() == data.getLastUbication().getY()) {
                    esFinal = false;
                }
                verificarIniciales(verificarNode->getLeft());
                verificarIniciales(verificarNode->getRight());
            };

            verificarIniciales(root);

            if (esFinal) {
                ubicacionFinal = &node->getData();
                return;
            }
        }

        buscarUbicacionFinal(node->getLeft());
        buscarUbicacionFinal(node->getRight());
    };

    buscarUbicacionFinal(current);
    return ubicacionFinal;
}

template <typename T>
void KD_Tree<T>::eliminarRutaCompleta(const std::string& nombreRuta) {
    // Función recursiva para eliminar todos los nodos de la ruta
    std::function<Node<T>*(Node<T>*, const std::string&)> eliminarRec = [&](Node<T>* node, const std::string& name) -> Node<T>* {
        if (node == nullptr) return nullptr;

        // Si el nodo actual pertenece a la ruta, eliminarlo
        if (node->data.getName() == name) {
            Node<T>* temp = node;
            node = nullptr;
            delete temp;
            return nullptr;
        }

        // Recursivamente eliminar en los subárboles
        node->left = eliminarRec(node->left, name);
        node->right = eliminarRec(node->right, name);
        return node;
    };

    // Eliminar todos los nodos de la ruta del árbol
    root = eliminarRec(root, nombreRuta);

    // Eliminar la ruta del archivo
    Route::eliminarRutaDelArchivo(nombreRuta);
}

template <typename T>
void KD_Tree<T>::eliminarTramo(const std::string& nombreRuta, int xInicial, int yInicial, int xFinal, int yFinal) {
    // Función recursiva para eliminar el nodo correspondiente al tramo
    std::function<Node<T>*(Node<T>*, const std::string&, int, int, int, int)> eliminarTramoRec = [&](Node<T>* node, const std::string& name, int xi, int yi, int xf, int yf) -> Node<T>* {
        if (node == nullptr) return nullptr;

        // Verificar si el nodo actual es el tramo a eliminar
        if (node->data.getName() == name &&
            node->data.getInitialUbication().getX() == xi &&
            node->data.getInitialUbication().getY() == yi &&
            node->data.getLastUbication().getX() == xf &&
            node->data.getLastUbication().getY() == yf) {
            Node<T>* temp = node;
            node = nullptr;
            delete temp;
            return nullptr;
        }

        // Recursivamente buscar y eliminar en los subárboles
        node->left = eliminarTramoRec(node->left, name, xi, yi, xf, yf);
        node->right = eliminarTramoRec(node->right, name, xi, yi, xf, yf);
        return node;
    };

    // Eliminar el tramo del árbol
    root = eliminarTramoRec(root, nombreRuta, xInicial, yInicial, xFinal, yFinal);

    // Eliminar el tramo del archivo
    Route::eliminarTramoDelArchivo(nombreRuta, xInicial, yInicial, xFinal, yFinal);
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
    string level;
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
              << "  - Trafico: " << route.getTrafic().getLevel() << "\n"
              << "--------------------------------------------\n";

    print_routes_rec(node->right);
}

template <typename T>
void KD_Tree<T>::print_routes() const {
    print_routes_rec(root);
}

