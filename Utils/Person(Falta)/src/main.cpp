/*
Universidad de las Fuerzas Armadas ESPE
Libreria para operaciones con datos de personas
Alexis Viteri
Fecha de creacion:  21/11/2024
Ultima fecha de modificacion:   24/11/2024
Estructura de Datos
NRC:  1978
*/
#include <iostream>
#include <list>
#include "../include/Person.h"

using namespace std;

int main() {
    Person person;
    list<Nodo> nodos;  // Lista de nodos (correos ya registrados)
    string userChoice;

    // Bucle para ingresar datos y generar correos institucionales
    do {
        string name1, name2, lastname, institution = "@espe.edu.ec";

        // Ingresar datos del usuario
        cout << "Ingrese el primer nombre: ";
        cin >> name1;

        cout << "Ingrese el segundo nombre: ";
        cin >> name2;

        cout << "Ingrese el apellido: ";
        cin >> lastname;

        // Generar correo institucional único para el nuevo usuario
        string newEmail = person.createInstitutionalEmailList(name1, name2, lastname, institution, nodos);

        // Agregar el correo generado a la lista de nodos (correos registrados)
        Nodo nuevoNodo;
        nuevoNodo.correo = newEmail;
        nodos.push_back(nuevoNodo);

        // Mostrar el correo institucional generado
        cout << "Correo institucional generado: " << newEmail << endl;

        // Preguntar si el usuario desea ingresar otro usuario
        cout << "¿Desea ingresar otro usuario? (si/no): ";
        cin >> userChoice;

    } while (userChoice == "si" || userChoice == "sí" || userChoice == "SI");

    return 0;
}
