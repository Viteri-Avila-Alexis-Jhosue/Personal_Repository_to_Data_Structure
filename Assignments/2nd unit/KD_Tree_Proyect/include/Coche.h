#ifndef COCHE_H
#define COCHE_H
#include "Propietario.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
using namespace std;

class Coche
{
private:
    string placa;
    string color;
    string modelo;
    string marca;
    int anio;
    Propietario propietario;

public:
    Coche(
        std::string placa, 
        std::string modelo, 
        std::string color, 
        std::string marca
       ) : placa(placa), modelo(modelo), color(color), marca(marca) {}
    Coche();
    Coche(string placa, string modelo, string color, string marca, int anio, Propietario propietario);
    Coche(string placa, string modelo, string color, string marca,Propietario propietario);
    void setPlaca(const string &placa);
    void setModelo(const string &modelo);
    void setMarca(const string &marca);
    void setColor(const string &color);
    Propietario getPropietario() const;
    void ingresar_coche_nuevo(int tipo);
    void ingresar_coche_existente(int tipo);

    string getPlaca() const;
    string getMarca() const;
    string getModelo() const;
    string getColor() const;
    int getAnio() const;
    void guardarEnArchivo() const;
    friend ostream &operator<<(ostream &os, const Coche &coche);
    string toString() const;

};
#endif // COCHE_H