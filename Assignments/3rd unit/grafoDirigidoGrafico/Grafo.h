#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>
#include <queue>

class Grafo {
public:
    Grafo();
    void nuevoGrafo(int numNodos, bool dirigido);
    void representacionLogica();
    void representacionListaAdyacencia();
    void representacionMatrizAdyacencia();
    void busquedaAmplitud(int verticeInicial);
    void representacionLogicaGrafica();
    void representacionListaAdyacenciaGrafica();
    void representacionMatrizAdyacenciaGrafica();

private:
    int numNodos;
    bool dirigido;
    std::vector<std::vector<int>> matrizAdyacencia;
    void generarRelacionesAleatorias();
};

#endif // GRAFO_H