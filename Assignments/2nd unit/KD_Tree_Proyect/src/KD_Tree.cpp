#include "../include/Propietario.h"
#include "../include/Coche.h"
#include "../include/Nodo.h"
#include "../include/Celda.h"
#include "../include/KD_Tree.h"
#include "../include/Time_utils.h"
#include <memory>
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

template <typename T>
KD_Tree<T>::KD_Tree() : root(nullptr) {}

template <typename T>
std::shared_ptr<Nodo<T>> KD_Tree<T>::insertRec(std::shared_ptr<Nodo<T>> node, const T& data, const std::array<float, 2>& coords, int depth) {
    if (node == nullptr) {
        return std::make_shared<Nodo<T>>(data, coords[0], coords[1]);
    }

    int axis = depth % 2;
    if (coords[axis] < node->coords[axis]) {
        node->left = insertRec(node->left, data, coords, depth + 1);
    } else {
        node->right = insertRec(node->right, data, coords, depth + 1);
    }

    return node;
}

template <typename T>
void KD_Tree<T>::insert(const T& data, float x, float y) {
    root = insertRec(root, data, {x, y}, 0);
}

template <typename T>
void KD_Tree<T>::inOrderRec(std::shared_ptr<Nodo<T>> node) const {
    if (node != nullptr) {
        inOrderRec(node->left);
        std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ") -> " << node->data << std::endl;
        inOrderRec(node->right);
    }
}

template <typename T>
void KD_Tree<T>::inOrder() const {
    inOrderRec(root);
}
template <typename T>
void KD_Tree<T>::loadPropietarios(const std::string& fileName) {
    std::ifstream file(fileName);
    float x,y;
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return; 
    }
    std::string line;
    std::cout << "Procesando propietarios.txt..." << std::endl;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string nombre, apellido, cedula, correo;
        std::string placa;
        std::vector<std::string> placas;

        if (std::getline(stream, nombre, ',') &&
            std::getline(stream, apellido, ',') &&
            std::getline(stream, cedula, ',') &&
            std::getline(stream, correo, ',')) {
            while (std::getline(stream, placa, ',')) {
                placas.push_back(placa);
            }
            x= convertirStringAFloat(nombre);
            cout<<nombre<<endl;
            cout<<x<<endl;
            y= convertirStringAFloat(apellido);
            cout<<apellido<<endl;
            cout<<y<<endl;
            Propietario propietario(nombre, apellido, cedula, correo, placas);
            insert(propietario, x, y); 
        }
    }

    file.close();
}

template <typename T>
void KD_Tree<T>::loadAutosHistorial(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando autos_historial.txt..." << std::endl;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string x, y, placa, modelo, color, marca, horaIngresoStr, horaSalidaStr;

        if (std::getline(stream, x, ',') &&
            std::getline(stream, y, ',') &&
            std::getline(stream, placa, ',') &&
            std::getline(stream, modelo, ',') &&
            std::getline(stream, color, ',') &&
            std::getline(stream, marca, ',') &&
            std::getline(stream, horaIngresoStr, ',') &&
            std::getline(stream, horaSalidaStr, ','))  {

            std::chrono::system_clock::time_point horaIngreso, horaSalida;

            if (horaIngresoStr != "N/A") {
                struct std::tm tm = {};
                std::istringstream ss(horaIngresoStr);
                ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
                horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            } else {
                horaIngreso = std::chrono::system_clock::now();
            }
            if (horaSalidaStr != "N/A") {
                struct std::tm tm = {};
                std::istringstream ss(horaSalidaStr);
                ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
                horaSalida = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            } else {
                horaSalida = definirFechaImprobable();
            }
            Coche coche(placa, modelo, color, marca, horaIngreso, horaSalida);
            Celda celda(std::stof(x), std::stof(y), coche, horaIngreso, horaSalida);
            insert(celda, std::stof(x), std::stof(y));
        }
    }

    file.close();
}

