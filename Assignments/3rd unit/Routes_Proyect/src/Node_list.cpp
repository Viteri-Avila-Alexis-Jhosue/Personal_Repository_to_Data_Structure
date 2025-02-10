#include "../include/Node_list.h"

template <typename T>
Node_list<T>::Node_list(T value) {
    data = value;
    next = nullptr;
}
