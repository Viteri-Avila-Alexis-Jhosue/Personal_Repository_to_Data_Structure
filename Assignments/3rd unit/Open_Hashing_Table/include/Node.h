#ifndef NODE_H
#define NODE_H

#include <memory>
#include <array>

template <typename T>
class Node {
public:
    T data;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;
    Node(const T& data);
};
# include "../src/Node.cpp"
#endif // NODO_H