template <typename T>
void KD_Tree<T>::loadAutos(const std::string& fileName) {
    std::ifstream file(fileName);
    float x,y;
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string line;
    std::cout << "Procesando autos.txt..." << std::endl;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string placa, modelo, color, marca, horaIngresoStr, horaSalidaStr;

        if (std::getline(stream, placa, ',') &&
            std::getline(stream, modelo, ',') &&
            std::getline(stream, color, ',') &&
            std::getline(stream, marca, ',') &&
            std::getline(stream, horaIngresoStr, ',') &&
            std::getline(stream, horaSalidaStr, ',')) {

            std::chrono::system_clock::time_point horaIngreso, horaSalida;
            struct std::tm tm;

            std::istringstream ss(horaIngresoStr);
            ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
            horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));

            if (horaSalidaStr != "N/A") {
                std::istringstream ss(horaSalidaStr);
                ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
                horaSalida = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            } else {
                horaSalida = definirFechaImprobable();
            }
            x= convertirStringAFloat(placa);
            y= convertirStringAFloat(horaIngresoStr);
            Coche nuevoAuto(placa, modelo, color, marca, horaIngreso, horaSalida);
            insert(nuevoAuto, x, y);
        }
    }

    file.close();
}
template <typename T>
float KD_Tree<T>::convertirStringAFloat(const std::string &str) {
    if (str.empty()) {
        // Retornamos un valor especial si el string está vacío.
        return 0.0f; 
    }

    // Tomamos el valor ASCII de la primera letra del string y lo convertimos a float.
    float resultado = static_cast<float>(str[0]);

    return resultado;
}

template <typename T>
void KD_Tree<T>::imprimir_propietarios() const {
    // Llamamos a la función recursiva para recorrer el árbol
    imprimirRec(root);
}

template <typename T>
void KD_Tree<T>::imprimirRec(std::shared_ptr<Nodo<T>> node) const {
    if (!node) {
        return;
    }
        // Primero recorrer la izquierda
        imprimirRec(node->left);

        // Verificar si el propietario tiene un nombre no vacío
        if (!node->data.getNombre().empty()) {
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
            // Acceder a los miembros de 'Propietario' mediante los getters
            std::cout << "Nombre: " << node->data.getNombre() << std::endl;
            std::cout << "Apellido: " << node->data.getApellido() << std::endl;
            std::cout << "Cédula: " << node->data.getCedula() << std::endl;
            std::cout << "Correo: " << node->data.getCorreo() << std::endl;

            // Obtener las placas del propietario
            std::vector<std::string> placas = node->data.getPlacas();

            // Imprimir las placas
            std::cout << "Placas: ";
            if (!placas.empty()) {
                for (const auto& placa : placas) {
                    std::cout << placa << " ";
                }
                std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
            } else {
                std::cout << "No tiene placas registradas.";
                std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
            }
            std::cout << std::endl;
        }

        // Luego recorrer la derecha
        imprimirRec(node->right);
    
}
template <typename T>
T* KD_Tree<T>::buscarPorCedulaRec(std::shared_ptr<Nodo<T>> node, const std::string& cedula) const {
    if (node == nullptr) {
        return nullptr; // No se encontró la cédula
    }

    // Verificar si la cédula coincide con la del nodo actual
    if (node->data.getCedula() == cedula) {
        // Imprimir los datos del propietario
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Propietario encontrado: " << std::endl;
        std::cout << "Nombre: " << node->data.getNombre() << std::endl;
        std::cout << "Apellido: " << node->data.getApellido() << std::endl;
        std::cout << "Cédula: " << node->data.getCedula() << std::endl;
        std::cout << "Correo: " << node->data.getCorreo() << std::endl;

        // Imprimir las placas del propietario
        std::vector<std::string> placas = node->data.getPlacas();
        if (!placas.empty()) {
            std::cout << "Placas del propietario: ";
            for (const auto& placa : placas) {
                std::cout << placa << " ";
            }
            std::cout << std::endl;
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        } else {
            std::cout << "No tiene placas registradas." << std::endl;
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        }

        return &(node->data);  // Ahora retorna un puntero al propietario
    }

    // Continuar la búsqueda en los subárboles
    T* encontradoIzquierda = buscarPorCedulaRec(node->left, cedula);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    return buscarPorCedulaRec(node->right, cedula);
}

