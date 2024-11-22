/*
Universidad de las Fuerzas Armadas ESPE
Programa con operaciones de listas
Alexis Viteri
Fecha de creacion:  18/11/2024
Ultima fecha de modificacion:   18/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef LISTAS_H
#define LISTAS_H

#include "Nodo.h"
#include <iostream>
#include <functional>
#include <memory>

template <typename T>
class List {
private:
    std::shared_ptr<Nodo<T>> head;

public:
    List();
    void addToTail(const T& value);
    void addToHead(const T& value);
    void display() const;
    void update(const std::function<bool(const T&)>& criteria, const T& newValue);
    void remove(const std::function<bool(const T&)>& criteria);
    T* search(const std::function<bool(const T&)>& criteria);
};

#endif // LISTAS_H
