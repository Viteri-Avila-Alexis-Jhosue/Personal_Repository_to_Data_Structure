#include "KD_Tree.h"
#include "Ordenamientos.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

// Función de comparación genérica que recibe un criterio
bool compararPorCriterio(const Coche& c1, const Coche& c2, int criterio) {
    switch (criterio) {
        case 0: return c1.getPlaca() < c2.getPlaca();
        case 1: return c1.getColor() < c2.getColor();
        case 2: return c1.getMarca() < c2.getMarca();
        case 3: return c1.getModelo() < c2.getModelo();
        case 4: return c1.getPropietario().getNombre() < c2.getPropietario().getNombre();
        default: return false;
    }
}

// Función auxiliar para recorrer el árbol en orden
template <typename T>
void Ordenamientos::recorrerInOrder(std::shared_ptr<Nodo<T>> nodo, std::function<void(std::shared_ptr<Nodo<T>>)> func) {
    if (nodo) {
        recorrerInOrder(nodo->left, func);
        func(nodo);
        recorrerInOrder(nodo->right, func);
    }
}


// Función para imprimir el árbol ordenado por el criterio dado
// Función para imprimir el árbol ordenado por el criterio dado
void Ordenamientos::imprimirOrdenado(KD_Tree<Coche>& arbol_coches, int criterio) {
    std::vector<Coche> coches;

    // Recorrer el árbol en orden y almacenar los coches en un vector
    std::function<void(std::shared_ptr<Nodo<Coche>>)> lambda_func = [&coches](std::shared_ptr<Nodo<Coche>> nodo) {
        if (nodo) {
            coches.push_back(nodo->data);  // Accede directamente al miembro 'data'
        }
    };

    // Llamada a recorrerInOrder con el tipo de lambda correcto
    recorrerInOrder(arbol_coches.getRoot(), lambda_func);

    // Ordenar los coches según el criterio dado
    std::sort(coches.begin(), coches.end(), [criterio](const Coche& c1, const Coche& c2) {
        return compararPorCriterio(c1, c2, criterio);
    });

    // Imprimir los coches ordenados
    for (const auto& coche : coches) {
        std::cout << "Placa: " << coche.getPlaca() << ", Modelo: " << coche.getModelo() 
                  << ", Color: " << coche.getColor() << ", Marca: " << coche.getMarca() 
                  << ", Propietario: " << coche.getPropietario().getNombre() << std::endl;
    }
}
template void Ordenamientos::recorrerInOrder<Coche>(std::shared_ptr<Nodo<Coche>>, std::function<void(std::shared_ptr<Nodo<Coche>>)>);