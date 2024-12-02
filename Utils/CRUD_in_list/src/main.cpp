/*
Universidad de las Fuerzas Armadas ESPE
Programa generico para el uso de listas
Alexis Viteri
Fecha de creacion:  24/10/2024
Ultima fecha de modificacion:   24/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Lista.h"
#include <iostream>

void mostrarMenu() {
    std::cout << "\n--- MENU ---\n";
    std::cout << "1. Insertar elemento\n";
    std::cout << "2. Actualizar elemento\n";
    std::cout << "3. Eliminar elemento\n";
    std::cout << "4. Mostrar elementos\n";
    std::cout << "5. Buscar elemento\n";    
    std::cout << "6. Salir del programa\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    // Crear una lista de enteros
    Lista lista;
    int opcion;
    int probar =1;
    int probar1 =10;
    int probar2 =100;
    int probar3 =1000;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1: {
                int dato;
                std::cout << "Ingrese el elemento a insertar: ";
                std::cin >> dato;
                lista.insertar(dato);
                break;
            }
            case 2: {
                int datoAntiguo, datoNuevo;
                std::cout << "Ingrese el elemento a actualizar: ";
                std::cin >> datoAntiguo;
                std::cout << "Ingrese el nuevo valor: ";
                std::cin >> datoNuevo;
                lista.actualizar(datoAntiguo, datoNuevo);
                break;
            }
            case 3: {
                int dato;
                std::cout << "Ingrese el elemento a eliminar: ";
                std::cin >> dato;
                lista.eliminar(dato);
                break;
            }
            case 4: {
                std::cout << "Elementos de la lista: ";
                lista.mostrar();
                break;
            }
            case 5: {
                int dato;
                std::cout << "Ingrese el elemento a buscar: ";
                std::cin >> dato;
                if (lista.buscar(dato)) {
                    std::cout << "El elemento " << dato << " está en la lista." << std::endl;
                } else {
                    std::cout << "El elemento " << dato << " no se encuentra en la lista." << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            }
            default:
                std::cout << "Opción no válida. Intente nuevamente." << std::endl;
        }
    } while (opcion != 6);

    return 0;
}
