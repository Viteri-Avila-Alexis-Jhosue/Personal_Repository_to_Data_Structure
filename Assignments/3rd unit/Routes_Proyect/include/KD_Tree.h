#ifndef KD_TREE_H
#define KD_TREE_H
#include "Node.h"
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <set>

template <typename T>
class KD_Tree {
private:
    void clear(std::shared_ptr<Node<T>> node);
    std::shared_ptr<Node<T>> root;
    std::shared_ptr<Node<T>> insertRec(std::shared_ptr<Node<T>> node, const T& data, const std::array<int, 2>& coords, int depth);
    void inOrderRec(std::shared_ptr<Node<T>> node) const;
    void print_ubicaciones_rec(std::shared_ptr<Node<T>> node) const;
public:
    KD_Tree();
    ~KD_Tree();
    void insert(const T& data, int x, int y);
    void inOrder() const;
    void load_ubicaciones(const std::string& fileName);
    void print_ubicaciones()const;
};

#include "../src/KD_Tree.cpp"

#endif // KD_TREE_H
