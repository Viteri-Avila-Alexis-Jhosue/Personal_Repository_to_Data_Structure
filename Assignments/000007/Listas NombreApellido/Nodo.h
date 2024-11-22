#ifndef NODO_H
#define NODO_H

#include <string>

class Nodo {
public:
    std::string nombre1;
    std::string nombre2;
    std::string apellido1;
    std::string apellido2;
    Nodo* siguiente;

    Nodo(const std::string& nombre1, const std::string& nombre2, 
         const std::string& apellido1, const std::string& apellido2);
};

#endif // NODO_H
