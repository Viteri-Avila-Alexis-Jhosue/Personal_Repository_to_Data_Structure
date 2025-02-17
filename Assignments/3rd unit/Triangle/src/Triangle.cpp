#include "../include/Triangle.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

Triangle::Triangle(int initialNumber, int increment) 
    : initialNumber(initialNumber), increment(increment) {}

void Triangle::generateNumbers() {
    numbers.clear();
    for (int i = 0; i < 6; ++i) {
        numbers.push_back(initialNumber + i * increment);
    }
}

void Triangle::solveMagicTriangle() {
    // Organiza los números en el triángulo mágico
    triangle.clear();
    triangle.push_back({numbers[0]});           // a
    triangle.push_back({numbers[5], numbers[3]}); // f, d
    triangle.push_back({numbers[2], numbers[1], numbers[4]}); // c, b, e
}

bool Triangle::isMagicTriangle() const {
    // Calcula las sumas de los tres lados del triángulo
    int sum1 = triangle[0][0] + triangle[1][0] + triangle[2][0]; // a + f + e
    int sum2 = triangle[0][0] + triangle[1][1] + triangle[2][2]; // a + d + c
    int sum3 = triangle[2][0] + triangle[2][1] + triangle[2][2]; // f + d + b

    if ((sum1 == sum2) && (sum2 == sum3)) {
        std::cout << "\nTodas las sumas son iguales a: " << sum1 << std::endl;
    }
    return (sum1 == sum2) && (sum2 == sum3);
}
void Triangle::displayTriangle() const {
    // Crear una ventana SFML más grande
    sf::RenderWindow window(sf::VideoMode(600, 500), "Triangulo Magico");

    // Cargar la fuente para el texto
    sf::Font font;
    if (!font.loadFromFile("output//arial.ttf")) {
        std::cerr << "Error cargando la fuente." << std::endl;
        return;
    }

    // Configurar el texto
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // Posiciones para los números del triángulo (ajustadas)
    std::vector<sf::Vector2f> positions = {
        {300, 50},   // a (vértice superior)
        {150, 200},  // f (izquierda)
        {450, 200},  // d (derecha)
        {100, 400},  // c (base izquierda)
        {300, 400},  // b (base centro)
        {500, 400}   // e (base derecha)
    };

    // Crear líneas para formar el triángulo
    sf::VertexArray lines(sf::LinesStrip, 7);
    lines[0].position = positions[0]; // a -> f
    lines[1].position = positions[1]; // f -> c
    lines[2].position = positions[3]; // c -> e
    lines[3].position = positions[5]; // e -> d
    lines[4].position = positions[2]; // d -> a
    lines[5].position = positions[0]; // a -> f (cerrar el triángulo)
    lines[6].position = positions[1]; // f -> c (cerrar el triángulo)
    for (int i = 0; i < 7; ++i) {
        lines[i].color = sf::Color::Green;
    }

    // Calcular el mensaje de la suma solo una vez
    std::string resultText;
    if (isMagicTriangle()) {
        int magicSum = triangle[0][0] + triangle[1][0] + triangle[2][0];
        resultText = "Suma: " + std::to_string(magicSum);
    } else {
        resultText = "No se pudo .";
    }

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Limpiar la ventana
        window.clear(sf::Color::Black);

        // Dibujar las líneas del triángulo
        window.draw(lines);

        // Dibujar los números del triángulo dentro de círculos
        const std::vector<std::string> triangleNumbers = {
            std::to_string(triangle[0][0]), // a
            std::to_string(triangle[1][0]), // f
            std::to_string(triangle[1][1]), // d
            std::to_string(triangle[2][0]), // c
            std::to_string(triangle[2][1]), // b
            std::to_string(triangle[2][2])  // e
        };

        for (size_t i = 0; i < positions.size(); ++i) {
            // Dibujar el círculo
            sf::CircleShape circle(30);
            circle.setFillColor(sf::Color::Blue);
            circle.setOutlineColor(sf::Color::White);
            circle.setOutlineThickness(2);
            circle.setPosition(positions[i].x - 30, positions[i].y - 30);
            window.draw(circle);

            // Dibujar el número
            text.setString(triangleNumbers[i]);
            text.setPosition(positions[i].x - 10, positions[i].y - 15);
            window.draw(text);
        }

        // Dibujar el mensaje de la suma
        text.setString(resultText);
        text.setPosition(50, 450);
        window.draw(text);

        // Mostrar el contenido en la ventana
        window.display();
    }
}