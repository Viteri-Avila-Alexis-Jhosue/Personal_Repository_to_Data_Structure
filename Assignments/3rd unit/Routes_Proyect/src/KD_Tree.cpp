# include "../include/KD_Tree.h"
# include "../include/Node.h"
# include "../include/Ubication.h"
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
#include <functional>
#include <cmath>
#include <set>
#include <random> 
#include <queue>
using namespace std;
template <typename T>
KD_Tree<T>::KD_Tree() : root(nullptr) {}

template <typename T>
KD_Tree<T>::~KD_Tree() {
    clear(root);
    root.reset(); 
}
template <typename T>
void KD_Tree<T>::clear(std::shared_ptr<Node<T>> node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    node.reset(); 
}

template <typename T>
std::shared_ptr<Node<T>> KD_Tree<T>::insertRec(std::shared_ptr<Node<T>> node, const T& data, const std::array<int, 2>& coords, int depth) {
    if (node == nullptr) {
        return std::make_shared<Node<T>>(data, coords[0], coords[1]);
    }
    int axis = depth % 2;
    if (coords[axis] < node->coords[axis]) {
        node->left = insertRec(node->left, data, coords, depth + 1);
    } else {
        node->right = insertRec(node->right, data, coords, depth + 1);
    }
    return node;
}

template <typename T>
void KD_Tree<T>::insert(const T& data, int x, int y) {
    root = insertRec(root, data, {x, y}, 0);
}

template <typename T>
void KD_Tree<T>::inOrderRec(std::shared_ptr<Node<T>> node) const {
    if (node != nullptr) {
        inOrderRec(node->left);
        std::cout << "(" << node->coords[0] << ", " << node->coords[1] << std::endl;
        inOrderRec(node->right);
    }
}

template <typename T>
void KD_Tree<T>::inOrder() const {
    inOrderRec(root);
}

template <typename T>
void KD_Tree<T>::load_ubicaciones(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return; 
    }
    std::string line;
    std::cout << "Procesando " << fileName << " ...." << std::endl;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string x_str, y_str, name;
        if (std::getline(stream, x_str, ',') &&
            std::getline(stream, y_str, ',') &&
            std::getline(stream, name, ',')) {
            int x = std::stoi(x_str);
            int y = std::stoi(y_str);
            Ubication ubication(x,y,name);

            insert(ubication, x, y); 
        }
    }
    file.close();
}
template <typename T>
void KD_Tree<T>::print_ubicaciones_rec(std::shared_ptr<Node<T>> node) const {
    if (!node) {
        return;
    }
        print_ubicaciones_rec(node->left);
        std::cout << "(" << node->coords[0] << ", " << node->coords[1] << ") -> " << node->data.getName() << std::endl;
        print_ubicaciones_rec(node->right);
    
}

template <typename T>
void KD_Tree<T>::print_ubicaciones() const {
    print_ubicaciones_rec(root);
}