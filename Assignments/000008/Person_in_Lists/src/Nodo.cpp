/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Nodo.h"
#include "../include/Encryption.h"

// Constructor
Nodo::Nodo(int id, string name1, string name2, string lastname1, string lastname2, string institucionalEmail)
    : id(id), name1(name1), name2(name2), lastname1(lastname1), lastname2(lastname2),
      institucionalEmail(institucionalEmail), next(nullptr), prev(nullptr) {}

// Destructor
Nodo::~Nodo() {
    next = nullptr;
    prev = nullptr;
}

// Getters
int Nodo::getId() const {
    return id;
}

string Nodo::getName1() const {
    return name1;
}

string Nodo::getName2() const {
    return name2;
}

string Nodo::getLastname1() const {
    return lastname1;
}

string Nodo::getLastname2() const {
    return lastname2;
}

string Nodo::getInstitucionalEmail() const {
    return institucionalEmail;
}

Nodo* Nodo::getNext() const {
    return next;
}

Nodo* Nodo::getPrev() const {
    return prev;
}

// Setters
void Nodo::setId(int newId) {
    id = newId;
}

void Nodo::setName1(const string& newName1) {
    name1 = newName1;
}

void Nodo::setName2(const string& newName2) {
    name2 = newName2;
}

void Nodo::setLastname1(const string& newLastname1) {
    lastname1 = newLastname1;
}

void Nodo::setLastname2(const string& newLastname2) {
    lastname2 = newLastname2;
}

void Nodo::setInstitucionalEmail(const string& newEmail) {
    institucionalEmail = newEmail;
}

void Nodo::setNext(Nodo* newNext) {
    next = newNext;
}

void Nodo::setPrev(Nodo* newPrev) {
    prev = newPrev;
}
void Nodo::encriptarDatos(int clave) {
    name1 = Encryption::cesar(name1, clave);
    name2 = Encryption::cesar(name2, clave);
    lastname1 = Encryption::cesar(lastname1, clave);
    lastname2 = Encryption::cesar(lastname2, clave);
    institucionalEmail = Encryption::cesar(institucionalEmail, clave);
}