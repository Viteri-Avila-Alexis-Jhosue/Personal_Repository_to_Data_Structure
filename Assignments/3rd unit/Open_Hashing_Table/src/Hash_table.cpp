#include "../include/Hash_table.h"

// Constructor
template <typename T>
Hash_table<T>::Hash_table(size_t size) : tableSize(size)
{
    table.resize(tableSize);
}

// Función hash para enteros (método simple de multiplicación)
template <typename T>
size_t Hash_table<T>::customHashInt(int key) const
{
    return key % tableSize; // Simple módulo directo para ver si el problema persiste
}

template <typename T>
size_t Hash_table<T>::customHashString(const std::string &key) const
{
    size_t hashValue = 0;
    for (auto it = key.rbegin(); it != key.rend(); ++it)
    {
        size_t temp = static_cast<size_t>(*it);
        temp = (temp + hashValue);
        if (it + 1 != key.rend())
        {
            temp = (temp << 4);
            hashValue = temp;
        }
        else
        {
            hashValue = temp;
        }
    }
    return hashValue % tableSize;
}

// Calcula el índice en la tabla hash según el tipo de dato
template <typename T>
size_t Hash_table<T>::getHashIndex(const T &key) const
{
    if constexpr (std::is_same<T, int>::value)
    {
        return customHashInt(key);
    }
    else if constexpr (std::is_same<T, std::string>::value)
    {
        return customHashString(key);
    }
    else
    {
        static_assert(sizeof(T) == 0, "Tipo no compatible con la función hash");
    }
}

// Insertar un elemento en la tabla
template <typename T>
void Hash_table<T>::insert(const T &key)
{
    size_t index = getHashIndex(key);
    table[index].push_back(key);
}

// Buscar un elemento en la tabla
template <typename T>
bool Hash_table<T>::search(const T &key) const
{
    size_t index = getHashIndex(key);
    for (const auto &item : table[index])
    {
        if (item == key)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void Hash_table<T>::remove(const T &key)
{
    size_t index = getHashIndex(key);
    table[index].remove(key);
}

// Mostrar la tabla hash
template <typename T>
void Hash_table<T>::display() const
{
    std::cout << " ------------------------------------------------------------------------\n";
    for (size_t i = 0; i < tableSize; ++i)
    {
        if (i >= 10)
        {
            std::cout << "| Índice " << i << ":|";
        }
        else
        {
            std::cout << "| Índice  " << i << ":|";
        }
        for (const auto &key : table[i])
        {
            std::cout << " " << key << " -> ";
        }
        std::cout << "NULL" << std::endl;
        std::cout << " ------------------------------------------------------------------------\n";
    }
}
