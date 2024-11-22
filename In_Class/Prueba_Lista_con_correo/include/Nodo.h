#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <string>
#include <memory>

template<typename T>
class Nodo {
private:
    T data;  // Datos almacenados en el nodo
    std::shared_ptr<Nodo<T>> next;  // Puntero al siguiente nodo

public:
    // Constructor
    Nodo(const T& data) : data(data), next(nullptr) {}

    // Getters y setters para el siguiente nodo
    std::shared_ptr<Nodo<T>> getNext() const { return next; }
    void setNext(const std::shared_ptr<Nodo<T>>& nextNode) { next = nextNode; }

    // Getter para los datos (devuelve una referencia para evitar errores temporales)
    T& getData() { return data; }
    const T& getData() const { return data; }  // Versión constante

    // Setter para los datos
    void setData(const T& newData) { data = newData; }
};

#endif // NODO_H
