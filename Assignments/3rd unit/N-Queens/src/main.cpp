#include <iostream>
#include <vector>
#include <fstream> // Para manejar archivos
#include <SFML/Graphics.hpp> // Incluir SFML
#include "../include/State.h"

// Tamaño de cada casilla del tablero
const int TILE_SIZE = 80; // Aumentamos el tamaño de las casillas

// Función para dibujar el tablero y las reinas
void drawBoard(sf::RenderWindow& window, const State& state, const sf::Texture& queenTexture) {
    int n = state.getN();
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    sf::Sprite queenSprite(queenTexture);

    // Ajustar el tamaño de la reina para que quepa en la casilla
    sf::FloatRect queenBounds = queenSprite.getLocalBounds(); // Obtener el tamaño del sprite
    float scale = TILE_SIZE / queenBounds.width; // Escalar basado en el ancho
    queenSprite.setScale(scale, scale); // Escalar el sprite

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Alternar colores del tablero
            tile.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
            tile.setPosition(j * TILE_SIZE, i * TILE_SIZE); // Establecer posición
            window.draw(tile);

            // Dibujar la reina si está en esta posición
            for (const Queen& q : state.getQueens()) {
                if (q.getRow() == i && q.getCol() == j) {
                    queenSprite.setPosition(j * TILE_SIZE, i * TILE_SIZE); // Establecer posición
                    window.draw(queenSprite);
                }
            }
        }
    }
}

// Función para dibujar el panel de información
void drawInfoPanel(sf::RenderWindow& window, const State& state, const sf::Font& font, int totalAttempts) {
    // Crear un fondo para el panel
    sf::RectangleShape panel(sf::Vector2f(400, window.getSize().y)); // Ancho fijo de 400 píxeles
    panel.setFillColor(sf::Color(240, 240, 240)); // Color de fondo gris claro
    panel.setPosition(window.getSize().x - 400, 0); // Posicionar a la derecha
    window.draw(panel);

    // Crear un objeto sf::Text para mostrar la información
    sf::Text infoText;
    infoText.setFont(font); // Establecer la fuente
    infoText.setCharacterSize(24); // Tamaño del texto más grande
    infoText.setFillColor(sf::Color::Black); // Color del texto

    // Construir el texto con las coordenadas de las reinas
    std::string infoString = "Posiciones de las reinas:\n";
    for (const Queen& queen : state.getQueens()) {
        infoString += "(" + std::to_string(queen.getRow()) + ", " + std::to_string(queen.getCol()) + ")\n";
    }

    // Agregar el número de intentos
    infoString += "\nNumero de intentos: " + std::to_string(totalAttempts);

    // Establecer el texto
    infoText.setString(infoString);

    // Posicionar el texto en el panel
    infoText.setPosition(window.getSize().x - 380, 20); // Margen izquierdo de 20 píxeles
    window.draw(infoText);
}

// Función para encontrar una solución al problema de las N reinas
bool solveNQueens(State& state, int col, int& totalAttempts) {
    int n = state.getN();
    if (col >= n) {
        return true; // Todas las reinas se han colocado correctamente
    }

    for (int row = 0; row < n; ++row) {
        totalAttempts++; // Incrementar el contador de intentos
        if (state.isSafe(row, col)) {
            state.placeQueen(row, col); // Colocar una reina

            // Llamar recursivamente para la siguiente columna
            if (solveNQueens(state, col + 1, totalAttempts)) {
                return true; // Si se encuentra una solución, retornar verdadero
            }

            state.removeQueen(); // Retroceder (backtracking)
        }
    }

    return false; // No se encontró una solución
}

// Función para guardar los resultados en un archivo de texto
void saveResultsToFile(const std::string& filename, int n, int attempts, const State& state) {
    std::ofstream outputFile(filename, std::ios::app); // Abrir el archivo en modo append

    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar los resultados." << std::endl;
        return;
    }

    // Escribir una línea separadora
    outputFile << "----------------------------------------\n";

    // Escribir el tamaño del tablero
    outputFile << "Tamaño del tablero (n): " << n << "\n";

    // Escribir el número de intentos
    outputFile << "Numero de intentos: " << attempts << "\n";

    // Escribir las coordenadas de las reinas
    outputFile << "Posiciones de las reinas:\n";
    for (const Queen& queen : state.getQueens()) {
        outputFile << "(" << queen.getRow() << ", " << queen.getCol() << ")\n";
    }

    outputFile << "\n"; // Espacio adicional entre registros
    outputFile.close(); // Cerrar el archivo
    std::cout << "Resultados guardados en " << filename << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the size of the board (N x N): ";
    std::cin >> n;

    State initialState(n);
    std::vector<State> solutions;

    // Contador de intentos
    int totalAttempts = 0;

    // Encontrar una solución al problema de las N reinas
    if (solveNQueens(initialState, 0, totalAttempts)) {
        std::cout << "Solucion encontrada." << std::endl;
    } else {
        std::cout << "No se encontro una solucion." << std::endl;
    }

    // Guardar los resultados en un archivo de texto
    saveResultsToFile("output//results.txt", n, totalAttempts, initialState);

    // Cargar la textura de la reina desde un archivo
    sf::Texture queenTexture;
    if (!queenTexture.loadFromFile("output//queen2.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de la reina." << std::endl;
        return -1;
    }

    // Cargar una fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("output//arial.ttf")) { // Cambia "arial.ttf" por la ruta de tu archivo de fuente
        std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
        return -1;
    }

    // Crear una ventana SFML
    int windowWidth = n * TILE_SIZE + 400; // Ancho del tablero + ancho del panel
    int windowHeight = n * TILE_SIZE; // Alto del tablero
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "N-Queens Board");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        drawBoard(window, initialState, queenTexture); // Dibujar el tablero con reinas
        drawInfoPanel(window, initialState, font, totalAttempts); // Dibujar el panel de información
        window.display();
    }

    return 0;
}