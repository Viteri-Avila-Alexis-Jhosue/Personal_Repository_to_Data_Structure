/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Double_list.h"
#include "../include/Nodo.h"
#include "../include/Encryption.h"
#include "../include/Validation.h"
#include "../include/Menu.h"
#include "../include/Person.h"
// Constructor
DoubleList::DoubleList() : head(nullptr), tail(nullptr) {}

// Destructor
DoubleList::~DoubleList() {
    Nodo* current = head;
    while (current != nullptr) {
        Nodo* next = current->getNext();
        delete current;
        current = next;
    }
}

// Insertar al inicio
void DoubleList::insertFront(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email) {
    Nodo* newNode = new Nodo(id, name1, name2, lastname1, lastname2, email);
    if (head == nullptr) { // Lista vacía
        head = tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
}

// Insertar al final
void DoubleList::insertBack(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email) {
    Nodo* newNode = new Nodo(id, name1, name2, lastname1, lastname2, email);
    if (tail == nullptr) { // Lista vacía
        head = tail = newNode;
    } else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
}

// Eliminar un nodo por ID
bool DoubleList::remove(int id) {
    if (head == nullptr) return false; // Lista vacía

    Nodo* current = head;
    while (current != nullptr && current->getId() != id) {
        current = current->getNext();
    }

    if (current == nullptr) return false; // No se encontró el nodo

    // Caso 1: Nodo es el único elemento
    if (current == head && current == tail) {
        head = tail = nullptr;
    }
    // Caso 2: Nodo es el primero
    else if (current == head) {
        head = head->getNext();
        head->setPrev(nullptr);
    }
    // Caso 3: Nodo es el último
    else if (current == tail) {
        tail = tail->getPrev();
        tail->setNext(nullptr);
    }
    // Caso 4: Nodo está en el medio
    else {
        current->getPrev()->setNext(current->getNext());
        current->getNext()->setPrev(current->getPrev());
    }

    delete current;
    return true;
}

// Buscar un nodo por ID
bool DoubleList::search(int id) {
    Nodo* current = head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

// Mostrar de inicio a fin
void DoubleList::displayForward() const {
    Nodo* current = head;
    while (current != nullptr) {
        cout << "ID: " << current->getId() << ", "
             << "Name: " << current->getName1() << " " << current->getName2() << " "
             << current->getLastname1() << " " << current->getLastname2() << ", "
             << "Email: " << current->getInstitucionalEmail() << endl;
        current = current->getNext();
    }
}

// Mostrar de fin a inicio
void DoubleList::displayBackward() const {
    Nodo* current = tail;
    while (current != nullptr) {
        cout << "ID: " << current->getId() << ", "
             << "Name: " << current->getName1() << " " << current->getName2() << " "
             << current->getLastname1() << " " << current->getLastname2() << ", "
             << "Email: " << current->getInstitucionalEmail() << endl;
        current = current->getPrev();
    }
}
void DoubleList::encrypt(int clave) {
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
void DoubleList::decrypt(int clave) {
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
void DoubleList::handleMenu(Nodo*& head, const string& institution) {
    Validation validation;
    Menu menu_double;
    menu_double.addOption("Ingresar los Datos");
    menu_double.addOption("Ver los nodos");
    menu_double.addOption("Eliminar un nodo");
    menu_double.addOption("Buscar un nodo");
    menu_double.addOption("Salir");
    menu_double.displayMenu();

    Person person;
    while (true) {
        int option = menu_double.getSelectedOption();
        switch (option) {
            case 0: { // Insertar nodo
                Menu insertMenu;
                insertMenu.addOption("Al inicio");
                insertMenu.addOption("Al final");
                insertMenu.displayMenu();
                int subOption = insertMenu.getSelectedOption();

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

                if (subOption == 0) {
                    insertFront(id, name1, name2, lastname1, lastname2, email);
                } else if (subOption == 1) {
                    insertBack(id, name1, name2, lastname1, lastname2, email);
                }
                break;
            }
            case 1: {
                Menu directionMenu;
                directionMenu.addOption("De inicio a fin");
                directionMenu.addOption("De fin a inicio");
                directionMenu.displayMenu();
                int direction = directionMenu.getSelectedOption();

                if (direction == 0) {
                    displayForward();
                } else if (direction == 1) {
                    displayBackward();
                } else {
                    cout << "Opción no válida." << endl;
                 }
            break;
            }
            case 2: {
                int id = validation.ingresarInt("Ingrese el número de cédula a eliminar");
                if (remove(id)) {
                    cout << "Nodo eliminado con éxito." << endl;
                } else {
                    cout << "Nodo no encontrado." << endl;
                }
                break;
            }
            case 3: {
                int id = validation.ingresarInt("Ingrese el número de cédula a buscar");
                if (search(id)) {
                    cout << "Nodo encontrado." << endl;
                } else {
                    cout << "Nodo no encontrado." << endl;
                }
                break;
            }
            case 4:
                return; // Salir del menú
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
        }
    }
}