#include <iostream>
#include "../include/Laberinto.h"
#include "../include/Validation.h"

int main() {
    Validation validation;
    Laberinto* laberinto = nullptr;

    // Preguntar si desea generar un nuevo laberinto o cargar desde un archivo
    std::string respuesta;
    std::cout << "Seleccione una opcion:\n"
                 "1. Cargar laberinto desde archivo\n"
                 "2. Generar un nuevo laberinto\n"
                 "Opcion (1/2): ";
    std::cin >> respuesta;

    if (respuesta == "1") {
        std::string nombreArchivo;
        nombreArchivo="output//laberinto.txt";

        laberinto = new Laberinto(1);  // Se inicializa con un tamaño temporal
        if (!laberinto->cargarLaberintoDesdeArchivo(nombreArchivo)) {
            std::cout << "No se pudo cargar el laberinto. Saliendo del programa.\n";
            delete laberinto;
            return 1;
        }
        std::cout << "Laberinto cargado exitosamente:\n";
    } 
    else if (respuesta == "2") {
        int size = validation.ingresarInt("Ingrese el tamanio del laberinto (n x n): ");
        laberinto = new Laberinto(size);
        laberinto->generarLaberinto();
        std::cout << "Laberinto generado:\n";
    } 
    else {
        std::cout << "Opcion invalida. Saliendo del programa.\n";
        return 1;
    }

    laberinto->imprimirLaberinto();

    // Guardar el laberinto en un archivo
    laberinto->guardarLaberintoEnArchivo("output/laberinto.txt");

    if (laberinto->resolverLaberinto()) {
        std::cout << "Se encontro una solucion.\n";
    } else {
        std::cout << "No se encontro una solucion.\n";
    }

    delete laberinto; // Liberar memoria
    return 0;
}
