#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include "KD_Tree.h"
#include "Coche.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

class Ordenamientos
{
public:
    // Función para ordenar el árbol por un criterio dado (0: Placa, 1: Color, 2: Marca, 3: Modelo, 4: Propietario)
    static void ordenarPorCriterio(KD_Tree<Coche>& arbol_coches, int criterio);

    // Función para imprimir el árbol ordenado por un criterio dado
    void imprimirOrdenado(KD_Tree<Coche>& arbol_coches, int criterio);

    template <typename T>
    void recorrerInOrder(std::shared_ptr<Nodo<T>> nodo, std::function<void(std::shared_ptr<Nodo<T>>)> func);

};

#endif // ORDENAMIENTOS_H