// Versión pública sin cambios drásticos
template <typename T>
T* KD_Tree<T>::buscarPorCedula(const std::string& cedula) const {
    return buscarPorCedulaRec(root, cedula);
}


template <typename T>
bool KD_Tree<T>::eliminarPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string &cedula, const std::string &placa) {
    if (node == nullptr) {
        return false; // Si el nodo es nulo, no se encontró la cédula
    }

    if (node->data.getCedula() == cedula) {
        // Intentar eliminar la placa
        node->data.eliminarPlaca(placa);
        return true; // Se encontró la cédula y se intentó eliminar la placa
    }

    // Recursión en los subárboles izquierdo y derecho
    bool eliminadoEnIzquierda = eliminarPlacaRec(node->left, cedula, placa);
    bool eliminadoEnDerecha = eliminarPlacaRec(node->right, cedula, placa);

    return eliminadoEnIzquierda || eliminadoEnDerecha; // Retorna true si se eliminó en algún subárbol
}

template <typename T>
void KD_Tree<T>::eliminarPlacaPorCedula(const std::string& cedula, const std::string& placa) {
    // Buscar el nodo del propietario usando la cédula
    std::shared_ptr<Nodo<T>> propietario = buscarNodoPorCedula(root, cedula);

    if (!propietario) {
        // Caso: No se encontró el propietario
        std::cout << "Propietario con cédula " << cedula << " no encontrado." << std::endl;
        return;
    }

    // Caso: El propietario fue encontrado
    auto& placas = propietario->data.getPlacas();
    if (placas.empty()) {
        // Caso: El propietario no tiene placas registradas
        std::cout << "El propietario con cédula " << cedula << " no tiene placas registradas." << std::endl;
        return;
    }

    // Buscar la placa manualmente
    bool placaEliminada = false;
    for (auto it = placas.begin(); it != placas.end(); ++it) {
        if (*it == placa) {
            placas.erase(it); // Eliminar la placa
            placaEliminada = true;
            std::cout << "Placa " << placa << " eliminada del propietario con cédula " << cedula << "." << std::endl;
            break;
        }
    }

    if (!placaEliminada) {
        std::cout << "La placa " << placa << " no está registrada para el propietario con cédula " << cedula << "." << std::endl;
    }
    guardarPropietariosEnArchivo("output//propietarios.txt");
}

template <typename T>
std::shared_ptr<Nodo<T>> KD_Tree<T>::buscarNodoPorCedula(std::shared_ptr<Nodo<T>> node, const std::string& cedula) const {
    if (node == nullptr) {
        return nullptr;
    }

    // Comparar la cédula con la del nodo actual
    if (node->data.getCedula() == cedula) {
        return node;
    }

    // Buscar en los subárboles
    if (cedula < node->data.getCedula()) {
        return buscarNodoPorCedula(node->left, cedula);
    } else {
        return buscarNodoPorCedula(node->right, cedula);
    }
}

template <typename T>
void KD_Tree<T>::guardarPropietariosEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar los propietarios." << std::endl;
        return;
    }

    // Guardar los propietarios en el archivo
    guardarPropietariosEnMemoria(root, archivo);

    archivo.close();
}

