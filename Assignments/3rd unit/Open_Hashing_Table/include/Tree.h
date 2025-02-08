#ifndef TREE_H
#define TREE_H

#include <memory>
#include "Node.h"
#include "Hash_table.h"

template <typename T>
class Tree {
private:
    void clear(std::shared_ptr<Node<T>> node);
    std::shared_ptr<Node<T>> root;
    void insertHelper(std::shared_ptr<Node<T>>& node, const T& data);
    void inOrderHelper(std::shared_ptr<Node<T>> node) const;
    void hashear_datos_helper(std::shared_ptr<Node<T>> node,int dato);
    void tabla_hash_id_helper(std::shared_ptr<Node<T>> node, Hash_table<int>& hashTableInt);
    void tabla_hash_nombre_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string>& hashTableStr);
    void tabla_hash_apellido_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string>& hashTableStr);
    void tabla_hash_contrasena_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string>& hashTableStr);
public:
    Tree();
    ~Tree();
    void insert(const T& data);
    void inOrder() const;
    void load_from_file(const std::string& fileName);
    void hashear_datos(int dato);
    void tabla_hash_id();
    void tabla_hash_nombre();
    void tabla_hash_apellido();
    void tabla_hash_contrasena();
};

#include "../src/Tree.cpp"

#endif // TREE_H