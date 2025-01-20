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
#include <functional>

template <typename T>
KD_Tree<T>::KD_Tree() : root(nullptr) {}

template <typename T>
KD_Tree<T>::~KD_Tree() {
    clear(root);
    root.reset(); 
}
template <typename T>
void KD_Tree<T>::clear(std::shared_ptr<Nodo<T>> node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    node.reset(); 
}

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
            y= convertirStringAFloat(apellido);
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
            Coche coche(placa, modelo, color, marca);
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
        std::string placa, modelo, color, marca;
        if (std::getline(stream, placa, ',') &&
            std::getline(stream, modelo, ',') &&
            std::getline(stream, color, ',') &&
            std::getline(stream, marca, ',')) {
            
            x= convertirStringAFloat(placa);
            y= convertirStringAFloat(placa);
            Coche nuevoAuto(placa, modelo, color, marca);
            insert(nuevoAuto, x, y);
        }
    }
    file.close();
}

template <typename T>
float KD_Tree<T>::convertirStringAFloat(const std::string &str) {
    if (str.empty()) {
        return 0.0f; 
    }
    float resultado = static_cast<float>(str[0]);
    return resultado;
}

template <typename T>
void KD_Tree<T>::imprimir_propietarios() const {
    imprimir_propietarios_Rec(root);
}

template <typename T>
void KD_Tree<T>::imprimir_propietarios_Rec(std::shared_ptr<Nodo<T>> node) const {
    if (!node) {
        return;
    }
        imprimir_propietarios_Rec(node->left);
        imprimir_propietario(node);
        imprimir_propietarios_Rec(node->right);
}

template <typename T>
T* KD_Tree<T>::buscarPorCedulaRec(std::shared_ptr<Nodo<T>> node, const std::string& cedula) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data.getCedula() == cedula) {
        std::cout << "Propietario encontrado: " << std::endl;
        imprimir_propietario(node);
        return &(node->data); 
    }
    T* encontradoIzquierda = buscarPorCedulaRec(node->left, cedula);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }
    return buscarPorCedulaRec(node->right, cedula);
}

template <typename T>
T* KD_Tree<T>::buscarPorCedula(const std::string& cedula) const {
    return buscarPorCedulaRec(root, cedula);
}

template <typename T>
bool KD_Tree<T>::eliminarPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string &cedula, const std::string &placa) {
    if (node == nullptr) {
        return false;
    }
    if (node->data.getCedula() == cedula) {
        node->data.eliminarPlaca(placa);
        return true; 
    }
    bool eliminadoEnIzquierda = eliminarPlacaRec(node->left, cedula, placa);
    bool eliminadoEnDerecha = eliminarPlacaRec(node->right, cedula, placa);
    return eliminadoEnIzquierda || eliminadoEnDerecha;
}

template <typename T>
void KD_Tree<T>::eliminarPlacaPorCedula(const std::string& cedula, const std::string& placa) {
    std::shared_ptr<Nodo<T>> propietario = buscarNodoPorCedula(root, cedula);
    if (!propietario) {
        std::cout << "Propietario con cédula " << cedula << " no encontrado." << std::endl;
        return;
    }
    auto& placas = propietario->data.getPlacas();
    if (placas.empty()) {
        std::cout << "El propietario con cédula " << cedula << " no tiene placas registradas." << std::endl;
        return;
    }
    bool placaEliminada = false;
    for (auto it = placas.begin(); it != placas.end(); ++it) {
        if (*it == placa) {
            placas.erase(it); 
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
    if (node->data.getCedula() == cedula) {
        return node;
    }
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
    guardarPropietariosEnMemoria(root, archivo);
    archivo.close();
}

template <typename T>
void KD_Tree<T>::guardarPropietariosEnMemoria(std::shared_ptr<Nodo<T>> node, std::ofstream& archivo) const {
    if (node == nullptr) {
        return;
    }
    node->data.guardar_en_archivo();
    guardarPropietariosEnMemoria(node->left, archivo);
    guardarPropietariosEnMemoria(node->right, archivo);
}

template <typename T>
T* KD_Tree<T>::buscarPorPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const {
    if (node == nullptr) {
        return nullptr; 
    }
    const auto& placas = node->data.getPlacas();
    if (std::find(placas.begin(), placas.end(), placa) != placas.end()) {
        std::cout << "Propietario encontrado: " << std::endl;
        imprimir_propietario(node);
        return &(node->data); 
    }
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
        return nullptr; 
    }
    if (node->data.getPlaca() == placa) {
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        std::cout << "Marca: " << node->data.getMarca() << std::endl;
        std::cout << "Modelo: " << node->data.getModelo() << std::endl;
        std::cout << "Color: " << node->data.getColor() << std::endl;
        std::cout << "Placa: " << node->data.getPlaca() << std::endl;
        std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
        return &(node->data); 
    }
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
        return nullptr; 
    }
    if (node->data.getCoche().getPlaca() == placa) {
        std::cout << "Celda encontrada: " << std::endl;
        imprimir_celda(node);
        return &(node->data); 
    }
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    imprimirCeldasRec(node->left);
    if (node->data.getHoraSalida() == fecha_improbable) {
    imprimir_celda(node);    
    }
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
    imprimir_celda(node);
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    buscarPorFechaImprobableRec(node->left, placa);
    if (node->data.getHoraSalida() == fecha_improbable && node->data.getCoche().getPlaca() == placa) {
        std::cout << "Celda encontrada: " << std::endl;
        imprimir_celda(node);
    }
    buscarPorFechaImprobableRec(node->right, placa);
}

