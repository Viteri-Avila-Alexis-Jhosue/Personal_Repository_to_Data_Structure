#ifndef LIST_H
#define LIST_H

#include "Node_list.h"

template <typename T>
class List {
private:
    Node_list<T>* head;

public:
    List();
    ~List();
    void insert(T value);
    void display() const;
};

#endif