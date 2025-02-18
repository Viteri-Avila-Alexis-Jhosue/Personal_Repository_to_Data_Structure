#include "../include/Laberinto.h"
#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

Laberinto::Laberinto(int size) : size(size) {
    laberinto.resize(size, std::vector<int>(size, 0)); // Todo comienza como pared
    visitado.resize(size, std::vector<bool>(size, false));
}

void Laberinto::generarCaminoSeguro() {
    int fila = 0, columna = 0;
    laberinto[fila][columna] = 1;

    while (fila < size - 1 || columna < size - 1) {
        if (fila == size - 1) {
            columna++; // Avanza solo a la derecha si está en la última fila
        } else if (columna == size - 1) {
            fila++; // Baja solo si está en la última columna
        } else {
            if (rand() % 2 == 0) {
                fila++; // Baja
            } else {
                columna++; // Derecha
            }
        }
        laberinto[fila][columna] = 1; // Marca camino
    }
}

void Laberinto::generarLaberinto() {
    srand(time(0));
    generarCaminoSeguro(); // Primero, asegura un camino seguro

    // Añade caminos aleatorios sin bloquear la solución
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (laberinto[i][j] == 0 && rand() % 3 == 0) { 
                laberinto[i][j] = 1; // Agrega caminos adicionales
            }
        }
    }
}

bool Laberinto::esValido(int fila, int columna) const {
    return fila >= 0 && fila < size && columna >= 0 && columna < size && laberinto[fila][columna] == 1;
}

bool Laberinto::esSolucion(int fila, int columna) const {
    return fila == size - 1 && columna == size - 1;
}

bool Laberinto::backtracking(int fila, int columna) {
    if (!esValido(fila, columna) || visitado[fila][columna]) return false;
    
    visitado[fila][columna] = true;

    if (esSolucion(fila, columna)) return true;

    // Intentar moverse en las 4 direcciones
    if (backtracking(fila + 1, columna) || backtracking(fila - 1, columna) ||
        backtracking(fila, columna + 1) || backtracking(fila, columna - 1)) {
        return true;
    }

    visitado[fila][columna] = false;
    return false;
}

bool Laberinto::resolverLaberinto() {
    return backtracking(0, 0);
}

void Laberinto::guardarLaberintoEnArchivo(const std::string& nombreArchivo) const {
    std::ofstream archivo(nombreArchivo); // Abre el archivo para escritura

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return;
    }

    for (const auto& fila : laberinto) {
        for (int celda : fila) {
            archivo << celda << " "; // Escribe cada celda en el archivo
        }
        archivo << std::endl; // Nueva línea después de cada fila
    }

    archivo.close(); // Cierra el archivo
    std::cout << "Laberinto guardado en " << nombreArchivo << std::endl;
}
bool Laberinto::cargarLaberintoDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo); // Abre el archivo para lectura

    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
        return false;
    }

    // Limpiar el laberinto actual
    laberinto.clear();
    visitado.clear();

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::vector<int> fila;
        std::istringstream ss(linea);
        int valor;

        while (ss >> valor) {
            fila.push_back(valor); // Lee cada valor de la fila
        }

        if (!fila.empty()) {
            laberinto.push_back(fila); // Agrega la fila al laberinto
        }
    }

    archivo.close(); // Cierra el archivo

    // Actualizar el tamaño del laberinto
    size = laberinto.size();

    // Redimensionar la matriz de visitados
    visitado.resize(size, std::vector<bool>(size, false));

    std::cout << "Laberinto cargado desde " << nombreArchivo << std::endl;
    return true;
}
void Laberinto::imprimirLaberinto() const {
    const int cellSize = 60;  // Aumenté el tamaño de cada celda
    const int windowSize = size * cellSize; // Tamaño de la ventana

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Laberinto");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White); // Fondo blanco

        // Dibujar el laberinto
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);

                if (laberinto[i][j] == 0) { 
                    // Pared (Negro)
                    cell.setFillColor(sf::Color::Black);
                } else { 
                    // Camino (Blanco con borde negro)
                    cell.setFillColor(sf::Color::White);
                    cell.setOutlineThickness(-3);  // Aumenté grosor del borde
                    cell.setOutlineColor(sf::Color::Black);
                }

                window.draw(cell);
            }
        }

        window.display();
    }
}
