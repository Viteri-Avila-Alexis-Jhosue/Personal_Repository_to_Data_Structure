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
#include <cmath>
#include <set>


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
        return nullptr; // Caso base: nodo vacío
    }

    if (node->data.getCedula() == cedula) {
        return node; // Nodo encontrado
    }
    std::shared_ptr<Nodo<T>> encontradoIzquierda = buscarNodoPorCedula(node->left, cedula);
    if (encontradoIzquierda != nullptr) {
        return encontradoIzquierda;
    }
    return buscarNodoPorCedula(node->right, cedula);
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
void KD_Tree<T>::buscarPorFechaImprobableRec(const std::shared_ptr<Nodo<T>>& node, const std::string& placa, bool& found) const {
    if (node == nullptr) {
        return;
    }
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    buscarPorFechaImprobableRec(node->left, placa, found);
    if (node->data.getHoraSalida() == fecha_improbable && node->data.getCoche().getPlaca() == placa) {
        std::cout << "Celda encontrada: " << std::endl;
        imprimir_celda(node);
        found = true;
    }
    buscarPorFechaImprobableRec(node->right, placa, found);
}

template <typename T>
void KD_Tree<T>::buscarPorFechaImprobable(const std::string& placa) const {
    bool found = false;
    buscarPorFechaImprobableRec(root, placa, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con la placa especificada." << std::endl;
    }
}
//--------------------------------------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::buscarPorMarcaRec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca, bool& found) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getMarca() == marca) {
        imprimir_celda(node);
        found = true;
    }
    buscarPorMarcaRec(node->left, marca, found);
    buscarPorMarcaRec(node->right, marca, found);
}

template <typename T>
void KD_Tree<T>::buscarPorMarca(const std::string& marca) const {
    bool found = false;
    buscarPorMarcaRec(root, marca, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con la marca especificada." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscarPorModeloRec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo, bool& found) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getModelo() == modelo) {
        imprimir_celda(node);
        found = true;
    }
    buscarPorModeloRec(node->left, modelo, found);
    buscarPorModeloRec(node->right, modelo, found);
}

template <typename T>
void KD_Tree<T>::buscarPorModelo(const std::string& modelo) const {
    bool found = false;
    buscarPorModeloRec(root, modelo, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el modelo especificado." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscarPorColorRec(const std::shared_ptr<Nodo<T>>& node, const std::string& color, bool& found) const {
    if (node == nullptr) return;
    if (node->data.getCoche().getColor() == color) {
        imprimir_celda(node);
        found = true;
    }
    buscarPorColorRec(node->left, color, found);
    buscarPorColorRec(node->right, color, found);
}

template <typename T>
void KD_Tree<T>::buscarPorColor(const std::string& color) const {
    bool found = false;
    buscarPorColorRec(root, color, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el color especificado." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscarPorFechaRec(const std::shared_ptr<Nodo<T>>& node, 
                                   const std::chrono::system_clock::time_point& fechaInicio, 
                                   const std::chrono::system_clock::time_point& fechaFin, bool& found) const {
    if (node == nullptr) return;

    auto horaEntrada = node->data.getHoraIngreso();
    if(horaEntrada == fechaInicio){
        imprimir_celda(node);
        found = true;   
        } else if (horaEntrada >= fechaInicio && horaEntrada <= fechaFin) {
        imprimir_celda(node); // Imprime solo si está dentro del rango
        found = true;
    }

    // Busca recursivamente en el subárbol izquierdo y derecho
    buscarPorFechaRec(node->left, fechaInicio, fechaFin, found);
    buscarPorFechaRec(node->right, fechaInicio, fechaFin, found);
}

template <typename T>
void KD_Tree<T>::buscarPorFecha(const std::string& fechaInicioStr, const std::string& fechaFinStr) const {
    auto fechaInicio = convertirStringATimePoint(fechaInicioStr);
    auto fechaFin = convertirStringATimePoint(fechaFinStr);
    bool found = false;
    if (fechaInicio > fechaFin) {
        std::cerr << "El rango de fechas es inválido: fechaInicio es posterior a fechaFin.\n";
        return;
    }

    buscarPorFechaRec(root, fechaInicio, fechaFin, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el rango de fechas especificado." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscarPorHoraRec(const std::shared_ptr<Nodo<T>>& node, 
                                  const std::chrono::minutes& horaInicio, 
                                  const std::chrono::minutes& horaFin, bool& found) const {
    if (node == nullptr) return;

    // Extraer solo la hora como minutos desde el inicio del día
    auto horaIngreso = convertirHoraAMinutos(node->data.getHoraIngreso());
    if (horaIngreso >= horaInicio && horaIngreso <= horaFin) {
        imprimir_celda(node);  // Asume que esta función imprime los datos del nodo
        found = true;
    }

    buscarPorHoraRec(node->left, horaInicio, horaFin, found);
    buscarPorHoraRec(node->right, horaInicio, horaFin, found);
}

template <typename T>
void KD_Tree<T>::buscarPorHora(const std::string& horaInicioStr, const std::string& horaFinStr) const {
    auto horaInicio = convertirStringAMinutos(horaInicioStr);
    auto horaFin = convertirStringAMinutos(horaFinStr);
    bool found = false;
    if (horaInicio > horaFin) {
        std::cerr << "El rango de horas es inválido: horaInicio es posterior a horaFin.\n";
        return;
    }

    buscarPorHoraRec(root, horaInicio, horaFin, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el rango de horas especificado." << std::endl;
    }
}


//---------------------------------------------------------------------------------------------------------
template <typename T>
void KD_Tree<T>::buscar_por_marca_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca, bool& found) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getMarca() == marca && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
        found = true;
    }
    buscar_por_marca_parqueadero_rec(node->left, marca, found);
    buscar_por_marca_parqueadero_rec(node->right, marca, found);
}

