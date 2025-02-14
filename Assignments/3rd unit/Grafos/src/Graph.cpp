#include "../include/Graph.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>

Graph::Graph(int vertices, bool directed) : V(vertices), directed(directed) {
    adjList.resize(V);
    adjMatrix.resize(V, std::vector<int>(V, 0));
    x.resize(V);
    y.resize(V);
}

void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjMatrix[u][v] = 1;
    if (!directed) {
        adjList[v].push_back(u);
        adjMatrix[v][u] = 1;
    }
}

void Graph::generateRandomEdges() {
    srand(time(0));
    for (int i = 0; i < V; ++i) {
        int edges = rand() % V;
        for (int j = 0; j < edges; ++j) {
            int neighbor = rand() % V;
            if (neighbor != i) {
                addEdge(i, neighbor);
            }
        }
    }
}

void Graph::drawGraph(sf::RenderWindow& window, int startVertex, int repChoice, bool highlightBFS) {
    int radius = 20;
    if (x[0] == 0 && y[0] == 0) {
        for (int i = 0; i < V; ++i) {
            x[i] = rand() % (800 - 2 * radius) + radius;
            y[i] = rand() % (600 - 2 * radius) + radius;
        }
    }
    for (int u = 0; u < V; ++u) {
        for (int v : adjList[u]) {
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x[u], y[u]), sf::Color::Black),
                sf::Vertex(sf::Vector2f(x[v], y[v]), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);
        }
    }

    // Dibujar nodos
    for (int i = 0; i < V; ++i) {
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(x[i] - radius, y[i] - radius);
        window.draw(circle);

        if (!font.loadFromFile("output//arial.ttf")) {
            std::cerr << "Error cargando la fuente\n";
            return;
        }
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x[i] - 5, y[i] - 10);
        window.draw(text);
    }
}

void Graph::bfs(int start) {
    visited.assign(V, false);
    bfsOrder.clear();
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        bfsOrder.push_back(u);

        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void Graph::printAdjacencyList() {
    std::cout << "Lista de Adyacencia:\n";
    for (int i = 0; i < V; i++) {
        std::cout << i << ": ";
        for (int neighbor : adjList[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << "\n";
    }
}

void Graph::printAdjacencyMatrix() {
    std::cout << "Matriz de Adyacencia:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}