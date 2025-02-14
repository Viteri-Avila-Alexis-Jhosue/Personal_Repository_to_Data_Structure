#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "State.h"
const int TILE_SIZE = 80;
void drawBoard(sf::RenderWindow& window, const State& state, const sf::Texture& queenTexture, const std::vector<std::pair<int, int>>& moves, int arbX, int arbY);
void drawInfoPanel(sf::RenderWindow& window, const State& state, const sf::Font& font, int totalAttempts, const std::vector<std::pair<int, int>>& moves);
std::vector<std::pair<int, int>> calculateQueenMoves(int x, int y, int n);
void saveResultsToFile(const std::string& filename, int n, int attempts, const State& state);

#endif // GAME_H
