/*
Universidad de las Fuerzas Armadas ESPE
Programa generico para el uso de listas
Alexis Viteri
Fecha de creacion:  24/10/2024
Ultima fecha de modificacion:   24/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Nodo.h"

Nodo::Nodo(int dato) {
    this->dato = dato;
    this->siguiente = nullptr;
}

int Nodo::getDato() {
    return dato;
}

void Nodo::setDato(int dato) {
    this->dato = dato;
}

Nodo* Nodo::getSiguiente() {
    return siguiente;
}

void Nodo::setSiguiente(Nodo* siguiente) {
    this->siguiente = siguiente;
}
