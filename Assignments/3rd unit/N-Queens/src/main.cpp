#include <iostream>
#include <SFML/Graphics.hpp>
#include "../include/State.h"
#include "../include/Game.h"

bool solveNQueens(State& state, int col, int& totalAttempts);

int main() {
    int n;
    do {
        std::cout << "Enter the size of the board (N x N) [1-8]: ";
        std::cin >> n;
        if (n < 1 || n > 8) {
            std::cerr << "Error: The size of the board must be between 1 and 8." << std::endl;
        }
    } while (n < 1 || n > 8);

    State initialState(n);
    int totalAttempts = 0;

    if (solveNQueens(initialState, 0, totalAttempts)) {
        std::cout << "Solucion encontrada." << std::endl;
    } else {
        std::cout << "No se encontro una solucion." << std::endl;
    }

    saveResultsToFile("output//results.txt", n, totalAttempts, initialState);

    sf::Texture queenTexture;
    if (!queenTexture.loadFromFile("output//queen2.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de la reina." << std::endl;
        return -1;
    }

    sf::Font font;
    if (!font.loadFromFile("output//arial.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
        return -1;
    }

    int queenX, queenY;
    do {
        std::cout << "Ingrese la fila de la reina (1 a " << n << "): ";
        std::cin >> queenX;

        if (queenX < 1 || queenX > n) {
            std::cerr << "Error: La fila ingresada está fuera del rango del tablero." << std::endl;
        }
    } while (queenX < 1 || queenX > n);

    do {
        std::cout << "Ingrese la columna de la reina (1 a " << n << "): ";
        std::cin >> queenY;

        if (queenY < 1 || queenY > n) {
            std::cerr << "Error: La columna ingresada está fuera del rango del tablero." << std::endl;
        }
    } while (queenY < 1 || queenY > n);

    // Ajustar las coordenadas para un índice basado en 0
    queenX -= 1;
    queenY -= 1;

    std::cout << "Coordenadas validas ingresadas: (" << queenX + 1 << ", " << queenY + 1 << ")" << std::endl;

    int windowWidth = n * TILE_SIZE + 400;
    int windowHeight = n * TILE_SIZE;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "N-Queens Board");

    std::vector<std::pair<int, int>> queenMoves = calculateQueenMoves(queenX, queenY, n);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawBoard(window, initialState, queenTexture, queenMoves, queenX, queenY);
        drawInfoPanel(window, initialState, font, totalAttempts, queenMoves);
        window.display();
    }

    return 0;
}

bool solveNQueens(State& state, int col, int& totalAttempts) {
    int n = state.getN();
    if (col >= n) return true;
    for (int row = 0; row < n; ++row) {
        totalAttempts++;
        if (state.isSafe(row, col)) {
            state.placeQueen(row, col);
            if (solveNQueens(state, col + 1, totalAttempts)) return true;
            state.removeQueen();
        }
    }
    return false;
}