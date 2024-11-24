/*
Universidad de las Fuerzas Armadas ESPE
Programa generico para el uso de listas
Alexis Viteri
Fecha de creacion:  24/10/2024
Ultima fecha de modificacion:   24/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef NODO_H
#define NODO_H

class Nodo {
private:
    int dato;  // Puede ser cualquier tipo de dato que necesites
    Nodo* siguiente;

public:
    Nodo(int dato);  // Constructor
    int getDato();   // Getter
    void setDato(int dato);  // Setter
    Nodo* getSiguiente();  // Getter
    void setSiguiente(Nodo* siguiente);  // Setter
};

#endif
