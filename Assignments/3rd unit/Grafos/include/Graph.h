// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class Graph {
private:
    std::vector<float> x, y;  // Posiciones de los nodos
    int V;
    vector<vector<int>> adjList;
    vector<vector<int>> adjMatrix;
    bool directed;
    vector<sf::Vector2f> positions;
    sf::Font font;
    vector<bool> visited;
    vector<int> bfsOrder;

public:
    Graph(int vertices, bool isDirected);
    void addEdge(int u, int v);
    void generateRandomEdges();
    void drawGraph(sf::RenderWindow& window, int startVertex = -1, int repChoice = 1, bool highlightBFS = false);
    void bfs(int start);
    void printAdjacencyList();
    void printAdjacencyMatrix();
};

#endif