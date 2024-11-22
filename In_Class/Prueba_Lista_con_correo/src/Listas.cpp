/*
Universidad de las Fuerzas Armadas ESPE
Programa con operaciones de listas
Alexis Viteri
Fecha de creacion:  18/11/2024
Ultima fecha de modificacion:   18/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Listas.h"

// Constructor de la lista
template <typename T>
List<T>::List() : head(nullptr) {}

// Agregar un nodo al final (cola)
template <typename T>
void List<T>::addToTail(const T& value) {
    auto newNode = std::make_shared<Nodo<T>>(value);
    if (!head) {
        head = newNode;
    } else {
        auto temp = head;
        while (temp->getNext()) {
            temp = temp->getNext();
        }
        temp->setNext(newNode);
    }
}

// Agregar un nodo al inicio (cabeza)
template <typename T>
void List<T>::addToHead(const T& value) {
    auto newNode = std::make_shared<Nodo<T>>(value);
    newNode->setNext(head);
    head = newNode;
}

// Mostrar todos los elementos
template <typename T>
void List<T>::display() const {
    auto temp = head;
    while (temp) {
        std::cout << temp->getData() << " --> ";
        temp = temp->getNext();
    }
    std::cout << "NULL" << std::endl;
}

// Actualizar un nodo basado en un criterio
template <typename T>
void List<T>::update(const std::function<bool(const T&)>& criteria, const T& newValue) {
    auto temp = head;
    while (temp) {
        if (criteria(temp->getData())) {
            temp->setData(newValue);
            return;
        }
        temp = temp->getNext();
    }
}

// Eliminar un nodo basado en un criterio
template <typename T>
void List<T>::remove(const std::function<bool(const T&)>& criteria) {
    if (!head) return;

    if (criteria(head->getData())) {
        head = head->getNext();
        return;
    }

    auto temp = head;
    while (temp->getNext() && !criteria(temp->getNext()->getData())) {
        temp = temp->getNext();
    }

    if (temp->getNext()) {
        temp->setNext(temp->getNext()->getNext());
    }
}

// Buscar un nodo basado en un criterio
template <typename T>
T* List<T>::search(const std::function<bool(const T&)>& criteria) {
    auto temp = head;
    int position = 1;

    while (temp) {
        if (criteria(temp->getData())) {
            std::cout << "\nElemento encontrado en la posicion: " << position << std::endl;
            return &temp->getData();
        }
        temp = temp->getNext();
        position++;
    }

    std::cout << "Elemento no encontrado en la lista." << std::endl;
    return nullptr;
}
#include "../include/Person.h"
template class List<Person>;