template <typename T>
void KD_Tree<T>::buscar_por_marca_parqueadero(const std::string& marca) const {
    bool found = false;
    buscar_por_marca_parqueadero_rec(root, marca, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con la marca especificada en el parqueadero." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscar_por_modelo_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo, bool& found) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getModelo() == modelo && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
        found = true;
    }
    buscar_por_modelo_parqueadero_rec(node->left, modelo, found);
    buscar_por_modelo_parqueadero_rec(node->right, modelo, found);
}

template <typename T>
void KD_Tree<T>::buscar_por_modelo_parqueadero(const std::string& modelo) const {
    bool found = false;
    buscar_por_modelo_parqueadero_rec(root, modelo, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el modelo especificado en el parqueadero." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscar_por_color_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& color,bool& found) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getCoche().getColor() == color && node->data.getHoraSalida() == fecha_improbable) {
        imprimir_celda(node);
        found = true;
    }
    buscar_por_color_parqueadero_rec(node->left, color, found);
    buscar_por_color_parqueadero_rec(node->right, color, found);
}

template <typename T>
void KD_Tree<T>::buscar_por_color_parqueadero(const std::string& color) const {
    bool found = false;
    buscar_por_color_parqueadero_rec(root, color, found);
    if (!found) {
        std::cout << "No se encontró ningún coche con el color especificado en el parqueadero." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscar_por_fecha_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, 
                                                  const std::chrono::system_clock::time_point& fechaInicio, 
                                                  const std::chrono::system_clock::time_point& fechaFin, bool& found) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaIngreso = node->data.getHoraIngreso();
    auto horaSalida = node->data.getHoraSalida();
    if (horaIngreso >= fechaInicio && horaIngreso <= fechaFin && horaSalida == fecha_improbable) {
        imprimir_celda(node);
        found = true;
    }
    buscar_por_fecha_parqueadero_rec(node->left, fechaInicio, fechaFin, found);
    buscar_por_fecha_parqueadero_rec(node->right, fechaInicio, fechaFin, found);
}

