#include "../include/Closed_Hash.h"
#include "../include/Node.h"
#include <SFML/Graphics.hpp>
#include <iostream>

template <typename T>
Closed_Hash<T>::Closed_Hash(int size, int method) : size(size), method(method) {
    table.resize(size, T(-1, "")); // Inicializar con objetos Node inválidos
    occupied.resize(size, false);
}

template <typename T>
int Closed_Hash<T>::primaryHash(T key) {
    return std::hash<int>{}(key.getIndex()) % size;
}

template <typename T>
int Closed_Hash<T>::secondaryHash(T key) {
    return 7 - (std::hash<int>{}(key.getIndex()) % 7);
}

template <typename T>
int Closed_Hash<T>::probe(int index, int attempt, T key) {
    if (method == 0) {
        return (index + attempt) % size;
    } else if (method == 1) {
        return (index + attempt * attempt) % size;
    } else if (method == 2) {
        return (index + attempt * secondaryHash(key)) % size;
    }
    return index;
}

template <typename T>
void Closed_Hash<T>::insert(T key) {
    int index = primaryHash(key);
    int attempt = 0;

    while (occupied[index]) {
        attempt++;
        index = probe(primaryHash(key), attempt, key);
        if (attempt >= size) {
            std::cout << "Error: Tabla llena, no se puede insertar " << key.getWord() << std::endl;
            return;
        }
    }

    table[index] = key;
    occupied[index] = true;
}

template<typename T>
int Closed_Hash<T>::convert_string_to_int(std::string cad) {
    size_t hashValue = 0;
    for (auto it = cad.rbegin(); it != cad.rend(); ++it) {
        size_t temp = static_cast<size_t>(*it);
        temp = (temp + hashValue);
        if (it + 1 != cad.rend()) {
            temp = (temp << 4);
            hashValue = temp;
        } else {
            hashValue = temp;
        }
    }
    return static_cast<int>(hashValue);
}


template <typename T>
void Closed_Hash<T>::display() {
    sf::RenderWindow window(sf::VideoMode(1000, 650), "Hash Table Visualization");

    sf::Font font;
    if (!font.loadFromFile("output//arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        int cellWidth = 150;
        int cellHeight = 75;
        int startX = 50;
        int startY = 50;

        for (int i = 0; i < size; ++i) {
            // Dibujar la celda
            sf::RectangleShape cell(sf::Vector2f(cellWidth, cellHeight));
            cell.setPosition(startX + (i % 5) * (cellWidth + 10), startY + (i / 5) * (cellHeight + 10));
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            cell.setFillColor(sf::Color::Transparent);
            window.draw(cell);

            // Crear texto para el número de posición
            sf::Text positionText;
            positionText.setFont(font);
            positionText.setCharacterSize(14); // Tamaño más pequeño para el número de posición
            positionText.setFillColor(sf::Color::Blue); // Color azul para el número de posición
            positionText.setString("Pos: " + std::to_string(i)); // Mostrar el número de posición
            positionText.setPosition(startX + (i % 5) * (cellWidth + 10) + 5, startY + (i / 5) * (cellHeight + 10) + 5);
            window.draw(positionText);

            // Crear texto para el contenido de la celda
            sf::Text contentText;
            contentText.setFont(font);
            contentText.setCharacterSize(20); // Tamaño más grande para el contenido
            contentText.setFillColor(sf::Color::Black); // Color negro para el contenido

            if (occupied[i]) {
                contentText.setString(table[i].getWord()); // Mostrar el valor almacenado
            } else {
                contentText.setString("+"); // Mostrar "+" si está vacía
            }

            // Posicionar el contenido debajo del número de posición
            contentText.setPosition(startX + (i % 5) * (cellWidth + 10) + 10, startY + (i / 5) * (cellHeight + 10) + 25);
            window.draw(contentText);
        }

        window.display();
    }
}
// Instanciación explícita para evitar problemas con templates en archivos separados
template class Closed_Hash<Node>;