template <typename T>
void KD_Tree<T>::guardarPropietariosEnMemoria(std::shared_ptr<Nodo<T>> node, std::ofstream& archivo) const {
    if (node == nullptr) {
        return;
    }

    // Guardar el propietario del nodo actual
    node->data.guardar_en_archivo();

    // Llamar recursivamente para los subárboles
    guardarPropietariosEnMemoria(node->left, archivo);
    guardarPropietariosEnMemoria(node->right, archivo);
}
template <typename T>
T* KD_Tree<T>::buscarPorPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const {
    if (node == nullptr) {
        return nullptr; // No se encontró la placa
    }

    // Verificar si la placa está en la lista de placas del nodo actual
    const auto& placas = node->data.getPlacas();
    if (std::find(placas.begin(), placas.end(), placa) != placas.end()) {
        // Imprimir los datos del propietario
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Propietario encontrado: " << std::endl;
        std::cout << "Nombre: " << node->data.getNombre() << std::endl;
        std::cout << "Apellido: " << node->data.getApellido() << std::endl;
        std::cout << "Cédula: " << node->data.getCedula() << std::endl;
        std::cout << "Correo: " << node->data.getCorreo() << std::endl;

        // Imprimir las placas del propietario
        if (!placas.empty()) {
            std::cout << "Placas del propietario: ";
            for (const auto& p : placas) {
                std::cout << p << " ";
                }
            std::cout << std::endl;
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        } else {
            std::cout << "No tiene placas registradas." << std::endl;
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        }

        return &(node->data);  // Retorna un puntero al propietario
    }

    // Continuar la búsqueda en los subárboles
    T* encontradoIzquierda = buscarPorPlacaRec(node->left, placa);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    return buscarPorPlacaRec(node->right, placa);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlaca(const std::string& placa) const {
    return buscarPorPlacaRec(root, placa);
}
template <typename T>
T* KD_Tree<T>::buscarPorPlacaEnCochesRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const {
    if (node == nullptr) {
        return nullptr; // No se encontró la placa
    }

    // Verificar si la placa coincide con la del nodo actual
    if (node->data.getPlaca() == placa) {
        // Imprimir los datos del coche
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Marca: " << node->data.getMarca() << std::endl;
        std::cout << "Modelo: " << node->data.getModelo() << std::endl;
        std::cout << "Color: " << node->data.getColor() << std::endl;
        std::cout << "Placa: " << node->data.getPlaca() << std::endl;
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        return &(node->data);  // Retorna un puntero al coche
    }

    // Continuar la búsqueda en los subárboles
    T* encontradoIzquierda = buscarPorPlacaEnCochesRec(node->left, placa);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    return buscarPorPlacaEnCochesRec(node->right, placa);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaEnCoches(const std::string& placa) const {
    return buscarPorPlacaEnCochesRec(root, placa);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaEnCeldaRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const {
    if (node == nullptr) {
        return nullptr; // No se encontró la placa
    }

    // Verificar si la placa del coche en la celda coincide
    if (node->data.getCoche().getPlaca() == placa) {
        // Imprimir los datos de la celda y del coche
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Celda encontrada: " << std::endl;
        std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;
        std::cout << "Hora de ingreso: " 
                  << std::chrono::system_clock::to_time_t(node->data.getHoraIngreso()) << std::endl;
        std::cout << "Hora de salida: " 
                  << std::chrono::system_clock::to_time_t(node->data.getHoraSalida()) << std::endl;

        const Coche& coche = node->data.getCoche();
        std::cout << "Datos del coche: " << std::endl;
        std::cout << "Marca: " << coche.getMarca() << std::endl;
        std::cout << "Modelo: " << coche.getModelo() << std::endl;
        std::cout << "Color: " << coche.getColor() << std::endl;
        std::cout << "Placa: " << coche.getPlaca() << std::endl;
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;

        return &(node->data); // Retorna un puntero a la celda
    }

    // Continuar la búsqueda en los subárboles
    T* encontradoIzquierda = buscarPorPlacaEnCeldaRec(node->left, placa);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    return buscarPorPlacaEnCeldaRec(node->right, placa);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaEnCelda(const std::string& placa) const {
    return buscarPorPlacaEnCeldaRec(root, placa);
}

template <typename T>
void KD_Tree<T>::imprimirCeldasRec(const std::shared_ptr<Nodo<T>>& node) const {
    if (!node) {
        return;
    }
    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    // Llamada recursiva al subárbol izquierdo
    imprimirCeldasRec(node->left);

    // Solo imprimir si la hora de salida es igual a la fecha improbable
    if (node->data.getHoraSalida() == fecha_improbable) {
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;

        auto horaIngreso = std::chrono::system_clock::to_time_t(node->data.getHoraIngreso());
        auto horaSalida = std::chrono::system_clock::to_time_t(node->data.getHoraSalida());

        std::cout << "Hora de ingreso: " << std::put_time(std::localtime(&horaIngreso), "%a %b %d %H:%M:%S %Y") << std::endl;
        std::cout << "Hora de salida: " << std::put_time(std::localtime(&horaSalida), "%a %b %d %H:%M:%S %Y") << std::endl;

        const Coche& coche = node->data.getCoche();
        std::cout << "Datos del coche: " << std::endl;
        std::cout << "Marca: " << coche.getMarca() << std::endl;
        std::cout << "Modelo: " << coche.getModelo() << std::endl;
        std::cout << "Color: " << coche.getColor() << std::endl;
        std::cout << "Placa: " << coche.getPlaca() << std::endl;
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
    }

    // Llamada recursiva al subárbol derecho
    imprimirCeldasRec(node->right);
}

template <typename T>
void KD_Tree<T>::imprimirCeldas() const {
    imprimirCeldasRec(root);
}

template <typename T>
void KD_Tree<T>::imprimirNodosRec(const std::shared_ptr<Nodo<T>>& node) const {
    if (!node) {
        return;
    }

    imprimirNodosRec(node->left);
    std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
    std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;

    auto horaIngreso = std::chrono::system_clock::to_time_t(node->data.getHoraIngreso());
    auto horaSalida = std::chrono::system_clock::to_time_t(node->data.getHoraSalida());

    std::cout << "Hora de ingreso: " << std::put_time(std::localtime(&horaIngreso), "%a %b %d %H:%M:%S %Y") << std::endl;
    std::cout << "Hora de salida: " << std::put_time(std::localtime(&horaSalida), "%a %b %d %H:%M:%S %Y") << std::endl;

    const Coche& coche = node->data.getCoche();
    std::cout << "Datos del coche: " << std::endl;
    std::cout << "Marca: " << coche.getMarca() << std::endl;
    std::cout << "Modelo: " << coche.getModelo() << std::endl;
    std::cout << "Color: " << coche.getColor() << std::endl;
    std::cout << "Placa: " << coche.getPlaca() << std::endl;
    std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;

    imprimirNodosRec(node->right);
}

template <typename T>
void KD_Tree<T>::imprimirNodos() const {
    imprimirNodosRec(root);
}

template <typename T>
void KD_Tree<T>::buscarPorFechaImprobableRec(const std::shared_ptr<Nodo<T>>& node, const std::string& placa) const {
    if (node == nullptr) {
        return;
    }
    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    // Llamada recursiva al subárbol izquierdo
    buscarPorFechaImprobableRec(node->left, placa);

    // Solo imprimir si la hora de salida es igual a la fecha improbable y la placa coincide
    if (node->data.getHoraSalida() == fecha_improbable && node->data.getCoche().getPlaca() == placa) {
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Celda encontrada: " << std::endl;
        std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;

        auto horaIngreso = std::chrono::system_clock::to_time_t(node->data.getHoraIngreso());
        auto horaSalida = std::chrono::system_clock::to_time_t(node->data.getHoraSalida());

        std::cout << "Hora de ingreso: " << std::put_time(std::localtime(&horaIngreso), "%a %b %d %H:%M:%S %Y") << std::endl;
        std::cout << "Hora de salida: " << std::put_time(std::localtime(&horaSalida), "%a %b %d %H:%M:%S %Y") << std::endl;

        const Coche& coche = node->data.getCoche();
        std::cout << "Datos del coche: " << std::endl;
        std::cout << "Marca: " << coche.getMarca() << std::endl;
        std::cout << "Modelo: " << coche.getModelo() << std::endl;
        std::cout << "Color: " << coche.getColor() << std::endl;
        std::cout << "Placa: " << coche.getPlaca() << std::endl;
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
    }

    // Llamada recursiva al subárbol derecho
    buscarPorFechaImprobableRec(node->right, placa);
}

template <typename T>
void KD_Tree<T>::buscarPorFechaImprobable(const std::string& placa) const {
    buscarPorFechaImprobableRec(root, placa);
}
//--------------------------------------------------------------------------------------------------------
// Buscar por Marca
template <typename T>
void KD_Tree<T>::buscarPorMarcaRec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca) const {
    if (node == nullptr) return;

    if (node->data.getCoche().getMarca() == marca) {
        imprimirCelda(node);
    }

    buscarPorMarcaRec(node->left, marca);
    buscarPorMarcaRec(node->right, marca);
}

template <typename T>
void KD_Tree<T>::buscarPorMarca(const std::string& marca) const {
    buscarPorMarcaRec(root, marca);
}

// Buscar por Modelo
template <typename T>
void KD_Tree<T>::buscarPorModeloRec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo) const {
    if (node == nullptr) return;

    if (node->data.getCoche().getModelo() == modelo) {
        imprimirCelda(node);
    }

    buscarPorModeloRec(node->left, modelo);
    buscarPorModeloRec(node->right, modelo);
}

template <typename T>
void KD_Tree<T>::buscarPorModelo(const std::string& modelo) const {
    buscarPorModeloRec(root, modelo);
}

// Buscar por Color
template <typename T>
void KD_Tree<T>::buscarPorColorRec(const std::shared_ptr<Nodo<T>>& node, const std::string& color) const {
    if (node == nullptr) return;

    if (node->data.getCoche().getColor() == color) {
        imprimirCelda(node);
    }

    buscarPorColorRec(node->left, color);
    buscarPorColorRec(node->right, color);
}

template <typename T>
void KD_Tree<T>::buscarPorColor(const std::string& color) const {
    buscarPorColorRec(root, color);
}

template <typename T>
void KD_Tree<T>::buscarPorFechaRec(const std::shared_ptr<Nodo<T>>& node, 
                                   const std::chrono::system_clock::time_point& fechaInicio, 
                                   const std::chrono::system_clock::time_point& fechaFin) const {
    if (node == nullptr) return;

    auto horaSalida = node->data.getHoraSalida();

    // Comparar si la fecha de salida está en el rango
    if (horaSalida >= fechaInicio && horaSalida <= fechaFin) {
        imprimirCelda(node);
    }

    buscarPorFechaRec(node->left, fechaInicio, fechaFin);
    buscarPorFechaRec(node->right, fechaInicio, fechaFin);
}

template <typename T>
void KD_Tree<T>::buscarPorFecha(const std::string& fechaInicioStr, const std::string& fechaFinStr) const {
    auto fechaInicio = convertirStringATimePoint(fechaInicioStr);
    auto fechaFin = convertirStringATimePoint(fechaFinStr);
    buscarPorFechaRec(root, fechaInicio, fechaFin);
}

// Función recursiva para buscar por rango de hora (con segundos)
template <typename T>
void KD_Tree<T>::buscarPorHoraRec(const std::shared_ptr<Nodo<T>>& node, 
                                  const std::chrono::system_clock::time_point& horaInicio, 
                                  const std::chrono::system_clock::time_point& horaFin) const {
    if (node == nullptr) return;

    auto horaSalida = node->data.getHoraSalida();

    // Comparar si la hora de salida está dentro del rango
    if (horaSalida >= horaInicio && horaSalida <= horaFin) {
        imprimirCelda(node);
    }

    // Continuar la búsqueda en ambos subárboles
    buscarPorHoraRec(node->left, horaInicio, horaFin);
    buscarPorHoraRec(node->right, horaInicio, horaFin);
}

// Función pública para realizar la búsqueda
template <typename T>
void KD_Tree<T>::buscarPorHora(const std::string& horaInicioStr, const std::string& horaFinStr) const {
    auto horaInicio = convertirStringATimePointHora(horaInicioStr);
    auto horaFin = convertirStringATimePointHora(horaFinStr);
    buscarPorHoraRec(root, horaInicio, horaFin);
}

template <typename T>
void KD_Tree<T>::imprimirCelda(const std::shared_ptr<Nodo<T>>& node) const {
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Celda encontrada: " << std::endl;
    std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;
    
    auto horaIngreso = std::chrono::system_clock::to_time_t(node->data.getHoraIngreso());
    auto horaSalida = std::chrono::system_clock::to_time_t(node->data.getHoraSalida());

    std::cout << "Hora de ingreso: " << std::put_time(std::localtime(&horaIngreso), "%a %b %d %H:%M:%S %Y") << std::endl;
    std::cout << "Hora de salida: " << std::put_time(std::localtime(&horaSalida), "%a %b %d %H:%M:%S %Y") << std::endl;

    const Coche& coche = node->data.getCoche();
    std::cout << "Marca: " << coche.getMarca() << std::endl;
    std::cout << "Modelo: " << coche.getModelo() << std::endl;
    std::cout << "Color: " << coche.getColor() << std::endl;
    std::cout << "Placa: " << coche.getPlaca() << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}

//---------------------------------------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::buscar_por_marca_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca) const {
    if (node == nullptr) return;

    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    // Verificar si la marca y la fecha improbable coinciden
    if (node->data.getCoche().getMarca() == marca && node->data.getHoraSalida() == fecha_improbable) {
        // Imprimir la celda si ambos coinciden
        imprimirCelda(node);
    }

    // Llamadas recursivas en los subárboles
    buscar_por_marca_parqueadero_rec(node->left, marca);
    buscar_por_marca_parqueadero_rec(node->right, marca);
}

template <typename T>
void KD_Tree<T>::buscar_por_marca_parqueadero(const std::string& marca) const {
    buscar_por_marca_parqueadero_rec(root, marca);
}

template <typename T>
void KD_Tree<T>::buscar_por_modelo_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo) const {
    if (node == nullptr) return;
    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    // Verificar si el modelo y la fecha improbable coinciden
    if (node->data.getCoche().getModelo() == modelo && node->data.getHoraSalida() == fecha_improbable) {
        // Imprimir la celda si ambos coinciden
        imprimirCelda(node);
    }

    // Llamadas recursivas en los subárboles
    buscar_por_modelo_parqueadero_rec(node->left, modelo);
    buscar_por_modelo_parqueadero_rec(node->right, modelo);
}

