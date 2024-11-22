/*
Universidad de las Fuerzas Armadas ESPE
Programa con operaciones de listas
Alexis Viteri
Fecha de creacion:  18/11/2024
Ultima fecha de modificacion:   18/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Listas.h"
#include "../include/Person.h"
#include "../include/Validation.h"
#include <iostream>
#include <string>

void showMenu() {
    std::cout << "\n--- Menu ---\n";
    std::cout << "1. Agregar Person al inicio\n";
    std::cout << "2. Agregar Person al final\n";
    std::cout << "3. Mostrar lista\n";
    std::cout << "4. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Validation validacion;
    Person person;
    List<Person> myList;
    string espe = "@espe.edu.ec";

    int opcion;
    do {
        showMenu();
        opcion = validacion.ingresarInt("");

        switch (opcion) {
            case 1:
            case 2: {
                std::string nombre1 = validacion.ingresarStringConEspacios("Ingrese primer nombre: ");
                std::string nombre2 = validacion.ingresarStringConEspacios("Ingrese segundo nombre: ");
                std::string apellido1 = validacion.ingresarStringConEspacios("Ingrese primer apellido: ");
                std::string apellido2 = validacion.ingresarStringConEspacios("Ingrese segundo apellido: ");
                std::string correo = person.createInstitutionalEmail(nombre1,nombre2,apellido1, espe);

                Person p(nombre1, nombre2, apellido1, apellido2, correo);

                if (opcion == 1) {
                    myList.addToHead(p);
                } else {
                    myList.addToTail(p);
                }
                break;
            }
            case 3:
                myList.display();
                break;
            case 4:
                std::cout << "\nSaliendo...\n";
                break;
            default:
                std::cout << "\nOpcion no valida.\n";
        }
    } while (opcion != 4);

    return 0;
}
