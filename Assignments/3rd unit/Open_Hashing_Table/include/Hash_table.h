#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <vector>
#include <list>
#include <string>
#include <iostream>

template <typename T>
class Hash_table
{
private:
    std::vector<std::list<T>> table;
    size_t tableSize;
    size_t customHashInt(int key) const;
    size_t customHashString(const std::string &key) const;

public:
    Hash_table(size_t size);
    void insert(const T &key);
    bool search(const T &key) const;
    void remove(const T &key);
    void display() const;
    size_t getHashIndex(const T &key) const;
};

#include "../src/Hash_table.cpp"

#endif // HASH_TABLE_H
