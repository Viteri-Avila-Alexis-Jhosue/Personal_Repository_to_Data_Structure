#ifndef NODO_H
#define NODO_H

#include <memory>
#include <array>

template <typename T>
class Nodo {
public:
    T data;
    std::array<float, 2> coords;
    std::shared_ptr<Nodo<T>> left;
    std::shared_ptr<Nodo<T>> right;

    Nodo(const T& data, float x, float y);
};

template <typename T>
Nodo<T>::Nodo(const T& data, float x, float y)
    : data(data), coords({x, y}), left(nullptr), right(nullptr) {}

#endif // NODO_H
