/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#include <stdio.h>
#include "../include/Circular_list.h"
#include "../include/Double_list.h"
#include "../include/Simple_list.h"
#include "../include/Menu.h"
#include "../include/Nodo.h"
#include "../include/Person.h"
#include "../include/Validation.h"
#include <iostream>
using namespace std;

int main() {
    Validation validation;
    Nodo* head1 = nullptr;
    Nodo* head2 = nullptr;
    Nodo* head3 = nullptr;
    string institution = "@espe.edu.ec";

    // Crear listas
    SimpleList simple_list;
    DoubleList double_list;
    CircularList circular_list;

    // Menú principal
    Menu main_menu;
main_menu.addOption("Lista Simple");
main_menu.addOption("Lista Doble");
main_menu.addOption("Lista Circular");
main_menu.addOption("Salir");

do {  // Inicia el ciclo do-while
    main_menu.displayMenu();
    int option = main_menu.getSelectedOption();
    switch (option) {
        case 0:  // Lista Simple
            simple_list.handleMenu(head1, institution);
            break;
        case 1:  // Lista Doble
            double_list.handleMenu(head2, institution);
            break;
        case 2:  // Lista Circular
            circular_list.handleMenu(head3, institution);
            break;
        case 3:  // Salir
            cout << "Saliendo del programa..." << endl;
            return 0;  // Termina el programa
        default:
            cout << "Opción no válida." << endl;
    }
} while (true);  // El ciclo sigue ejecutándose hasta que el `return` sea ejecutado

}
