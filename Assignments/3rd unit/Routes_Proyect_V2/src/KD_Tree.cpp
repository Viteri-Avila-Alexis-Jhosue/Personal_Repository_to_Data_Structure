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
#include <filesystem>
using namespace std;

template <typename T>
KD_Tree<T>::KD_Tree() : root(nullptr) {}

template <typename T>
KD_Tree<T>::~KD_Tree()
{
    clear(root); // Liberar toda la memoria al destruir el árbol
}

template <typename T>
void KD_Tree<T>::clear(Node<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    clear(node->left);  // Liberar el subárbol izquierdo
    clear(node->right); // Liberar el subárbol derecho
    delete node;        // Liberar el nodo actual
}

template <typename T>
Node<T> *KD_Tree<T>::insertRec(Node<T> *node, const T &data, const std::array<int, 2> &coords, int depth)
{
    if (node == nullptr)
    {
        return new Node<T>(data, coords[0], coords[1]); // Crear un nuevo nodo
    }

    int axis = depth % 2; // Alternar entre eje X (0) y eje Y (1)

    if (coords[axis] < node->coords[axis])
    {
        node->left = insertRec(node->left, data, coords, depth + 1);
    }
    else
    {
        node->right = insertRec(node->right, data, coords, depth + 1);
    }

    return node;
}

template <typename T>
void KD_Tree<T>::insert(const T &data, int x, int y)
{
    root = insertRec(root, data, {x, y}, 0);
}

template <typename T>
void KD_Tree<T>::inOrderRec(Node<T> *node) const
{
    if (node != nullptr)
    {
        inOrderRec(node->left);
        std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ")\n";
        inOrderRec(node->right);
    }
}

template <typename T>
void KD_Tree<T>::inOrder() const
{
    inOrderRec(root);
}

template <typename T>
void KD_Tree<T>::load_ubicaciones(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando " << fileName << " ...." << std::endl;

    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string x_str, y_str, name, description;

        if (std::getline(stream, x_str, ',') &&
            std::getline(stream, y_str, ',') &&
            std::getline(stream, name, ',') &&
            std::getline(stream, description, ','))
        {
            int x = std::stoi(x_str);
            int y = std::stoi(y_str);
            Ubication ubication(x, y, name, description);

            insert(ubication, x, y);
        }
    }

    file.close();
}
template <typename T>
void KD_Tree<T>::load_routes(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando " << fileName << " ...." << std::endl;

    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string name, initialName, lastName, distance_str, speed_str;
        int initialX, initialY, lastX, lastY;
        std::string initial_hour, last_hour, level_str;

        // Leer campos comunes de la ruta
        if (std::getline(stream, name, ',') &&
            stream >> initialX && stream.ignore() &&
            stream >> initialY && stream.ignore() &&
            std::getline(stream, initialName, ',') &&
            stream >> lastX && stream.ignore() &&
            stream >> lastY && stream.ignore() &&
            std::getline(stream, lastName, ',') &&
            std::getline(stream, distance_str, ',') &&
            std::getline(stream, speed_str, ','))
        {

            try
            {
                double distance = std::stod(distance_str);
                double speed = std::stod(speed_str);

                // Crear ubicaciones inicial y final
                Ubication initial(initialX, initialY, initialName);
                Ubication last(lastX, lastY, lastName);

                // Leer tramos de tráfico si existen
                std::vector<Trafic> trafics;
                while (std::getline(stream, initial_hour, ',') &&
                       std::getline(stream, last_hour, ',') &&
                       std::getline(stream, level_str, ','))
                {
                    try
                    {
                        int level = std::stoi(level_str);
                        Trafic trafic(initial_hour, last_hour, level);
                        trafics.push_back(trafic);
                    }
                    catch (const std::invalid_argument &)
                    {
                        std::cerr << "Error: Nivel de trafico invalido en la linea: " << line << std::endl;
                        break;
                    }
                }
                if (!trafics.empty())
                {
                    Route route = Route(name, distance, initial, last, speed, trafics);
                    std::cout << "Ruta con trafico: " << name << " (" << trafics.size() << " tramos de trafico)" << std::endl;
                    insert(route, initialX, initialY);
                }
                else
                {
                    Route route = Route(name, distance, initial, last, speed);
                    std::cout << "Ruta sin trafico: " << name << std::endl;
                    insert(route, initialX, initialY);
                }

                // Insertar la ruta en el KD-Tree
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Error: Formato de numero invalido en la linea: " << line << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Formato de linea incorrecto en el archivo: " << line << std::endl;
        }
    }

    file.close();
}

