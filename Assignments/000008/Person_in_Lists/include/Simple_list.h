/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

#include "Nodo.h"
#include "Encryption.h"
#include <iostream>
#include "Validation.h"
using namespace std;

class SimpleList {
private:
    Nodo* head; // Puntero al inicio de la lista

public:
    // Constructor y destructor
    SimpleList();
    ~SimpleList();

    // Operaciones básicas
    void insert(int id, const string& name1, const string& name2, const string& lastname1, const string& lastname2, const string& email); // Insertar al final
    bool remove(int id);   // Eliminar por ID
    bool search(int id);   // Buscar por ID
    void display() const;  // Mostrar todos los nodos
    void encrypt(int clave);
    void decrypt(int clave);
    void handleMenu(Nodo*& head, const string& institution);
};

#endif // SIMPLE_LIST_H