template <typename T>
void KD_Tree<T>::buscar_por_modelo_parqueadero(const std::string& modelo) const {
    buscar_por_modelo_parqueadero_rec(root, modelo);
}

template <typename T>
void KD_Tree<T>::buscar_por_color_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& color) const {
    if (node == nullptr) return;
// Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    // Verificar si el modelo y la fecha improbable coinciden
    if (node->data.getCoche().getColor() == color && node->data.getHoraSalida() == fecha_improbable) {
        // Imprimir la celda si ambos coinciden
        imprimirCelda(node);
    }

    // Llamadas recursivas en los subárboles
    buscar_por_color_parqueadero_rec(node->left, color);
    buscar_por_color_parqueadero_rec(node->right, color);
}

template <typename T>
void KD_Tree<T>::buscar_por_color_parqueadero(const std::string& color) const {
    buscar_por_color_parqueadero_rec(root, color);
}

template <typename T>
void KD_Tree<T>::buscar_por_fecha_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, 
                                                  const std::chrono::system_clock::time_point& fechaInicio, 
                                                  const std::chrono::system_clock::time_point& fechaFin) const {
    if (node == nullptr) return;
    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaSalida = node->data.getHoraSalida();

    // Comparar si la fecha de salida está en el rango y si la hora de salida es la fecha improbable
    if (horaSalida >= fechaInicio && horaSalida <= fechaFin && horaSalida == fecha_improbable) {
        imprimirCelda(node);
    }

    // Llamadas recursivas en los subárboles
    buscar_por_fecha_parqueadero_rec(node->left, fechaInicio, fechaFin);
    buscar_por_fecha_parqueadero_rec(node->right, fechaInicio, fechaFin);
}

