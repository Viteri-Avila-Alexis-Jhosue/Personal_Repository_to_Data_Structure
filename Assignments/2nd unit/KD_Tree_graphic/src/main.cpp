/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Menu.h"
#include "../include/KD_tree.h"
#include "../include/Validation.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    Menu menu;
    KD_tree tree;
    Validation validation;
    int opcion = 0;
    int x, y;

    // Agregar opciones al menú
    menu.addOption("Insertar nodo");
    menu.addOption("Eliminar nodo");
    menu.addOption("Imprimir el Arbol");
    menu.addOption("Mostrar arbol en orden");
    menu.addOption("Mostrar arbol en preorden");
    menu.addOption("Mostrar arbol en postorden");
    menu.addOption("Salir");

    // Bucle del menú principal
    while (opcion != 6) {
        menu.displayMenu();
        opcion = menu.getSelectedOption();

        switch (opcion) {
            case 0: {
                x = validation.ingresarInt("Ingrese la coordenada X del nodo: \t");
                y = validation.ingresarInt("\nIngrese la coordenada Y del nodo: \t");
                tree.insert(x, y);
                std::cout << "\nNodo (" << x << ", " << y << ") insertado correctamente.\n";
                system("pause");
                break;
            }
            case 1: {
                x = validation.ingresarInt("Ingrese la coordenada X del nodo a eliminar: \t");
                y = validation.ingresarInt("\nIngrese la coordenada Y del nodo a eliminar: \t");
                tree.remove(x, y);
                system("pause");
                break;
            }
            case 2: {
                tree.printTree();
                system("pause");
                break;
            }
            case 3: {
                std::cout << "\nArbol en orden:\n";
                tree.printInOrder();
                system("pause");
                break;
            }
            case 4: {
                std::cout << "\nArbol en preorden:\n";
                tree.printPreOrder();
                system("pause");
                break;
            }
            case 5: {
                std::cout << "\nArbol en postorden:\n";
                tree.printPostOrder();
                system("pause");
                break;
            }
            case 6: {
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                std::cout << "Opción invalida. Intente nuevamente.\n";
                break;
            }
        }
    }

    // Llamada explícita al destructor
    tree.~KD_tree();

    return 0;
}
