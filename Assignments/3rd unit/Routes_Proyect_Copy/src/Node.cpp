# include "../include/Node.h"

template <typename T>
Node<T>::Node(const T& data, int x, int y)
: data(data), left(nullptr), right(nullptr) {
coords[0] = x; // Coordenada X
coords[1] = y; // Coordenada Y
}