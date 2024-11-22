#ifndef LISTAS_H
#define LISTAS_H

#include "Nodo.h"
#include <string>

class Lista {
private:
    Nodo* cabeza;
public:
    Lista();
    ~Lista();

    void agregarNodo(const std::string& nombre1, const std::string& nombre2, 
                     const std::string& apellido1, const std::string& apellido2);
    void eliminarCaracter(char caracter);
    void imprimirLista();
};

#endif // LISTAS_H

