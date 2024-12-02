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
#include "../include/Nodo.h"
#include <iostream>

Lista::Lista() {
    cabeza = nullptr;
}

Lista::~Lista() {
    Nodo* temp = cabeza;
    while (temp) {
        Nodo* siguiente = temp->getSiguiente();
        delete temp;
        temp = siguiente;
    }
}


void Lista::insertar(int dato) {
    Nodo* nuevoNodo = new Nodo(dato);
    if (!cabeza) {
        cabeza = nuevoNodo;
    } else {
        Nodo* temp = cabeza;
        while (temp->getSiguiente()) {
            temp = temp->getSiguiente();
        }
        temp->setSiguiente(nuevoNodo);
    }
}

void Lista::eliminar(int dato) {
    Nodo* temp = cabeza;
    Nodo* anterior = nullptr;
    while (temp && temp->getDato() != dato) {
        anterior = temp;
        temp = temp->getSiguiente();
    }

    if (temp) {
        if (anterior) {
            anterior->setSiguiente(temp->getSiguiente());
        } else {
            cabeza = temp->getSiguiente();
        }
        delete temp;
    }
}

void Lista::mostrar() {
    Nodo* temp = cabeza;
    while (temp) {
        std::cout << temp->getDato() << " --> ";
        temp = temp->getSiguiente();
    }
    std::cout << std::endl;
}

void Lista::actualizar(int viejoDato, int nuevoDato) {
    Nodo* nodo = buscar(viejoDato);
    if (nodo) {
        nodo->setDato(nuevoDato);
    }
}
Nodo* Lista::buscar(int dato) {
    Nodo* temp = cabeza;
    int pos = 0;
    // Recorrer la lista hasta el final
    while (temp) {
        pos++;
        if (temp->getDato() == dato) {
            // Si se encuentra el dato, mostrar la posición desde el final
            std::cout << "El elemento " << dato << " está en la posición " << pos << " \n";
            return temp;
        }
        temp = temp->getSiguiente();
    }
    return nullptr;
}
