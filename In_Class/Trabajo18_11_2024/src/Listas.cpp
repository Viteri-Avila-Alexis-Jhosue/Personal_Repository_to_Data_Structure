/*
Universidad de las Fuerzas Armadas ESPE
Programa con operaciones de listas
Alexis Viteri
Fecha de creacion:  18/11/2024
Ultima fecha de modificacion:   18/11/2024
Estructura de Datos
NRC:  1978
*/
#include "Listas.h"

// Constructor del nodo
template <typename T>
List<T>::Node::Node(const T& data) : data(data), next(nullptr) {}

// Constructor de la lista
template <typename T>
List<T>::List() : head(nullptr) {}

// Agregar un nodo al final (cola)
template <typename T>
void List<T>::addToTail(const T& value) {
    auto newNode = std::make_shared<Node>(value);
    if (!head) {
        head = newNode;
    } else {
        auto temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Agregar un nodo al inicio (cabeza)
template <typename T>
void List<T>::addToHead(const T& value) {
    auto newNode = std::make_shared<Node>(value);
    newNode->next = head;
    head = newNode;
}

// Mostrar todos los elementos
template <typename T>
void List<T>::display() {
    auto temp = head;
    while (temp) {
        std::cout << temp->data << " --> ";
        temp = temp->next;
    }
    printf("NULL");
    std::cout << std::endl;
}

// Actualizar un nodo basado en un criterio
template <typename T>
void List<T>::update(const std::function<bool(const T&)>& criteria, const T& newValue) {
    auto temp = head;
    while (temp) {
        if (criteria(temp->data)) {
            temp->data = newValue;
            return;
        }
        temp = temp->next;
    }
}

// Eliminar un nodo basado en un criterio
template <typename T>
void List<T>::remove(const std::function<bool(const T&)>& criteria) {
    if (!head) return;

    // Caso especial para el primer nodo
    if (criteria(head->data)) {
        head = head->next;
        return;
    }

    auto temp = head;
    while (temp->next && !criteria(temp->next->data)) {
        temp = temp->next;
    }

    if (temp->next) {
        temp->next = temp->next->next;
    }
}

// Buscar un nodo basado en un criterio
template <typename T>
T* List<T>::search(const std::function<bool(const T&)>& criteria) {
    auto temp = head;
    int position = 1; // Contador de posición

    while (temp) {
        if (criteria(temp->data)) {
            std::cout << "\nElemento encontrado en la posicion: " << position << std::endl;
            return &temp->data; // Devuelve un puntero al dato encontrado
        }
        temp = temp->next;
        position++;
    }

    std::cout << "Elemento no encontrado en la lista." << std::endl;
    return nullptr; // No encontrado
}


// Necesario para compilar clases template
template class List<int>;
template class List<std::string>;
