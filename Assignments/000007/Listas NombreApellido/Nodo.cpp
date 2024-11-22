#include "Nodo.h"

Nodo::Nodo(const std::string& nombre1, const std::string& nombre2, 
           const std::string& apellido1, const std::string& apellido2) 
    : nombre1(nombre1), nombre2(nombre2), apellido1(apellido1), apellido2(apellido2), siguiente(nullptr) {}