template <typename T>
void KD_Tree<T>::buscarPorFechaImprobable(const std::string& placa) const {
    buscarPorFechaImprobableRec(root, placa);
}
//--------------------------------------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::buscarPorMarcaRec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getMarca() == marca) {
        imprimir_celda(node);
    }
    buscarPorMarcaRec(node->left, marca);
    buscarPorMarcaRec(node->right, marca);
}

template <typename T>
void KD_Tree<T>::buscarPorMarca(const std::string& marca) const {
    buscarPorMarcaRec(root, marca);
}

template <typename T>
void KD_Tree<T>::buscarPorModeloRec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getModelo() == modelo) {
        imprimir_celda(node);
    }
    buscarPorModeloRec(node->left, modelo);
    buscarPorModeloRec(node->right, modelo);
}

template <typename T>
void KD_Tree<T>::buscarPorModelo(const std::string& modelo) const {
    buscarPorModeloRec(root, modelo);
}

template <typename T>
void KD_Tree<T>::buscarPorColorRec(const std::shared_ptr<Nodo<T>>& node, const std::string& color) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getColor() == color) {
        imprimir_celda(node);
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
    if (horaSalida >= fechaInicio && horaSalida <= fechaFin) {
        imprimir_celda(node);
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
    if (horaSalida >= horaInicio && horaSalida <= horaFin) {
        imprimir_celda(node);
    }
    buscarPorHoraRec(node->left, horaInicio, horaFin);
    buscarPorHoraRec(node->right, horaInicio, horaFin);
}

template <typename T>
void KD_Tree<T>::buscarPorHora(const std::string& horaInicioStr, const std::string& horaFinStr) const {
    auto horaInicio = convertirStringATimePointHora(horaInicioStr);
    auto horaFin = convertirStringATimePointHora(horaFinStr);
    buscarPorHoraRec(root, horaInicio, horaFin);
}

//---------------------------------------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::buscar_por_marca_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getMarca() == marca && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
    }
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getModelo() == modelo && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
    }
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getColor() == color && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
    }
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaSalida = node->data.getHoraSalida();
    if (horaSalida >= fechaInicio && horaSalida <= fechaFin && horaSalida == fecha_improbable) {
        imprimir_celda(node);
    }
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
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaSalida = node->data.getHoraSalida();
    if (horaSalida >= horaInicio && horaSalida <= horaFin && horaSalida == fecha_improbable) {
        imprimir_celda(node);
    }
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
        return nullptr;
    }
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getPlaca() == placa && node->data.getHoraSalida() == fecha_improbable) {
        std::cout << "Celda encontrada: " << std::endl;
        imprimir_celda(node);
        return &(node->data);
    }
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
//------------------------------------------------------------------------
//Inmpresiones individuales
//------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::imprimir_propietario(std::shared_ptr<Nodo<T>> node) const{
          if (!node->data.getNombre().empty()) {
            std::cout <<"--------------------------------------------------------------------------------------"<< std::endl;
            std::cout << "Nombre: " << node->data.getNombre() << std::endl;
            std::cout << "Apellido: " << node->data.getApellido() << std::endl;
            std::cout << "Cédula: " << node->data.getCedula() << std::endl;
            std::cout << "Correo: " << node->data.getCorreo() << std::endl;
            std::vector<std::string> placas = node->data.getPlacas();
            std::cout << "Placas: ";
            if (!placas.empty()) {
                for (const auto& placa : placas) {
                    std::cout << placa << " ";
                }
                std::cout <<"\n--------------------------------------------------------------------------------------"<< std::endl;
            } else {
                std::cout << "No tiene placas registradas.";
                std::cout <<"\n--------------------------------------------------------------------------------------"<< std::endl;
            }
            std::cout << std::endl;
        }  
}

