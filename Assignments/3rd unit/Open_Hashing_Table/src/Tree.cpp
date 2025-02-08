#include "../include/Tree.h"
#include "../include/Node.h"
#include "../include/User.h"
#include "../include/Hash_table.h"
#include <functional>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
Tree<T>::~Tree()
{
    clear(root);
    root.reset();
}

template <typename T>
void Tree<T>::clear(std::shared_ptr<Node<T>> node)
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);
    node.reset();
}

template <typename T>
void Tree<T>::insert(const T &data)
{
    insertHelper(root, data);
}

template <typename T>
void Tree<T>::insertHelper(std::shared_ptr<Node<T>> &node, const T &data)
{
    if (!node)
    {
        node = std::make_shared<Node<T>>(data);
    }
    else if (data.getId() < node->data.getId())
    {
        insertHelper(node->left, data);
    }
    else
    {
        insertHelper(node->right, data);
    }
}

template <typename T>
void Tree<T>::inOrder() const
{
    inOrderHelper(root);
}

template <typename T>
void Tree<T>::inOrderHelper(std::shared_ptr<Node<T>> node) const
{
    if (node)
    {
        inOrderHelper(node->left);
        std::cout << "ID: " << node->data.getId() << "; NOMBRE: " << node->data.getName() << "; APELLIDO: " << node->data.getLastName() << "; CONTRASEÑA: " << node->data.getPassword() << std::endl;
        inOrderHelper(node->right);
    }
}
template <typename T>
void Tree<T>::load_from_file(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }
    std::string line;
    std::cout << "Procesando Users.txt..." << std::endl;
    while (std::getline(file, line))
    {
        std::istringstream stream(line);
        std::string namestr, lastnamestr, passwordstr, idstr;
        int id;
        if (std::getline(stream, idstr, ',') &&
            std::getline(stream, namestr, ',') &&
            std::getline(stream, lastnamestr, ',') &&
            std::getline(stream, passwordstr, ','))
        {
            id = std::stoi(idstr);
            User user(id, namestr, lastnamestr, passwordstr);
            insert(user);
        }
    }
    file.close();
}

template <typename T>
void Tree<T>::hashear_datos(int dato)
{
    hashear_datos_helper(root, dato);
}

template <typename T>
void Tree<T>::hashear_datos_helper(std::shared_ptr<Node<T>> node, int dato)
{
    if (node)
    {
        hashear_datos_helper(node->left, dato);
        Hash_table<int> hashTableInt(dato);
        Hash_table<std::string> hashTableStr(dato);

        std::cout << "-------------------------------------------------------------------------------------" << std::endl;
        std::cout << "ID: " << node->data.getId()
                  << " -> " << hashTableInt.getHashIndex(node->data.getId()) << std::endl;
        std::cout << "NOMBRE: " << node->data.getName()
                  << " -> " << hashTableStr.getHashIndex(node->data.getName()) << std::endl;
        std::cout << "APELLIDO: " << node->data.getLastName()
                  << " -> " << hashTableStr.getHashIndex(node->data.getLastName()) << std::endl;
        std::cout << "CONTRASEÑA: " << node->data.getPassword()
                  << " -> " << hashTableStr.getHashIndex(node->data.getPassword()) << std::endl;
        std::cout << "-------------------------------------------------------------------------------------" << std::endl;
        hashear_datos_helper(node->right, dato);
    }
}

template <typename T>
void Tree<T>::tabla_hash_id()
{
    Hash_table<int> hashTableInt(13);
    tabla_hash_id_helper(root, hashTableInt);
    hashTableInt.display();
}

template <typename T>
void Tree<T>::tabla_hash_id_helper(std::shared_ptr<Node<T>> node, Hash_table<int> &hashTableInt)
{
    if (node)
    {
        tabla_hash_id_helper(node->left, hashTableInt);
        hashTableInt.insert(node->data.getId());
        tabla_hash_id_helper(node->right, hashTableInt);
    }
}
template <typename T>
void Tree<T>::tabla_hash_nombre()
{
    Hash_table<std::string> hashTableStr(13);
    tabla_hash_nombre_helper(root, hashTableStr);
    hashTableStr.display();
}

template <typename T>
void Tree<T>::tabla_hash_nombre_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string> &hashTableStr)
{
    if (node)
    {
        tabla_hash_nombre_helper(node->left, hashTableStr);
        hashTableStr.insert(node->data.getName());
        tabla_hash_nombre_helper(node->right, hashTableStr);
    }
}

template <typename T>
void Tree<T>::tabla_hash_apellido()
{
    Hash_table<std::string> hashTableStr(13);
    tabla_hash_apellido_helper(root, hashTableStr);
    hashTableStr.display();
}

template <typename T>
void Tree<T>::tabla_hash_apellido_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string> &hashTableStr)
{
    if (node)
    {
        tabla_hash_apellido_helper(node->left, hashTableStr);
        hashTableStr.insert(node->data.getLastName());
        tabla_hash_apellido_helper(node->right, hashTableStr);
    }
}

template <typename T>
void Tree<T>::tabla_hash_contrasena()
{
    Hash_table<std::string> hashTableStr(13);
    tabla_hash_contrasena_helper(root, hashTableStr);
    hashTableStr.display();
}

template <typename T>
void Tree<T>::tabla_hash_contrasena_helper(std::shared_ptr<Node<T>> node, Hash_table<std::string> &hashTableStr)
{
    if (node)
    {
        tabla_hash_contrasena_helper(node->left, hashTableStr);
        hashTableStr.insert(node->data.getPassword());
        tabla_hash_contrasena_helper(node->right, hashTableStr);
    }
}