template <typename T>
void KD_Tree<T>::buscar_por_fecha_parqueadero(const std::string& fechaInicioStr, const std::string& fechaFinStr) const {
    auto fechaInicio = convertirStringATimePoint(fechaInicioStr);
    auto fechaFin = convertirStringATimePoint(fechaFinStr);
    buscar_por_fecha_parqueadero_rec(root, fechaInicio, fechaFin);
}

template <typename T>
void KD_Tree<T>::buscar_por_hora_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, 
                                                 const std::chrono::system_clock::time_point& horaInicio, 
                                                 const std::chrono::system_clock::time_point& horaFin) const {
    if (node == nullptr) return;
    // Obtener la fecha improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaSalida = node->data.getHoraSalida();

    // Comparar si la hora de salida está dentro del rango y si la hora de salida es la fecha improbable
    if (horaSalida >= horaInicio && horaSalida <= horaFin && horaSalida == fecha_improbable) {
        imprimirCelda(node);
    }

    // Llamadas recursivas en los subárboles
    buscar_por_hora_parqueadero_rec(node->left, horaInicio, horaFin);
    buscar_por_hora_parqueadero_rec(node->right, horaInicio, horaFin);
}

template <typename T>
void KD_Tree<T>::buscar_por_hora_parqueadero(const std::string& horaInicioStr, const std::string& horaFinStr) const {
    auto horaInicio = convertirStringATimePointHora(horaInicioStr);
    auto horaFin = convertirStringATimePointHora(horaFinStr);
    buscar_por_hora_parqueadero_rec(root, horaInicio, horaFin);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaYFechaImprobableRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const {
    if (node == nullptr) {
        return nullptr; // Nodo no encontrado
    }

    // Llamar a definirFechaImprobable desde time_utils.h
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    // Verificar si la placa y la fecha de salida coinciden
    if (node->data.getCoche().getPlaca() == placa && node->data.getHoraSalida() == fecha_improbable) {
        // Imprimir los datos de la celda y del coche
        std::cout << "--------------------------------------------------------------------------------------" << std::endl;
        std::cout << "Celda encontrada: " << std::endl;
        std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;
        std::cout << "Hora de ingreso: "
                  << std::chrono::system_clock::to_time_t(node->data.getHoraIngreso()) << std::endl;
        std::cout << "Hora de salida: "
                  << std::chrono::system_clock::to_time_t(node->data.getHoraSalida()) << std::endl;

        const Coche& coche = node->data.getCoche();
        std::cout << "Datos del coche: " << std::endl;
        std::cout << "Marca: " << coche.getMarca() << std::endl;
        std::cout << "Modelo: " << coche.getModelo() << std::endl;
        std::cout << "Color: " << coche.getColor() << std::endl;
        std::cout << "Placa: " << coche.getPlaca() << std::endl;
        std::cout << "--------------------------------------------------------------------------------------" << std::endl;

        return &(node->data); // Retorna un puntero a la celda
    }

    // Continuar la búsqueda en los subárboles
    T* encontradoIzquierda = buscarPorPlacaYFechaImprobableRec(node->left, placa);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }

    return buscarPorPlacaYFechaImprobableRec(node->right, placa);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaYFechaImprobable(const std::string& placa) const {
    return buscarPorPlacaYFechaImprobableRec(root, placa);
}
