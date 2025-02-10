#ifndef NODE_H
#define NODE_H

#include <memory>
#include <array>

template <typename T>
class Node {
public:
    T data;
    std::array<int, 2> coords;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;

    Node(const T& data, int x, int y);
};
#include "../src/Node.cpp"
#endif // Node_H
