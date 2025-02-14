#include "../include/Game.h"
#include <fstream>
#include <iostream>

void drawBoard(sf::RenderWindow& window, const State& state, const sf::Texture& queenTexture, const std::vector<std::pair<int, int>>& moves, int arbX, int arbY) {
    int n = state.getN();
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    sf::Sprite queenSprite(queenTexture);

    sf::FloatRect queenBounds = queenSprite.getLocalBounds();
    float scale = TILE_SIZE / queenBounds.width;
    queenSprite.setScale(scale, scale);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tile.setFillColor((i + j) % 2 == 0 ? sf::Color::White : sf::Color::Black);
            tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            window.draw(tile);

            for (const auto& move : moves) {
                if (move.first == i && move.second == j) {
                    sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    highlight.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    highlight.setFillColor(sf::Color(255, 255, 0, 128));
                    window.draw(highlight);
                }
            }

            for (const Queen& q : state.getQueens()) {
                if (q.getRow() == i && q.getCol() == j) {
                    queenSprite.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                    window.draw(queenSprite);
                }
            }
        }
    }

    queenSprite.setColor(sf::Color::Red);
    queenSprite.setPosition(arbY * TILE_SIZE, arbX * TILE_SIZE);
    window.draw(queenSprite);
}

void drawInfoPanel(sf::RenderWindow& window, const State& state, const sf::Font& font, int totalAttempts, const std::vector<std::pair<int, int>>& moves) {
    sf::RectangleShape panel(sf::Vector2f(400, window.getSize().y));
    panel.setFillColor(sf::Color(240, 240, 240));
    panel.setPosition(window.getSize().x - 400, 0);
    window.draw(panel);

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(24);
    infoText.setFillColor(sf::Color::Black);

    std::string infoString = "Posiciones de las reinas:\n";
    for (const Queen& queen : state.getQueens()) {
        infoString += "(" + std::to_string(queen.getRow()) + ", " + std::to_string(queen.getCol()) + ")\n";
    }

    infoString += "\nNumero de intentos: " + std::to_string(totalAttempts);
    infoString += "\nRecorrido de la reina arbitraria:\n";
    for (const auto& move : moves) {
        infoString += "(" + std::to_string(move.first) + ", " + std::to_string(move.second) + ")\n";
    }

    infoText.setString(infoString);
    infoText.setPosition(window.getSize().x - 380, 20);
    window.draw(infoText);
}

std::vector<std::pair<int, int>> calculateQueenMoves(int x, int y, int n) {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < n; ++i) {
        if (i != x) moves.push_back({i, y});
        if (i != y) moves.push_back({x, i});
    }
    for (int i = 1; i < n; ++i) {
        if (x + i < n && y + i < n) moves.push_back({x + i, y + i});
        if (x - i >= 0 && y - i >= 0) moves.push_back({x - i, y - i});
        if (x + i < n && y - i >= 0) moves.push_back({x + i, y - i});
        if (x - i >= 0 && y + i < n) moves.push_back({x - i, y + i});
    }
    return moves;
}

void saveResultsToFile(const std::string& filename, int n, int attempts, const State& state) {
    std::ofstream outputFile(filename, std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar los resultados." << std::endl;
        return;
    }

    outputFile << "----------------------------------------\n";
    outputFile << "Tamaño del tablero (n): " << n << "\n";
    outputFile << "Numero de intentos: " << attempts << "\n";
    outputFile << "Posiciones de las reinas:\n";
    for (const Queen& queen : state.getQueens()) {
        outputFile << "(" << queen.getRow() << ", " << queen.getCol() << ")\n";
    }
    outputFile << "\n";
    outputFile.close();
    std::cout << "Resultados guardados en " << filename << std::endl;
}
