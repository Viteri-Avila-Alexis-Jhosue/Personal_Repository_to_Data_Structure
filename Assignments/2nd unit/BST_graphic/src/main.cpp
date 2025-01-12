/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles binarios
Alexis Viteri
Fecha de creacion:  11/01/2025
Ultima fecha de modificacion:   11/01/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Menu.h"
#include "../include/Tree.h"
#include "../include/Validation.h"
#include <iostream>
#include <string>
#include <vector>
int main(){
    Menu menu;
    Tree tree;
    Validation validation;
    int opcion=0;
    int id;
    menu.addOption("Insertar nodo");
    menu.addOption("Eliminar nodo");
    menu.addOption("Imprimir el Arbol");
    menu.addOption("Mostrar arbol en orden");
    menu.addOption("Mostrar arbol en preorden");
    menu.addOption("Mostrar arbol en postorden");
    menu.addOption("Salir");
    while (opcion != 6) {
        menu.displayMenu();
        opcion = menu.getSelectedOption();
        switch (opcion) {
            case 0:{
                id = validation.ingresarInt("Ingrese el ID del nodo a insertar: \t");
                tree.insert(id);
                system("pause");
                break;
            }
            case 1:{
                id = validation.ingresarInt("Ingrese el ID del nodo a eliminar: \t");
                if (tree.remove(id)) {
                    std::cout << "\nNodo eliminado correctamente del arbol.\n";
                } else {
                    std::cout << "\nNodo no encontrado.\n";
                }
                system("pause");
                break;
            }
            case 2:{
                tree.printTree();
                system("pause");
                break;
            }
            case 3:{
                tree.displayInOrder();
                system("pause");
                break;
            }
            case 4:{
                tree.displayPreOrder();
                system("pause");
                break;
            }
            case 5:{
                tree.displayPostOrder();
                system("pause");
                break;
            }
            case 6:{
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default:{
                std::cout << "Opción inválida. Intente nuevamente.\n";
                break;
            }
        }
    }
    tree.~Tree();
    return 0;
}
