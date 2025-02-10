#include "../include/List.h"
#include <iostream>

template <typename T>
List<T>::List() : head(nullptr) {}

template <typename T>
List<T>::~List() {
    Node_list<T>* current = head;
    while (current) {
        Node_list<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void List<T>::insert(T value) {
    Node_list<T>* newNode = new Node_list<T>(value);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void List<T>::display() const {
    Node_list<T>* current = head;
    while (current) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}
