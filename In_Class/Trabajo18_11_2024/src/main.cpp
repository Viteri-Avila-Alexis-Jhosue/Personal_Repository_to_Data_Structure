/*
Universidad de las Fuerzas Armadas ESPE
Programa con operaciones de listas
Alexis Viteri
Fecha de creacion:  18/11/2024
Ultima fecha de modificacion:   18/11/2024
Estructura de Datos
NRC:  1978
*/
#include "Listas.h"
#include "../include/Validacion.h"
#include <string>
#include <iostream>

void showMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Agregar al inicio\n";
    std::cout << "2. Agregar al final\n";
    std::cout << "3. Mostrar lista\n";
    std::cout << "4. Actualizar elemento\n";
    std::cout << "5. Eliminar elemento\n";
    std::cout << "6. Buscar elemento\n";
    std::cout << "7. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Validacion validacion;
    List<std::string> myList;

    int opcion;
    do {
        showMenu();
        opcion = validacion.ingresarInt("");

        switch (opcion) {
            case 1: {
                std::string value = validacion.ingresarString("\nIngrese un valor: ");
                myList.addToHead(value);
                break;
            }
            case 2: {
                std::string value = validacion.ingresarString("\nIngrese un valor: ");
                myList.addToTail(value);
                break;
            }
            case 3: {
                std::cout << "\nContenido de la lista: ";
                myList.display();
                break;
            }
            case 4: {
                std::string target = validacion.ingresarString("\nIngrese el valor a actualizar: ");
                std::string newValue = validacion.ingresarString("\nIngrese el nuevo valor: ");
                myList.update([target](const std::string& data) { return data == target; }, newValue);
                break;
            }
            case 5: {
                std::string target = validacion.ingresarString("\nIngrese el valor a eliminar: ");
                myList.remove([target](const std::string& data) { return data == target; });
                break;
            }
            case 6: {
                std::string target = validacion.ingresarString("\nIngrese el valor a buscar: ");
                std::string* result = myList.search([target](const std::string& data) { return data == target; });
                if (result) {
                    std::cout << "\nElemento encontrado: " << *result << std::endl;
                } else {
                    std::cout << "\nElemento no encontrado.\n";
                }
                break;
            }
            case 7:
                std::cout << "\nSaliendo del programa...\n";
                break;
            default:
                std::cout << "\nOpcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 7);

    return 0;
}
