#ifndef KD_TREE_H
#define KD_TREE_H

#include "Propietario.h"
#include "Coche.h"
#include "Nodo.h"
#include "Celda.h"
#include "Time_utils.h"
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
#include <set>



template <typename T>
class KD_Tree {
private:
    void clear(std::shared_ptr<Nodo<T>> node);
    std::shared_ptr<Nodo<T>> root;
    std::shared_ptr<Nodo<T>> insertRec(std::shared_ptr<Nodo<T>> node, const T& data, const std::array<float, 2>& coords, int depth);
    void inOrderRec(std::shared_ptr<Nodo<T>> node) const;
    T* buscarPorCedulaRec(std::shared_ptr<Nodo<T>> node, const std::string& cedula) const;
    T* buscarPorPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const;
    T* buscarPorPlacaEnCochesRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const;
    T* buscarPorPlacaEnCeldaRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const;
    T* buscarPorPlacaYFechaImprobableRec(std::shared_ptr<Nodo<T>> node, const std::string& placa) const;
    bool eliminarPlacaRec(std::shared_ptr<Nodo<T>> node, const std::string &cedula, const std::string &placa);
    std::shared_ptr<Nodo<T>> buscarNodoPorCedula(std::shared_ptr<Nodo<T>> node, const std::string &cedula) const;
    void imprimirNodosRec(const std::shared_ptr<Nodo<T>>& node) const;
    void imprimirCeldasRec(const std::shared_ptr<Nodo<T>>& node) const;
    void buscarPorFechaImprobableRec(const std::shared_ptr<Nodo<T>>& node, const std::string& placa,bool& found) const;
    void buscarPorMarcaRec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca,bool& found) const;
    void buscarPorModeloRec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo,bool& found) const;
    void buscarPorColorRec(const std::shared_ptr<Nodo<T>>& node, const std::string& color,bool& found) const;
    void buscarPorFechaRec(const std::shared_ptr<Nodo<T>>& node, const std::chrono::system_clock::time_point& fechaInicio, const std::chrono::system_clock::time_point& fechaFin,bool& found) const;
    void buscarPorHoraRec(const std::shared_ptr<Nodo<T>>& node, const std::chrono::minutes& horaInicio, const std::chrono::minutes& horaFin,bool& found) const;
    void buscar_por_marca_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& marca,bool& found) const;
    void buscar_por_modelo_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& modelo, bool& found) const;
    void buscar_por_color_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::string& color,bool& found) const;
    void buscar_por_fecha_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, const std::chrono::system_clock::time_point& fechaInicio, const std::chrono::system_clock::time_point& fechaFin,bool& found) const;
    void buscar_por_hora_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node,const std::chrono::minutes& horaInicio, const std::chrono::minutes& horaFin,bool& found) const;
    void imprimir_propietarios_Rec(std::shared_ptr<Nodo<T>> node) const;
    void imprimir_propietario(std::shared_ptr<Nodo<T>> node) const;
    void imprimir_celda(std::shared_ptr<Nodo<T>> node) const;
    bool buscar_coordenadas_en_parqueadero_rec(const std::shared_ptr<Nodo<T>>& node, float x, float y) const;
    void buscar_vecino_mas_cercano_rec(std::shared_ptr<Nodo<T>> node, float x, float y, float &min_dist, std::shared_ptr<Nodo<T>> &min_node, int depth) const;
    void buscar_celda_vacia_mas_cercana_rec(std::shared_ptr<Nodo<T>> node, float x, float y, float &min_dist, std::shared_ptr<Nodo<T>> &min_node, int depth) const;
    void extraer_coordenadas_ocupadas(const std::shared_ptr<Nodo<T>> node, std::set<std::pair<float, float>>& ocupadas) const;
  
public:
    KD_Tree();
    ~KD_Tree();
    void insert(const T& data, float x, float y);
    void inOrder() const;
    void loadPropietarios(const std::string& fileName);
    void loadAutosHistorial(const std::string& fileName);
    void loadAutos(const std::string& fileName);
    float convertirStringAFloat(const std::string & str);
    void imprimir_propietarios() const;
    T* buscarPorPlaca(const std::string& placa) const;
    T* buscarPorCedula(const std::string& cedula) const;
    void eliminarPlacaPorCedula(const std::string &cedula, const std::string &placa);
    void guardarPropietariosEnArchivo(const std::string& nombreArchivo) const;
    void guardarPropietariosEnMemoria(std::shared_ptr<Nodo<T>> node, std::ofstream& archivo) const;
    T* buscarPorPlacaEnCoches(const std::string& placa) const;
    void imprimirNodos() const;
    T* buscarPorPlacaEnCelda(const std::string& placa) const;
    void imprimirCeldas() const;
    void buscarPorFechaImprobable(const std::string& placa) const;
    void buscarPorMarca(const std::string& marca) const;
    void buscarPorModelo(const std::string& modelo) const;
    void buscarPorColor(const std::string& color) const;
    void buscarPorFecha(const std::string& fechaInicioStr, const std::string& fechaFinStr) const;
    void buscarPorHora(const std::string& horaInicioStr, const std::string& horaFinStr) const;
    void buscar_por_marca_parqueadero(const std::string& marca) const;
    void buscar_por_modelo_parqueadero(const std::string& modelo) const;
    void buscar_por_color_parqueadero(const std::string& color) const;
    void buscar_por_fecha_parqueadero(const std::string& fechaInicioStr, const std::string& fechaFinStr) const;
    void buscar_por_hora_parqueadero(const std::string& horaInicioStr, const std::string& horaFinStr) const;
    T* buscarPorPlacaYFechaImprobable(const std::string& placa) const;
    std::shared_ptr<Nodo<T>> getRoot() const {
        return root;
    }
    void imprimir_parqueadero(int size)const;
    bool buscar_coordenadas_en_parqueadero(float x, float y) const;
    void buscar_vecino_mas_cercano(float x, float y) const;
    void buscar_celda_vacia_mas_cercana(float x, float y, int size) const;
 
};

#include "../src/KD_Tree.cpp"

#endif // KD_TREE_H
