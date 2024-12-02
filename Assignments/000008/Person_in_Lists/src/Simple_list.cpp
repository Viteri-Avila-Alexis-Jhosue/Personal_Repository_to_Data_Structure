/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Simple_list.h"
#include "../include/Nodo.h"
#include "../include/Encryption.h"
#include "../include/Person.h"
#include "../include/Menu.h"
// Constructor
SimpleList::SimpleList() : head(nullptr) {}

// Destructor
SimpleList::~SimpleList() {
    Nodo* current = head;
    while (current != nullptr) {
        Nodo* next = current->getNext();
        delete current;
        current = next;
    }
}

// Insertar al final
void SimpleList::insert(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email) {
    Nodo* newNode = new Nodo(id, name1, name2, lastname1, lastname2, email);
    if (head == nullptr) {
        head = newNode;
    } else {
        Nodo* temp = head;
        while (temp->getNext() != nullptr) {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }
}

// Eliminar un nodo por ID
bool SimpleList::remove(int id) {
    if (head == nullptr) {
        return false;
    }

    if (head->getId() == id) {
        Nodo* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    Nodo* current = head;
    while (current->getNext() != nullptr && current->getNext()->getId() != id) {
        current = current->getNext();
    }

    if (current->getNext() != nullptr) {
        Nodo* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
        return true;
    }
    return false; // No se encontró el nodo
}

// Buscar un nodo por ID
bool SimpleList::search(int id) {
    Nodo* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Mostrar todos los nodos
void SimpleList::display() const {
    Nodo* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->getId() << ", "
             << "Name: " << current->getName1() << " " << current->getName2() << " "
             << current->getLastname1() << " " << current->getLastname2() << ", "
             << "Email: " << current->getInstitucionalEmail() << endl;
        current = current->getNext();
    }
}
void SimpleList::encrypt(int clave) {
    Nodo* current = head;
    while (current) {
        current->setName1(Encryption::cesar(current->getName1(), clave));
        current->setName2(Encryption::cesar(current->getName2(), clave));
        current->setLastname1(Encryption::cesar(current->getLastname1(), clave));
        current->setLastname2(Encryption::cesar(current->getLastname2(), clave));
        current->setInstitucionalEmail(Encryption::cesar(current->getInstitucionalEmail(), clave));
        current = current->getNext();
    }
}
void SimpleList::decrypt(int clave) {
    Nodo* current = head;
    while (current != nullptr) {
        current->setName1(Encryption::decryptCesar(current->getName1(), clave));
        current->setName2(Encryption::decryptCesar(current->getName2(), clave));
        current->setLastname1(Encryption::decryptCesar(current->getLastname1(), clave));
        current->setLastname2(Encryption::decryptCesar(current->getLastname2(), clave));
        current->setInstitucionalEmail(Encryption::decryptCesar(current->getInstitucionalEmail(), clave));
        current = current->getNext();
    }
}
void SimpleList::handleMenu(Nodo*& head, const string& institution) {
    Validation validation;
    Person person;

    do {  // Inicia el ciclo do-while
        Menu menu_simple;
        menu_simple.addOption("Ingresar los Datos");
        menu_simple.addOption("Ver los nodos");
        menu_simple.addOption("Eliminar un nodo");
        menu_simple.addOption("Buscar un nodo");
        menu_simple.addOption("Salir");
        menu_simple.displayMenu();
        
        int option = menu_simple.getSelectedOption(); // Obtiene la opción seleccionada
        switch (option) {
            case 0: { // Insertar nodo
                bool validId = false;
                int id;
                while (!validId) {
                    id = validation.ingresarInt("Ingrese su número de cédula");
                    validId = person.validateId(id);
                }
                string name1 = validation.ingresarStringConEspacios("Ingrese el primer nombre");
                string name2 = validation.ingresarStringConEspacios("Ingrese el segundo nombre");
                string lastname1 = validation.ingresarStringConEspacios("Ingrese el primer apellido");
                string lastname2 = validation.ingresarStringConEspacios("Ingrese el segundo apellido");
                string email = person.createInstitutionalEmailList(name1, name2, lastname1, institution, head);
                insert(id, name1, name2, lastname1, lastname2, email);
                break;
            }
            case 1:  // Ver los nodos
                display();
                break;
            case 2: {  // Eliminar nodo
                int id = validation.ingresarInt("Ingrese el número de cédula a eliminar");
                bool flag = remove(id);
                if(!flag){
                    printf("Nodo no encontrado\n");
                }else{
                    printf("Nodo eliminado satisfactoriamente\n");
                }
                break;
            }
            case 3: {  // Buscar nodo
                int id = validation.ingresarInt("Ingrese el número de cédula a buscar");
                if (search(id)) {
                    cout << "Nodo encontrado." << endl;
                } else {
                    cout << "Nodo no encontrado." << endl;
                }
                break;
            }
            case 4:  // Salir
                return;  // Salir del ciclo y la función
            default:
                cout << "Opción no válida." << endl;
        }
    } while (true);  // El ciclo sigue hasta que el `return` sea ejecutado
}