template <typename T>
Node<T> *KD_Tree<T>::findNodeRec(Node<T> *node, const std::array<int, 2> &coords, int depth) const
{
    if (node == nullptr || (node->coords[0] == coords[0] && node->coords[1] == coords[1]))
    {
        return node;
    }

    int axis = depth % 2;
    if (coords[axis] < node->coords[axis])
    {
        return findNodeRec(node->left, coords, depth + 1);
    }
    else
    {
        return findNodeRec(node->right, coords, depth + 1);
    }
}

template <typename T>
Node<T> *KD_Tree<T>::findNode(int x, int y) const
{
    return findNodeRec(root, {x, y}, 0);
}

template <typename T>
bool KD_Tree<T>::findNodeByNameRec(Node<T> *node, const std::string &name) const
{
    if (node == nullptr)
    {
        return false; // Caso base: nodo nulo
    }

    // Verificar si la ruta en el nodo actual tiene el nombre buscado
    if (node->data.getName() == name)
    {
        return true; // Se encontró una ruta con el nombre especificado
    }

    // Recorrer el subárbol izquierdo y derecho
    return findNodeByNameRec(node->left, name) || findNodeByNameRec(node->right, name);
}

template <typename T>
bool KD_Tree<T>::findNodeByName(const std::string &name) const
{
    return findNodeByNameRec(root, name); // Iniciar la búsqueda desde la raíz
}

