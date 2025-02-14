#include "../include/Graph.h"
#include "../include/Validation.h"
#include "../include/Menu.h"
#include <SFML/Graphics.hpp>

int main() {
    int choice, sizeChoice, repChoice, startVertex;
    Menu mainMenu, sizeMenu, repMenu;
    Validation validation;
    bool directed = false;
    int vertices;

    // Configurar menú principal
    mainMenu.addTitle("Seleccione el tipo de grafo:");
    mainMenu.addOption("Grafo Dirigido");
    mainMenu.addOption("Grafo No Dirigido");
    mainMenu.addOption("Salir");

    // Configurar menú de tamaño
    sizeMenu.addTitle("Seleccione el tamano del grafo:");
    sizeMenu.addOption("Grafo Pequeno (5 vertices)");
    sizeMenu.addOption("Grafo Grande (10 vertices)");
    sizeMenu.addOption("Atras");

    // Configurar menú de representación
    repMenu.addTitle("Seleccione la representacion:");
    repMenu.addOption("Representacion Logica");
    repMenu.addOption("Lista de Adyacencia");
    repMenu.addOption("Matriz de Adyacencia");

    while (true) {
        // Mostrar menú principal
        mainMenu.displayMenu();
        choice = mainMenu.getSelectedOption() + 1; // +1 para coincidir con las opciones originales

        if (choice == 3) break; // Salir
        directed = (choice == 1); // Grafo dirigido si la opción es 1

        // Mostrar menú de tamaño
        sizeMenu.displayMenu();
        sizeChoice = sizeMenu.getSelectedOption() + 1;

        if (sizeChoice == 3) continue; // Atrás
        vertices = (sizeChoice == 1) ? 5 : 10; // 5 o 10 vértices

        // Crear grafo y generar aristas aleatorias
        Graph g(vertices, directed);
        g.generateRandomEdges();

        // Mostrar menú de representación
        repMenu.displayMenu();
        repChoice = repMenu.getSelectedOption() + 1;

        // Crear ventana SFML para visualizar el grafo
        sf::RenderWindow window(sf::VideoMode(800, 600), "Grafo");
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);
            g.drawGraph(window, startVertex, repChoice, true);
            window.display();
        }

        // Mostrar lista o matriz de adyacencia según la selección
        if (repChoice == 2) {
            g.printAdjacencyList();
        } else if (repChoice == 3) {
            g.printAdjacencyMatrix();
        }
        startVertex=validation.ingresarInt("Ingrese el Vertice de Inicio para BFS: ");
        cout<<endl;
        if (startVertex >= 0 && startVertex < vertices) {
            g.bfs(startVertex);
            sf::RenderWindow bfsWindow(sf::VideoMode(800, 600), "BFS");
            while (bfsWindow.isOpen()) {
                sf::Event event;
                while (bfsWindow.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        bfsWindow.close();
                }

                bfsWindow.clear(sf::Color::White);
                g.drawGraph(bfsWindow, startVertex, repChoice, true);
                bfsWindow.display();
            }
        } else {
            cout << "Vertice de Inicio Invalido!" << endl;
            system("pause");
        }
    }

    return 0;
}