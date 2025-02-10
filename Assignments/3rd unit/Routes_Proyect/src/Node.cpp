# include "../include/Node.h"

template <typename T>
Node<T>::Node(const T& data, int x, int y)
    : data(data), coords({x, y}), left(nullptr), right(nullptr) {}