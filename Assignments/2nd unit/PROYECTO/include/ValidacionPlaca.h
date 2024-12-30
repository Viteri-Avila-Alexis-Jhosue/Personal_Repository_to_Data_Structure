#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <regex>
#include <algorithm>
#include <stdexcept>
#include "Nodo.h"
#include "Lista.h"
#include "Coche.h"

using namespace std;

template <typename T>
class Placa
{
public:
    string ingresarPlaca(Nodo<T> *aux);

private:
    void convertirAMayusculas(string &placa);
};
#include "../src/ValidacionPlaca.cpp"