template <typename T>
void KD_Tree<T>::buscar_por_fecha_parqueadero(const std::string& fechaInicioStr, const std::string& fechaFinStr) const {
    bool found = false;
    auto fechaInicio = convertirStringATimePoint(fechaInicioStr);
    auto fechaFin = convertirStringATimePoint(fechaFinStr);
    if (fechaInicio > fechaFin) {
        std::cerr << "El rango de fechas es inválido: fechaInicio es posterior a fechaFin.\n";
        return;
    }
    buscar_por_fecha_parqueadero_rec(root, fechaInicio, fechaFin, found);
    if (!found) {
        std::cout << "No se encontró ningún coche en el parqueadero con el rango de fechas especificado." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscar_por_hora_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, 
                                                 const std::chrono::minutes& horaInicio, 
                                                 const std::chrono::minutes& horaFin, bool& found) const {
    if (node == nullptr) return;
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    auto horaIngreso = convertirHoraAMinutos(node->data.getHoraIngreso());
    auto horaSalida = node->data.getHoraSalida();
    if (horaIngreso >= horaInicio && horaIngreso <= horaFin && horaSalida == fecha_improbable) {
        imprimir_celda(node);
        found = true;
    }
    buscar_por_hora_parqueadero_rec(node->left, horaInicio, horaFin, found);
    buscar_por_hora_parqueadero_rec(node->right, horaInicio, horaFin, found);
}

template <typename T>
void KD_Tree<T>::buscar_por_hora_parqueadero(const std::string& horaInicioStr, const std::string& horaFinStr) const {
    bool found = false;
    auto horaInicio = convertirStringAMinutos(horaInicioStr);
    auto horaFin = convertirStringAMinutos(horaFinStr);
    if (horaInicio > horaFin) {
        std::cerr << "El rango de horas es inválido: horaInicio es posterior a horaFin.\n";
        return;
    }
    buscar_por_hora_parqueadero_rec(root, horaInicio, horaFin, found);
    if (!found) {
        std::cout << "No se encontró ningún coche en el parqueadero con el rango de horas especificado." << std::endl;
    }
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
    std::cout << "\033[34m" << " ENT " << "\033[0m "; 
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::ostringstream oss;
            oss << "(" << i << ";" << j << ")";
            std::string coord = oss.str();

            if (ocupacion[i][j]) {
                std::cout << "\033[31m" << coord << "\033[0m "; 
            } else {
                std::cout << "\033[32m" << coord << "\033[0m "; 
            }
            if (i == size - 1 && j == size - 1) {
                std::cout << "\033[34m" << "SAL" << "\033[0m "; 
            } 
        }
        std::cout << std::endl;
        std::cout << "      ";
    }
    cout << endl;
    cout << "\033[31m" << "(x ; y)" << "\033[0m ";
    cout << "Celda ocupada" << endl;
    cout << "\033[32m" << "(x ; y)" << "\033[0m ";
    cout << "Celda libre" << endl;  
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
    return buscar_coordenadas_en_parqueadero_rec(node->left, x, y) &&
           buscar_coordenadas_en_parqueadero_rec(node->right, x, y);
}

template <typename T>
bool KD_Tree<T>::buscar_coordenadas_en_parqueadero(float x, float y) const {
    return buscar_coordenadas_en_parqueadero_rec(root, x, y);
}
//--------------------------------------------------------------------------------------------------------
//---------------BUSQUEDAS DE VECINOS CERCANOS-----------------------------------------------------------
//--------------------------------------------------------------------------------------------------------

template <typename T>
void KD_Tree<T>::buscar_vecino_mas_cercano_rec(std::shared_ptr<Nodo<T>> node, float x, float y, float &min_dist, std::shared_ptr<Nodo<T>> &min_node, int depth) const {
    if (node == nullptr) return;

    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    if (node->data.getHoraSalida() == fecha_improbable) {
        float dx = node->coords[0] - x;
        float dy = node->coords[1] - y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < min_dist) {
            min_dist = dist;
            min_node = node;
        }
    }

    int axis = depth % 2;
    float diff = (axis == 0) ? (x - node->coords[0]) : (y - node->coords[1]);

    std::shared_ptr<Nodo<T>> near_node = (diff < 0) ? node->left : node->right;
    std::shared_ptr<Nodo<T>> far_node = (diff < 0) ? node->right : node->left;

    buscar_vecino_mas_cercano_rec(near_node, x, y, min_dist, min_node, depth + 1);

    if (std::abs(diff) < min_dist) {
        buscar_vecino_mas_cercano_rec(far_node, x, y, min_dist, min_node, depth + 1);
    }
}

template <typename T>
void KD_Tree<T>::buscar_vecino_mas_cercano(float x, float y) const {
    float min_dist = std::numeric_limits<float>::max();
    std::shared_ptr<Nodo<T>> min_node = nullptr;

    buscar_vecino_mas_cercano_rec(root, x, y, min_dist, min_node, 0);

    if (min_node) {
        std::cout << "El vecino más cercano está en (" << min_node->coords[0] << ", " << min_node->coords[1] << ") con una distancia de " << min_dist << std::endl;
        imprimir_celda(min_node);
    } else {
        std::cout << "No se encontró ningún vecino." << std::endl;
    }
}

