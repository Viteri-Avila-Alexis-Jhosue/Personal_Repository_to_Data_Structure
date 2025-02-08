#include "../include/Node.h"

template <typename T>
Node<T>::Node(const T &data) : data(data), left(nullptr), right(nullptr) {}