template <typename T>
void KD_Tree<T>::imprimir_celda(std::shared_ptr<Nodo<T>> node) const {
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
    std::cout << "Coordenadas: (" << node->data.getX() << ", " << node->data.getY() << ")" << std::endl;

    auto horaIngreso = node->data.getHoraIngreso(); 
    if (horaIngreso == std::chrono::system_clock::time_point{}) {
        std::cout << "Hora de ingreso: No registrada" << std::endl;
    } else {
        std::time_t tiempoIngreso = std::chrono::system_clock::to_time_t(horaIngreso);
        std::cout << "Hora de ingreso: " << std::put_time(std::localtime(&tiempoIngreso), "%a %b %d %H:%M:%S %Y") << std::endl;
    }

    auto horaSalida = node->data.getHoraSalida(); 
    if (horaSalida == std::chrono::system_clock::time_point{}) {
        std::cout << "Hora de salida: N/A (el coche todavía está en el parqueadero)" << std::endl;
    } else {
        std::time_t tiempoSalida = std::chrono::system_clock::to_time_t(horaSalida);
        std::cout << "Hora de salida: " << std::put_time(std::localtime(&tiempoSalida), "%a %b %d %H:%M:%S %Y") << std::endl;
    }

    const Coche& coche = node->data.getCoche();
    std::cout << "Datos del coche: " << std::endl;
    std::cout << "Marca: " << coche.getMarca() << std::endl;
    std::cout << "Modelo: " << coche.getModelo() << std::endl;
    std::cout << "Color: " << coche.getColor() << std::endl;
    std::cout << "Placa: " << coche.getPlaca() << std::endl;
    std::cout << "--------------------------------------------------------------------------------------" << std::endl;
}

template <typename T>
void KD_Tree<T>::imprimir_parqueadero(int size) const {
    std::vector<std::vector<bool>> ocupacion(size, std::vector<bool>(size, false));
    std::function<void(std::shared_ptr<Nodo<T>>)> marcarOcupacion;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    marcarOcupacion = [&](std::shared_ptr<Nodo<T>> node) {
        if (node) {
            if (node->data.getHoraSalida() == fecha_improbable) {
                int x = static_cast<int>(node->coords[0]);
                int y = static_cast<int>(node->coords[1]);
                if (x >= 0 && x < size && y >= 0 && y < size) {
                    ocupacion[x][y] = true;
                }
            }
            marcarOcupacion(node->left);
            marcarOcupacion(node->right);
        }
    };

    marcarOcupacion(root);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::ostringstream oss;
            oss << "(" << i << ";" << j << ")";
            std::string coord = oss.str();

            if (ocupacion[i][j]) {
                std::cout << "\033[31m" << coord << "\033[0m "; // Rojo para ocupado
            } else {
                std::cout << "\033[32m" << coord << "\033[0m "; // Verde para disponible
            }
        }
        std::cout << std::endl;
    }
    system("pause");
}

template <typename T>
bool KD_Tree<T>::buscar_coordenadas_en_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, float x, float y) const {
    if (node == nullptr) return true;

    // Definir la fecha improbable como referencia
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    // Verificar las coordenadas y la hora de salida
    if (node->coords[0] == x && node->coords[1] == y && node->data.getHoraSalida() == fecha_improbable) {
        return false; // Se encontró un nodo que cumple las condiciones
    }

    // Continuar la búsqueda en los subárboles izquierdo y derecho
    return buscar_coordenadas_en_parqueadero_rec(node->left, x, y) ||
           buscar_coordenadas_en_parqueadero_rec(node->right, x, y);
}

template <typename T>
bool KD_Tree<T>::buscar_coordenadas_en_parqueadero(float x, float y) const {
    return buscar_coordenadas_en_parqueadero_rec(root, x, y);
}
