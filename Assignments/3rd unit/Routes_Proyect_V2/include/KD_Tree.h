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
    void clear(Node<T>* node); 
    Node<T>* root;
    Node<T>* insertRec(Node<T>* node, const T& data, const std::array<int, 2>& coords, int depth);
    void inOrderRec(Node<T>* node) const;
    void print_ubicaciones_rec(Node<T>* node) const;
    void print_routes_rec(Node<T>* node) const;
    void print_routes_name_rec(Node<T>* node, std::string routeName) const;
    Node<T>* findNodeRec(Node<T>* node, const std::array<int, 2>& coords, int depth) const;
    bool findNodeByNameRec(Node<T>* node, const std::string& name) const;
    T* getNodeByNameRec(Node<T>* node, const std::string& name) const;
    T* getNodeByNameAndCoordinatesRec(Node<T>* node, const std::string& name, int x, int y) const;
    T* getNodeByNameAndLastCoordinatesRec(Node<T>* node, const std::string& name, int x, int y) const;
    T* obtenerSiguienteTramo(const std::string& routeName, T* tramoActual);
    bool validarTramoExistenteRec(Node<T>* node, const std::string& routeName, int xInicial, int yInicial, int xFinal, int yFinal, double distance) const;
    void obtenerUbicacionesRec(Node<T>* node, std::vector<T>& ubicaciones) const;
    void obtenerRutasRec(Node<T>* node, std::vector<T>& rutas) const;
    Node<T> *eliminarRec(Node<T> *node, const std::string &name);
    Node<T> *eliminarTramoRec(Node<T> *node, const std::string &name, int xi, int yi, int xf, int yf);
    void verificarBidireccionalidadRec(Node<T>* node, KD_Tree<T>& nuevoArbol) const;
    Node<T>* obtenerNodoPorNombreUbicacionRec(Node<T>* node, const std::string& nombreUbicacion)const ; 
    void updateUbicationNameRec(Node<T>* node, const std::string& oldName, const std::string& newName);
 
public:
    KD_Tree();
    ~KD_Tree();
    void insert(const T& data, int x, int y);
    void inOrder() const;
    void load_ubicaciones(const std::string& fileName);
    void load_routes(const std::string& fileName);
    void print_ubicaciones() const;
    Node<T>* findNode(int x, int y) const;
    bool findNodeByName(const std::string& name) const;
    void print_routes() const;
    void print_routes_name(std::string routeName) const;
    T* getNodeByName(const std::string& name) const;
    T* getNodeByNameAndCoordinates(const std::string& name, int x, int y) const; 
    T* getNodeByNameAndLastCoordinates(const std::string& name, int x, int y) const; 
    void aplicarTraficoEntreUbicaciones(const std::string& routeName, int x1, int y1, int x2, int y2, const Trafic& trafic);
    T* obtenerUbicacionInicial(const std::string& routeName) const;
    T* obtenerUbicacionFinal(const std::string& routeName) const;
    void eliminarTramo(const std::string& nombreRuta, int xInicial, int yInicial, int xFinal, int yFinal);
    void eliminarRutaCompleta(const std::string& nombreRuta);
    bool validarTramoExistente(const std::string& routeName, int xInicial, int yInicial, int xFinal, int yFinal, double distance) const;
    std::vector<T> obtenerTodasLasUbicaciones() const;
    std::vector<T> obtenerTodasLasRutas() const;
    KD_Tree<T> crearArbolBidireccional() const;
    Node<T>* obtenerNodoPorNombreUbicacion(const std::string& nombreUbicacion) const;
    void updateUbicationName(const std::string& oldName, const std::string& newName);
    double get_trafico_total(const std::string& hora, const std::string& route_name) const;
    std::vector<std::tuple<std::string, double>> get_trafico_por_horas(const std::string& route_name) const;
    void guardar_trafico_por_horas(const std::string& route_name) const;
    void guardar_trafico_todas_rutas() const;

};

#include "../src/KD_Tree.cpp"

#endif // KD_TREE_