template <typename T>
T *KD_Tree<T>::getNodeByNameRec(Node<T> *node, const std::string &name) const
{
    if (node == nullptr)
    {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si la ruta en el nodo actual tiene el nombre buscado
    if (node->data.getName() == name)
    {
        return &(node->data); // Retornar un puntero al dato del nodo
    }

    // Buscar en el subárbol izquierdo
    T *foundInLeft = getNodeByNameRec(node->left, name);
    if (foundInLeft != nullptr)
    {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameRec(node->right, name);
}

template <typename T>
T *KD_Tree<T>::getNodeByName(const std::string &name) const
{
    return getNodeByNameRec(root, name); // Iniciar la búsqueda desde la raíz
}

template <typename T>
T *KD_Tree<T>::getNodeByNameAndCoordinatesRec(Node<T> *node, const std::string &name, int x, int y) const
{
    if (node == nullptr)
    {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si el nodo actual coincide en nombre y coordenadas
    if (node->data.getName() == name && node->data.getInitialUbication().getX() == x && node->data.getInitialUbication().getY() == y)
    {
        return &(node->data); // Retornar un puntero al dato del nodo si se cumplen ambas condiciones
    }

    // Buscar en el subárbol izquierdo
    T *foundInLeft = getNodeByNameAndCoordinatesRec(node->left, name, x, y);
    if (foundInLeft != nullptr)
    {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameAndCoordinatesRec(node->right, name, x, y);
}

template <typename T>
T *KD_Tree<T>::getNodeByNameAndCoordinates(const std::string &name, int x, int y) const
{
    return getNodeByNameAndCoordinatesRec(root, name, x, y); // Iniciar la búsqueda desde la raíz
}

template <typename T>
T *KD_Tree<T>::getNodeByNameAndLastCoordinatesRec(Node<T> *node, const std::string &name, int x, int y) const
{
    if (node == nullptr)
    {
        return nullptr; // Caso base: nodo nulo
    }

    // Verificar si el nodo actual coincide en nombre y coordenadas
    if (node->data.getName() == name && node->data.getLastUbication().getX() == x && node->data.getLastUbication().getY() == y)
    {
        return &(node->data); // Retornar un puntero al dato del nodo si se cumplen ambas condiciones
    }

    // Buscar en el subárbol izquierdo
    T *foundInLeft = getNodeByNameAndLastCoordinatesRec(node->left, name, x, y);
    if (foundInLeft != nullptr)
    {
        return foundInLeft;
    }

    // Buscar en el subárbol derecho
    return getNodeByNameAndLastCoordinatesRec(node->right, name, x, y);
}

template <typename T>
T *KD_Tree<T>::getNodeByNameAndLastCoordinates(const std::string &name, int x, int y) const
{
    return getNodeByNameAndLastCoordinatesRec(root, name, x, y); // Iniciar la búsqueda desde la raíz
}

template <typename T>
void KD_Tree<T>::aplicarTraficoEntreUbicaciones(const std::string &routeName, int x1, int y1, int x2, int y2, const Trafic &trafic)
{
    // Obtener el tramo inicial
    T *tramoInicial = getNodeByNameAndCoordinates(routeName, x1, y1);
    T *tramoFinal = getNodeByNameAndLastCoordinates(routeName, x2, y2);
    T *tramoActual = tramoInicial;
    while (tramoActual && tramoActual != tramoFinal)
    {
        tramoActual->eliminarTramoDelArchivo(routeName, tramoActual->getInitialUbication().getX(), tramoActual->getInitialUbication().getY(),
                                             tramoActual->getLastUbication().getX(), tramoActual->getLastUbication().getY());
        tramoActual->agregar_trafico(trafic);
        tramoActual->guardar_en_archivo();
        tramoActual = obtenerSiguienteTramo(routeName, tramoActual);
    }

    tramoFinal->eliminarTramoDelArchivo(routeName, tramoFinal->getInitialUbication().getX(), tramoFinal->getInitialUbication().getY(),
                                        tramoFinal->getLastUbication().getX(), tramoFinal->getLastUbication().getY());
    tramoFinal->agregar_trafico(trafic);
    tramoFinal->guardar_en_archivo();
}

template <typename T>
T *KD_Tree<T>::obtenerSiguienteTramo(const std::string &routeName, T *tramoActual)
{
    // Obtener la ubicación final del tramo actual
    Ubication lastUbication = tramoActual->getLastUbication();
    return getNodeByNameAndCoordinates(routeName, lastUbication.getX(), lastUbication.getY());
}

template <typename T>
T *KD_Tree<T>::obtenerUbicacionInicial(const std::string &routeName) const
{
    Node<T> *current = root;
    T *ubicacionInicial = nullptr;

    // Recorre todos los nodos del árbol buscando la ubicación inicial
    std::function<void(Node<T> *)> buscarUbicacionInicial = [&](Node<T> *node)
    {
        if (!node)
            return;

        T data = node->getData();
        if (data.getName() == routeName)
        {
            bool esInicial = true;

            // Verificar que no sea la ubicación final de otro tramo de la misma ruta
            std::function<void(Node<T> *)> verificarFinales = [&](Node<T> *verificarNode)
            {
                if (!verificarNode)
                    return;
                if (verificarNode->getData().getName() == routeName &&
                    verificarNode->getData().getLastUbication().getX() == data.getInitialUbication().getX() &&
                    verificarNode->getData().getLastUbication().getY() == data.getInitialUbication().getY())
                {
                    esInicial = false;
                }
                verificarFinales(verificarNode->getLeft());
                verificarFinales(verificarNode->getRight());
            };

            verificarFinales(root);

            if (esInicial)
            {
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
T *KD_Tree<T>::obtenerUbicacionFinal(const std::string &routeName) const
{
    Node<T> *current = root;
    T *ubicacionFinal = nullptr;

    // Recorre todos los nodos del árbol buscando la ubicación final
    std::function<void(Node<T> *)> buscarUbicacionFinal = [&](Node<T> *node)
    {
        if (!node)
            return;

        T data = node->getData();
        if (data.getName() == routeName)
        {
            bool esFinal = true;

            // Verificar que no sea la ubicación inicial de otro tramo de la misma ruta
            std::function<void(Node<T> *)> verificarIniciales = [&](Node<T> *verificarNode)
            {
                if (!verificarNode)
                    return;
                if (verificarNode->getData().getName() == routeName &&
                    verificarNode->getData().getInitialUbication().getX() == data.getLastUbication().getX() &&
                    verificarNode->getData().getInitialUbication().getY() == data.getLastUbication().getY())
                {
                    esFinal = false;
                }
                verificarIniciales(verificarNode->getLeft());
                verificarIniciales(verificarNode->getRight());
            };

            verificarIniciales(root);

            if (esFinal)
            {
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
// Método recursivo para eliminar una ruta del árbol
template <typename T>
Node<T> *KD_Tree<T>::eliminarRec(Node<T> *node, const std::string &name) {
    if (node == nullptr)
        return nullptr;

    if (node->data.getName() == name) {
        // Caso 1: Nodo sin hijos
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (node->left == nullptr) {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            // Buscar el nodo más a la derecha del subárbol izquierdo
            Node<T> *successor = node->left;
            Node<T> *parent = node;
            while (successor->right != nullptr) {
                parent = successor;
                successor = successor->right;
            }

            node->data = successor->data; // Copiar datos del sucesor

            // Eliminar el sucesor
            if (parent->right == successor) {
                parent->right = successor->left;
            } else {
                parent->left = successor->left;
            }
            delete successor;
        }
    } else {
        node->left = eliminarRec(node->left, name);
        node->right = eliminarRec(node->right, name);
    }

    return node;
}

// Método para eliminar una ruta completa del árbol
template <typename T>
void KD_Tree<T>::eliminarRutaCompleta(const std::string &nombreRuta) {
    while (findNodeByName(nombreRuta)) {
        root = eliminarRec(root, nombreRuta);
    }
    Route::eliminarRutaDelArchivo(nombreRuta);
}

// Método recursivo para eliminar un tramo específico de una ruta
template <typename T>
Node<T> *KD_Tree<T>::eliminarTramoRec(Node<T> *node, const std::string &name, int xi, int yi, int xf, int yf) {
    if (node == nullptr)
        return nullptr;

    if (node->data.getName() == name &&
        node->data.getInitialUbication().getX() == xi &&
        node->data.getInitialUbication().getY() == yi &&
        node->data.getLastUbication().getX() == xf &&
        node->data.getLastUbication().getY() == yf) {
        // Caso 1: Nodo sin hijos
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // Caso 2: Nodo con un solo hijo
        else if (node->left == nullptr) {
            Node<T> *temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node<T> *temp = node->left;
            delete node;
            return temp;
        }
        // Caso 3: Nodo con dos hijos
        else {
            Node<T> *successor = node->left;
            Node<T> *parent = node;
            while (successor->right != nullptr) {
                parent = successor;
                successor = successor->right;
            }

            node->data = successor->data; // Copiar datos del sucesor

            // Eliminar el sucesor
            if (parent->right == successor) {
                parent->right = successor->left;
            } else {
                parent->left = successor->left;
            }
            delete successor;
        }
    } else {
        node->left = eliminarTramoRec(node->left, name, xi, yi, xf, yf);
        node->right = eliminarTramoRec(node->right, name, xi, yi, xf, yf);
    }

    return node;
}

// Método público para eliminar un tramo específico de una ruta
template <typename T>
void KD_Tree<T>::eliminarTramo(const std::string &nombreRuta, int xInicial, int yInicial, int xFinal, int yFinal) {
    root = eliminarTramoRec(root, nombreRuta, xInicial, yInicial, xFinal, yFinal);
    Route::eliminarTramoDelArchivo(nombreRuta, xInicial, yInicial, xFinal, yFinal);
}

template <typename T>
bool KD_Tree<T>::validarTramoExistente(const std::string &routeName, int xInicial, int yInicial, int xFinal, int yFinal, double distance) const
{
    return validarTramoExistenteRec(root, routeName, xInicial, yInicial, xFinal, yFinal, distance);
}

template <typename T>
bool KD_Tree<T>::validarTramoExistenteRec(Node<T> *node, const std::string &routeName, int xInicial, int yInicial, int xFinal, int yFinal, double distance) const
{
    if (node == nullptr)
    {
        return false;
    }

    const Route &route = node->data;
    if ((route.getInitialUbication().getX() == xInicial &&
         route.getInitialUbication().getY() == yInicial &&
         route.getLastUbication().getX() == xFinal &&
         route.getLastUbication().getY() == yFinal &&
         route.getDistance() == distance) ||
        (route.getInitialUbication().getX() == xFinal &&
         route.getInitialUbication().getY() == yFinal &&
         route.getLastUbication().getX() == xInicial &&
         route.getLastUbication().getY() == yInicial &&
         route.getDistance() == distance))
    {
        return true; // Se encontró un tramo idéntico o una ruta inversa
    }

    // Recursivamente buscar en los subárboles izquierdo y derecho
    return validarTramoExistenteRec(node->left, routeName, xInicial, yInicial, xFinal, yFinal, distance) ||
           validarTramoExistenteRec(node->right, routeName, xInicial, yInicial, xFinal, yFinal, distance);
}
template <typename T>
void KD_Tree<T>::obtenerUbicacionesRec(Node<T> *node, std::vector<T> &ubicaciones) const
{
    if (node == nullptr)
        return;

    // Recorrido in-order para obtener las ubicaciones en orden
    obtenerUbicacionesRec(node->left, ubicaciones);
    ubicaciones.push_back(node->data);
    obtenerUbicacionesRec(node->right, ubicaciones);
}

template <typename T>
std::vector<T> KD_Tree<T>::obtenerTodasLasUbicaciones() const
{
    std::vector<T> ubicaciones;
    obtenerUbicacionesRec(root, ubicaciones);
    return ubicaciones;
}

template <typename T>
void KD_Tree<T>::obtenerRutasRec(Node<T> *node, std::vector<T> &rutas) const
{
    if (node == nullptr)
        return;

    // Recorrido in-order para obtener las rutas en orden
    obtenerRutasRec(node->left, rutas);
    rutas.push_back(node->data); // Aquí `data` es una ruta (Route)
    obtenerRutasRec(node->right, rutas);
}

template <typename T>
std::vector<T> KD_Tree<T>::obtenerTodasLasRutas() const
{
    std::vector<T> rutas;
    obtenerRutasRec(root, rutas); // `root` es la raíz del árbol KD
    return rutas;
}

template <typename T>
void KD_Tree<T>::print_ubicaciones_rec(Node<T> *node) const
{
    if (node == nullptr)
    {
        return;
    }

    print_ubicaciones_rec(node->left);
    std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ") -> " << node->data.getName() << " -> " << node->data.getDescription() << std::endl;
    print_ubicaciones_rec(node->right);
}

template <typename T>
void KD_Tree<T>::print_ubicaciones() const
{
    print_ubicaciones_rec(root);
}

template <typename T>
void KD_Tree<T>::print_routes_rec(Node<T> *node) const
{
    if (node == nullptr)
    {
        return;
    }

    // Llamada recursiva al subárbol izquierdo
    print_routes_rec(node->left);

    // Imprimir los datos de la ruta almacenada en el nodo
    const Route &route = node->data;
    std::cout << "Ruta: " << route.getName() << "\n"
              << "  - Inicio: (" << route.getInitialUbication().getX() << ", " << route.getInitialUbication().getY() << ") -> " << route.getInitialUbication().getName() << "\n"
              << "  - Fin: (" << route.getLastUbication().getX() << ", " << route.getLastUbication().getY() << ") -> " << route.getLastUbication().getName() << "\n"
              << "  - Distancia: " << route.getDistance() << "\n"
              << "  - Velocidad: " << route.getSpeed() << "\n";

    // Verificar si hay tráfico antes de imprimirlo
    const std::vector<Trafic> &trafics = route.getTrafics();
    if (!trafics.empty())
    {
        std::cout << "  - Trafico:\n";
        for (const auto &trafic : trafics)
        {
            std::cout << "    * Desde: " << trafic.getInitialHour()
                      << " hasta: " << trafic.getLastHour()
                      << " - Nivel: " << trafic.getLevel() << "\n";
        }
    }
    else
    {
        std::cout << "  - Trafico: No hay tramos de tráfico registrados\n";
    }

    std::cout << "--------------------------------------------\n";

    // Llamada recursiva al subárbol derecho
    print_routes_rec(node->right);
}

template <typename T>
void KD_Tree<T>::print_routes() const
{
    print_routes_rec(root);
}

template <typename T>
void KD_Tree<T>::print_routes_name_rec(Node<T> *node, string routeName) const
{
    if (node == nullptr)
    {
        return;
    }

    // Llamada recursiva al subárbol izquierdo
    print_routes_name_rec(node->left, routeName);
    const Route &route = node->data;
    if (route.getName() == routeName)
    {
        std::cout << "Ruta: " << route.getName() << "\n"
                  << "  - Inicio: (" << route.getInitialUbication().getX() << ", " << route.getInitialUbication().getY() << ") -> " << route.getInitialUbication().getName() << "\n"
                  << "  - Fin: (" << route.getLastUbication().getX() << ", " << route.getLastUbication().getY() << ") -> " << route.getLastUbication().getName() << "\n"
                  << "  - Distancia: " << route.getDistance() << "\n"
                  << "  - Velocidad: " << route.getSpeed() << "\n";

        // Verificar si hay tráfico antes de imprimirlo
        const std::vector<Trafic> &trafics = route.getTrafics();
        if (!trafics.empty())
        {
            std::cout << "  - Trafico:\n";
            for (const auto &trafic : trafics)
            {
                std::cout << "    * Desde: " << trafic.getInitialHour()
                          << " hasta: " << trafic.getLastHour()
                          << " - Nivel: " << trafic.getLevel() << "\n";
            }
        }
        else
        {
            std::cout << "  - Trafico: No hay tramos de tráfico registrados\n";
        }

        std::cout << "--------------------------------------------\n";
    }
    // Llamada recursiva al subárbol derecho
    print_routes_name_rec(node->right, routeName);
}

template <typename T>
void KD_Tree<T>::print_routes_name(string routeName) const
{
    print_routes_name_rec(root, routeName);
}

template <typename T>
void KD_Tree<T>::verificarBidireccionalidadRec(Node<T>* node, KD_Tree<T>& nuevoArbol) const {
    if (node == nullptr) {
        return;
    }

    // Obtener la ruta actual
    T rutaActual = node->data;

    // Insertar la ruta actual en el nuevo árbol
    nuevoArbol.insert(rutaActual, rutaActual.getInitialUbication().getX(), rutaActual.getInitialUbication().getY());

    // Verificar si existe la ruta inversa
    std::string inicio = rutaActual.getInitialUbication().getName();
    std::string fin = rutaActual.getLastUbication().getName();
    bool existeInversa = false;

    // Buscar la ruta inversa en el árbol original
    for (const auto& ruta : obtenerTodasLasRutas()) {
        if (ruta.getInitialUbication().getName() == fin && ruta.getLastUbication().getName() == inicio) {
            existeInversa = true;
            break;
        }
    }

    // Si no existe la ruta inversa, crearla y agregarla al nuevo árbol
    if (!existeInversa) {
        T rutaInversa = rutaActual;
        rutaInversa.setInitialUbication(rutaActual.getLastUbication());
        rutaInversa.setLastUbication(rutaActual.getInitialUbication());
        nuevoArbol.insert(rutaInversa, rutaInversa.getInitialUbication().getX(), rutaInversa.getInitialUbication().getY());
    }

    // Recorrer los subárboles
    verificarBidireccionalidadRec(node->left, nuevoArbol);
    verificarBidireccionalidadRec(node->right, nuevoArbol);
}

// Implementación de la función para crear un nuevo árbol de rutas con bidireccionalidad
template <typename T>
KD_Tree<T> KD_Tree<T>::crearArbolBidireccional() const {
    KD_Tree<T> nuevoArbol;

    // Llamar a la función recursiva para verificar y agregar rutas inversas
    verificarBidireccionalidadRec(root, nuevoArbol);

    return nuevoArbol;
}

template <typename T>
Node<T>* KD_Tree<T>::obtenerNodoPorNombreUbicacionRec(Node<T>* node, const std::string& nombreUbicacion) const {
    if (node == nullptr) {
        return nullptr; // Si el nodo es nulo, no se encontró la ubicación
    }

    // Verificar si el nodo actual contiene la ubicación buscada
    T data = node->data;
    if (data.getInitialUbication().getName() == nombreUbicacion || data.getLastUbication().getName() == nombreUbicacion) {
        return node; // Devolver el nodo si coincide
    }

    // Buscar en los subárboles
    Node<T>* resultadoIzquierdo = obtenerNodoPorNombreUbicacionRec(node->left, nombreUbicacion);
    if (resultadoIzquierdo != nullptr) {
        return resultadoIzquierdo; // Si se encontró en el subárbol izquierdo, devolverlo
    }

    Node<T>* resultadoDerecho = obtenerNodoPorNombreUbicacionRec(node->right, nombreUbicacion);
    return resultadoDerecho; // Devolver el resultado del subárbol derecho (puede ser nullptr)
}

// Implementación de la función pública
template <typename T>
Node<T>* KD_Tree<T>::obtenerNodoPorNombreUbicacion(const std::string& nombreUbicacion) const {
    return obtenerNodoPorNombreUbicacionRec(root, nombreUbicacion);
}

template <typename T>
void KD_Tree<T>::updateUbicationName(const std::string& oldName, const std::string& newName) {
    updateUbicationNameRec(root, oldName, newName);
}

template <typename T>
void KD_Tree<T>::updateUbicationNameRec(Node<T>* node, const std::string& oldName, const std::string& newName) {
    if (!node) return;

    T& tramo = node->data; // Usamos el dato genérico T

    // Si la ubicación inicial coincide con el nombre antiguo, actualizar
    if (tramo.getInitialUbication().getName() == oldName) {
        tramo.eliminarTramoDelArchivo(tramo.getName(), tramo.getInitialUbication().getX(), tramo.getInitialUbication().getY(), 
                                    tramo.getLastUbication().getX(), tramo.getLastUbication().getY());
                                    tramo.setInitialUbication(Ubication(tramo.getInitialUbication().getX(), tramo.getInitialUbication().getY(), newName));
                                    tramo.guardar_en_archivo();
    }

    // Si la ubicación final coincide con el nombre antiguo, actualizar
    if (tramo.getLastUbication().getName() == oldName) {
        tramo.eliminarTramoDelArchivo(tramo.getName(), tramo.getInitialUbication().getX(), tramo.getInitialUbication().getY(), 
                                      tramo.getLastUbication().getX(), tramo.getLastUbication().getY());
                                      tramo.setLastUbication(Ubication(tramo.getLastUbication().getX(), tramo.getLastUbication().getY(), newName));
                                    tramo.guardar_en_archivo();
    }

    // Llamadas recursivas para recorrer el árbol
    updateUbicationNameRec(node->left, oldName, newName);
    updateUbicationNameRec(node->right, oldName, newName);
}

template <typename T>
double KD_Tree<T>::get_trafico_total(const std::string& hora, const std::string& route_name) const {
    double sumatorio_distancia_nivel_trafico = 0.0;
    double sumatorio_distancias = 0.0;

    // Función recursiva para recorrer el árbol y calcular los sumatorios
    std::function<void(Node<T>*)> calcularSumatorios = [&](Node<T>* node) {
        if (!node) return;

        const T& route = node->data;
        if (route.getName() == route_name) {
            double distancia = route.getDistance();
            sumatorio_distancias += distancia;

            // Calcular el nivel de tráfico en la hora especificada
            const std::vector<Trafic>& trafics = route.getTrafics();
            for (const auto& trafic : trafics) {
                if (trafic.getInitialHour() <= hora && hora <= trafic.getLastHour()) {
                    sumatorio_distancia_nivel_trafico += distancia * trafic.getLevel();
                    break;
                }
            }
        }
        calcularSumatorios(node->left);
        calcularSumatorios(node->right);
    };

    // Iniciar el cálculo desde la raíz
    calcularSumatorios(root);

    // Aplicar la fórmula para calcular el tráfico total
    if (sumatorio_distancias == 0.0) {
        return 0.0; // Evitar división por cero
    }
    return (sumatorio_distancia_nivel_trafico * 100) / (3 * sumatorio_distancias);
}
template <typename T>
std::vector<std::tuple<std::string, double>> KD_Tree<T>::get_trafico_por_horas(const std::string& route_name) const {
    std::vector<std::tuple<std::string, double>> trafico_por_horas;
    std::vector<std::string> horas = {
        "00:00:00", "01:00:00", "02:00:00", "03:00:00", "04:00:00", "05:00:00",
        "06:00:00", "07:00:00", "08:00:00", "09:00:00", "10:00:00", "11:00:00",
        "12:00:00", "13:00:00", "14:00:00", "15:00:00", "16:00:00", "17:00:00",
        "18:00:00", "19:00:00", "20:00:00", "21:00:00", "22:00:00", "23:00:00"
    };

    for (const auto& hora : horas) {
        double trafico = get_trafico_total(hora, route_name);
        trafico_por_horas.emplace_back(hora, trafico);
    }

    return trafico_por_horas;
}
#include <filesystem>

template <typename T>
void KD_Tree<T>::guardar_trafico_por_horas(const std::string& route_name) const {
    // Crear la carpeta output si no existe
    std::filesystem::create_directory("output");

    // Abrir el archivo en la carpeta output
    std::ofstream file("output/tuplas.txt");
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo tuplas.txt para escribir." << std::endl;
        return;
    }

    // Obtener el tráfico por horas
    auto trafico_por_horas = get_trafico_por_horas(route_name);

    // Escribir las tuplas en el archivo
    for (const auto& [hora, trafico] : trafico_por_horas) {
        file << hora << ", " << trafico << "\n";
    }

    file.close();
}

template <typename T>
void KD_Tree<T>::guardar_trafico_todas_rutas() const {
    // Crear la carpeta output si no existe
    std::filesystem::create_directory("output");

    // Abrir el archivo en la carpeta output
    std::ofstream file("output/todas_rutas_tuplas.txt");
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo todas_rutas_tuplas.txt para escribir." << std::endl;
        return;
    }

    // Usar un set para evitar duplicados
    std::set<std::string> rutasProcesadas;

    // Función recursiva para recorrer el árbol y escribir las tuplas en el archivo
    std::function<void(Node<T>*)> recorrerYGuardar = [&](Node<T>* node) {
        if (!node) return;

        const T& ruta = node->data;
        if (rutasProcesadas.find(ruta.getName()) == rutasProcesadas.end()) {
            rutasProcesadas.insert(ruta.getName());
            auto trafico_por_horas = get_trafico_por_horas(ruta.getName());
            for (const auto& [hora, trafico] : trafico_por_horas) {
                file << ruta.getName() << ", " << hora << ", " << trafico << "\n";
            }
        }

        recorrerYGuardar(node->left);
        recorrerYGuardar(node->right);
    };

    // Iniciar el recorrido desde la raíz
    recorrerYGuardar(root);

    file.close();
}