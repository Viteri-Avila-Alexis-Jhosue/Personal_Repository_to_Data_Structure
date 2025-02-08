#ifndef CLOSED_HASH_H
#define CLOSED_HASH_H

#include <vector>
#include <functional>
#include <iostream>
#include "Node.h"

template <typename T>
class Closed_Hash {
private:
    std::vector<T> table;
    std::vector<bool> occupied;
    int size;
    int method;

    int primaryHash(T key);
    int secondaryHash(T key);
    int probe(int index, int attempt, T key);

public:
    Closed_Hash(int size, int method);
    void insert(T key);
    void display();
    int convert_string_to_int(std::string cad);
};

#include "../src/Closed_Hash.cpp"

#endif // CLOSED_HASH_H