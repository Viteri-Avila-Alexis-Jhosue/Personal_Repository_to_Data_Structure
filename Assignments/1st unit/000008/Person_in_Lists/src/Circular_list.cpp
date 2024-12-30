/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Circular_list.h"
#include "../include/Nodo.h"
#include "../include/Encryption.h"
#include "../include/Validation.h"
#include "../include/Menu.h"
#include "../include/Person.h"

// Constructor
CircularList::CircularList() : head(nullptr), tail(nullptr) {}

// Destructor
CircularList::~CircularList() {
    if (head == nullptr) return;

    Nodo* current = head;
    do {
        Nodo* next = current->getNext();
        delete current;
        current = next;
    } while (current != head);

    head = tail = nullptr;
}

// Insertar al inicio
void CircularList::insertFront(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email) {
    Nodo* newNode = new Nodo(id, name1, name2, lastname1, lastname2, email);

    if (head == nullptr) { // Lista vacía
        head = tail = newNode;
        head->setNext(head);
        head->setPrev(head);
    } else {
        newNode->setNext(head);
        newNode->setPrev(tail);
        head->setPrev(newNode);
        tail->setNext(newNode);
        head = newNode;
    }
}

// Insertar al final
void CircularList::insertBack(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email) {
    Nodo* newNode = new Nodo(id, name1, name2, lastname1, lastname2, email);

    if (head == nullptr) { // Lista vacía
        head = tail = newNode;
        head->setNext(head);
        head->setPrev(head);
    } else {
        newNode->setNext(head);
        newNode->setPrev(tail);
        tail->setNext(newNode);
        head->setPrev(newNode);
        tail = newNode;
    }
}

// Eliminar un nodo por ID
bool CircularList::remove(int id) {
    if (head == nullptr) return false; // Lista vacía

    Nodo* current = head;
    do {
        if (current->getId() == id) {
            // Caso único elemento
            if (current == head && current == tail) {
                delete current;
                head = tail = nullptr;
                return true;
            }
            // Caso nodo inicial
            else if (current == head) {
                head = head->getNext();
                head->setPrev(tail);
                tail->setNext(head);
            }
            // Caso nodo final
            else if (current == tail) {
                tail = tail->getPrev();
                tail->setNext(head);
                head->setPrev(tail);
            }
            // Caso nodo intermedio
            else {
                current->getPrev()->setNext(current->getNext());
                current->getNext()->setPrev(current->getPrev());
            }
            delete current;
            return true;
        }
        current = current->getNext();
    } while (current != head);

    return false; // No se encontró el nodo
}

// Buscar un nodo por ID
bool CircularList::search(int id) {
    if (head == nullptr) return false; // Lista vacía

    Nodo* current = head;
    do {
        if (current->getId() == id) {
            return true;
        }
        current = current->getNext();
    } while (current != head);

    return false; // No se encontró
}

// Mostrar todos los elementos
void CircularList::display() const {
    if (head == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo* current = head;
    do {
        cout << "ID: " << current->getId() << ", "
             << "Name: " << current->getName1() << " " << current->getName2() << " "
             << current->getLastname1() << " " << current->getLastname2() << ", "
             << "Email: " << current->getInstitucionalEmail() << endl;
        current = current->getNext();
    } while (current != head);
}
void CircularList::encrypt(int clave) {
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
void CircularList::decrypt(int clave) {
    if (head == nullptr) return;
    Nodo* current = head;
    do {
        current->setName1(Encryption::decryptCesar(current->getName1(), clave));
        current->setName2(Encryption::decryptCesar(current->getName2(), clave));
        current->setLastname1(Encryption::decryptCesar(current->getLastname1(), clave));
        current->setLastname2(Encryption::decryptCesar(current->getLastname2(), clave));
        current->setInstitucionalEmail(Encryption::decryptCesar(current->getInstitucionalEmail(), clave));
        current = current->getNext();
    } while (current != head);
}
void CircularList::handleMenu(Nodo*& head, const string& institution) {
    Validation validation;
    Menu menu_circular;
    menu_circular.addOption("Ingresar los Datos");
    menu_circular.addOption("Ver los nodos");
    menu_circular.addOption("Eliminar un nodo");
    menu_circular.addOption("Buscar un nodo");
    menu_circular.addOption("Salir");
    menu_circular.displayMenu();
    Person person;
    while (true) {
        int option = menu_circular.getSelectedOption();
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
            case 1:
                display();
                break;
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