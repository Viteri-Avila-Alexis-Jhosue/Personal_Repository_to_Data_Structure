#include "../include/Closed_Hash.h"
#include "../include/Node.h"

template <typename T>
Closed_Hash<T>::Closed_Hash(int size, int method) : size(size), method(method) {
    table.resize(size, T(-1, "")); // Inicializar con objetos Node inválidos
    occupied.resize(size, false);
}

template <typename T>
int Closed_Hash<T>::primaryHash(T key) {
    return std::hash<int>{}(key.getIndex()) % size;
}

template <typename T>
int Closed_Hash<T>::secondaryHash(T key) {
    return 7 - (std::hash<int>{}(key.getIndex()) % 7);
}

template <typename T>
int Closed_Hash<T>::probe(int index, int attempt, T key) {
    if (method == 0) {
        return (index + attempt) % size;
    } else if (method == 1) {
        return (index + attempt * attempt) % size;
    } else if (method == 2) {
        return (index + attempt * secondaryHash(key)) % size;
    }
    return index;
}

template <typename T>
void Closed_Hash<T>::insert(T key) {
    int index = primaryHash(key);
    int attempt = 0;

    while (occupied[index]) {
        attempt++;
        index = probe(primaryHash(key), attempt, key);
        if (attempt >= size) {
            std::cout << "Error: Tabla llena, no se puede insertar " << key.getWord() << std::endl;
            return;
        }
    }

    table[index] = key;
    occupied[index] = true;
}

template <typename T>
void Closed_Hash<T>::display() {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (occupied[i]) {
            std::cout << "[" << i << "]: " << table[i].getWord() << "   ";
        } else {
            std::cout << "[" << i << "]: +    ";
        }
        count++;
        if (count % 3 == 0) {
            std::cout << std::endl;
        }
    }
    if (count % 3 != 0) {
        std::cout << std::endl;
    }
}

template<typename T>
int Closed_Hash<T>::convert_string_to_int(std::string cad) {
    size_t hashValue = 0;
    for (auto it = cad.rbegin(); it != cad.rend(); ++it) {
        size_t temp = static_cast<size_t>(*it);
        temp = (temp + hashValue);
        if (it + 1 != cad.rend()) {
            temp = (temp << 4);
            hashValue = temp;
        } else {
            hashValue = temp;
        }
    }
    return static_cast<int>(hashValue);
}

// Instanciación explícita para evitar problemas con templates en archivos separados
template class Closed_Hash<Node>;