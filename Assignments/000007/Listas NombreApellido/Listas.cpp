#include "Listas.h"
#include <iostream>
#include <algorithm>

Lista::Lista() : cabeza(nullptr) {}

Lista::~Lista() {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void Lista::agregarNodo(const std::string& nombre1, const std::string& nombre2, 
                        const std::string& apellido1, const std::string& apellido2) {
    Nodo* nuevoNodo = new Nodo(nombre1, nombre2, apellido1, apellido2);
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
    }
}

void Lista::eliminarCaracter(char caracter) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        for (std::string* campo : {&temp->nombre1, &temp->nombre2, &temp->apellido1, &temp->apellido2}) {
            campo->erase(std::remove(campo->begin(), campo->end(), caracter), campo->end());
        }
        temp = temp->siguiente;
    }
}

void Lista::imprimirLista() {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        std::cout << "Nombre1: " << temp->nombre1 << ", Nombre2: " << temp->nombre2
                  << ", Apellido1: " << temp->apellido1 << ", Apellido2: " << temp->apellido2 << std::endl;
        temp = temp->siguiente;
    }
}