template <typename T>
void KD_Tree<T>::buscar_celda_vacia_mas_cercana(float x, float y, int size) const {
    // 1. Extraer coordenadas ocupadas
    std::set<std::pair<float, float>> ocupadas;
    extraer_coordenadas_ocupadas(root, ocupadas);

    // 2. Generar coordenadas faltantes
    std::vector<std::pair<float, float>> faltantes;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (ocupadas.find({i, j}) == ocupadas.end()) {
                faltantes.emplace_back(i, j);
            }
        }
    }

    // 3. Construir un nuevo KD-Tree con las coordenadas faltantes
    KD_Tree<T> kd_vacio;
    for (const auto& coord : faltantes) {
        kd_vacio.insert(T{}, coord.first, coord.second);

    }

    // 4. Buscar celda vacía más cercana en el nuevo árbol
    float min_dist = std::numeric_limits<float>::max();
    std::shared_ptr<Nodo<T>> min_node = nullptr;
    kd_vacio.buscar_celda_vacia_mas_cercana_rec(kd_vacio.root, x, y, min_dist, min_node, 0);

    // Imprimir resultados
    if (min_node) {
        std::cout << "La celda vacía más cercana está en (" << min_node->coords[0] << ", " << min_node->coords[1] << ") con una distancia de " << min_dist << std::endl;
    } else {
        std::cout << "No se encontró ninguna celda vacía." << std::endl;
    }
    imprimir_parqueadero(size);
    kd_vacio.~KD_Tree();
}

// Método auxiliar: Extraer coordenadas ocupadas
template <typename T>
void KD_Tree<T>::extraer_coordenadas_ocupadas(const std::shared_ptr<Nodo<T>> node, std::set<std::pair<float, float>>& ocupadas) const {
    if (!node) return;

    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();
    if (node->data.getHoraSalida() == fecha_improbable) { // Celda ocupada
        ocupadas.insert({node->coords[0], node->coords[1]});
    }

    extraer_coordenadas_ocupadas(node->left, ocupadas);
    extraer_coordenadas_ocupadas(node->right, ocupadas);
}

template <typename T>
void KD_Tree<T>::buscar_celda_vacia_mas_cercana_rec(std::shared_ptr<Nodo<T>> node, float x, float y, float &min_dist, std::shared_ptr<Nodo<T>> &min_node, int depth) const {
    if (node == nullptr) return;

    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    if (node->data.getHoraSalida() != fecha_improbable) { // Check if the cell is empty
        float dx = node->coords[0] - x;
        float dy = node->coords[1] - y;
        float dist = std::sqrt(dx * dx + dy * dy);

        if (dist < min_dist) {
            min_dist = dist;
            min_node = node;
        }
    }
    int axis = depth % 2;
    float diff = (axis == 0) ? (x - node->coords[0]) : (y - node->coords[1]);

    std::shared_ptr<Nodo<T>> near_node = (diff < 0) ? node->left : node->right;
    std::shared_ptr<Nodo<T>> far_node = (diff < 0) ? node->right : node->left;

    buscar_celda_vacia_mas_cercana_rec(near_node, x, y, min_dist, min_node, depth + 1);

    if (std::abs(diff) < min_dist) {
        buscar_celda_vacia_mas_cercana_rec(far_node, x, y, min_dist, min_node, depth + 1);
    }
}

template <typename T>
bool KD_Tree<T>::verificar_espacio_en_parqueadero() const {
    return verificar_espacio_en_parqueadero_rec(root);
}

template <typename T>
bool KD_Tree<T>::verificar_espacio_en_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node) const {
    if (node == nullptr) return true;

    // Definir la fecha improbable como referencia
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    // Verificar la hora de salida
    if (node->data.getHoraSalida() == fecha_improbable) {
        return false; // Se encontró un nodo con espacio disponible
    }

    // Continuar la búsqueda en los subárboles izquierdo y derecho
    return verificar_espacio_en_parqueadero_rec(node->left) &&
           verificar_espacio_en_parqueadero_rec(node->right);
}