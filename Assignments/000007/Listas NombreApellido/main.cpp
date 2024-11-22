#include "Listas.h"
#include <iostream>
#include <windows.h> 
int main() {
    SetConsoleOutputCP(CP_UTF8);
    Lista lista;
    int opcion;
    char caracter;

    do {
        std::cout << "\nMenú:\n";
        std::cout << "1. Agregar nodo\n";
        std::cout << "2. Eliminar caracter de todos los nodos\n";
        std::cout << "3. Imprimir lista\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                std::string nombre1, nombre2, apellido1, apellido2;
                std::cout << "Ingrese el primer nombre: ";
                std::cin >> nombre1;
                std::cout << "Ingrese el segundo nombre: ";
                std::cin >> nombre2;
                std::cout << "Ingrese el primer apellido: ";
                std::cin >> apellido1;
                std::cout << "Ingrese el segundo apellido: ";
                std::cin >> apellido2;
                lista.agregarNodo(nombre1, nombre2, apellido1, apellido2);
                break;
            }
            case 2:
                std::cout << "Ingrese el caracter a eliminar: ";
                std::cin >> caracter;
                lista.eliminarCaracter(caracter);
                break;
            case 3:
                lista.imprimirLista();
                break;
            case 4:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 4);

    return 0;
}
