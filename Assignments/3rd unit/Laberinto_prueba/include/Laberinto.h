#ifndef LABERINTO_H
#define LABERINTO_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream> // Para manejar archivos
#include <sstream> // Para manejar strings como streams
#include <SFML/Graphics.hpp>    

class Laberinto {
public:
    Laberinto(int size);
    void generarLaberinto();
    bool resolverLaberinto();
    void imprimirLaberinto() const;
    void generarCaminoSeguro();
    void guardarLaberintoEnArchivo(const std::string& nombreArchivo) const;
    bool cargarLaberintoDesdeArchivo(const std::string& nombreArchivo); // Nuevo método

private:
    int size;
    std::vector<std::vector<int>> laberinto; // 0: pared, 1: camino
    std::vector<std::vector<bool>> visitado;

    void generarCamino(int fila, int columna);
    bool esValido(int fila, int columna) const;
    bool esSolucion(int fila, int columna) const;
    bool backtracking(int fila, int columna);
};

#endif