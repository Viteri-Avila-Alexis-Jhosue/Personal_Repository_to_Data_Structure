#ifndef GRAFO_H
#define GRAFO_H

#include "Route.h"
#include "Ubication.h"
#include "Trafic.h"
#include "KD_Tree.h" 
#include <vector>
#include <map>
#include <string>
#include <limits>
#include <queue>
#include <algorithm>
#include <ctime>

class Grafo {
private:
    std::map<std::string, Ubication*> nodos; // Mapa de nodos (ubicaciones)
    std::map<std::string, std::vector<std::pair<std::string, double>>> adyacencias; // Lista de adyacencia
    const KD_Tree<Ubication>& kdTreeUbicaciones; // Árbol KD con ubicaciones
    const KD_Tree<Route>& kdTreeRutas;          // Árbol KD con rutas

    double calcularTiempo(double distancia, const std::vector<Trafic>& traficos, const std::string& horaActual, double velocidadRuta) const;
    std::string sumarHoras(const std::string& horaActual, double horas) const;
    std::vector<Trafic> obtenerTraficos(const std::string& origen, const std::string& destino) const;
    
public:
    Grafo(const KD_Tree<Ubication>& kdTreeUbicaciones, const KD_Tree<Route>& kdTreeRutas);
    ~Grafo();
    void construirGrafo();  
    void agregarNodo(const Ubication& ubicacion);
    void agregarArista(const std::string& nombreOrigen, const std::string& nombreDestino, double distancia, const std::vector<Trafic>& traficos);
    std::vector<Route> dijkstraTiempo(const std::string& origen, const std::string& destino, const std::string& horaSalida) const;
    std::vector<Route> dijkstraD(const std::string& origen, const std::string& destino) const;
    std::vector<Route> calcularRutaOptimaVariosPuntos(const std::vector<std::string>& puntos, const std::string& horaSalida) const;
    std::vector<Route> calcularRutaOptimaVariosPuntosDistancia(const std::vector<std::string>& puntos) const;
};

#endif // GRAFO_H