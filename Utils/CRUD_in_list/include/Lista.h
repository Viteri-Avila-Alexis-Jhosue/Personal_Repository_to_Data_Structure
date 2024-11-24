/*
Universidad de las Fuerzas Armadas ESPE
Programa generico para el uso de listas
Alexis Viteri
Fecha de creacion:  24/10/2024
Ultima fecha de modificacion:   24/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"

class Lista {
private:
    Nodo* cabeza;

public:
    Lista();  // Constructor
    ~Lista(); // Destructor

    void insertar(int dato);  // Método para insertar
    void eliminar(int dato);  // Método para eliminar
    void mostrar();           // Método para mostrar
    Nodo* buscar(int dato);   // Método para buscar
    void actualizar(int viejoDato, int nuevoDato);  // Método para actualizar
};

#endif
