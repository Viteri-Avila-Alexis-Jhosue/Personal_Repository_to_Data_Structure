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
    chrono::system_clock::time_point horaIngreso;
    chrono::system_clock::time_point horaSalida;
    int anio;
    Propietario propietario;

public:
    Coche(
        std::string placa, 
        std::string modelo, 
        std::string color, 
        std::string marca, 
        std::chrono::system_clock::time_point horaIngreso, 
        std::chrono::system_clock::time_point horaSalida
    ) : placa(placa), modelo(modelo), color(color), marca(marca), 
        horaIngreso(horaIngreso), horaSalida(horaSalida) {}
    Coche();
    Coche(string placa, string modelo, string color, string marca, int anio, Propietario propietario);
    Coche(string placa, string modelo, string color, string marca,
      chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida, Propietario propietario);

    void setHoraSalida(chrono::system_clock::time_point hora);
    void setPlaca(const string &placa);
    void setModelo(const string &modelo);
    void setMarca(const string &marca);
    void setColor(const string &color);
    Propietario getPropietario() const;
    void ingresar_coche_nuevo();
    void ingresar_coche_existente();

    chrono::system_clock::time_point getHoraSalida() const;
    string getPlaca() const;
    string getMarca() const;
    string getModelo() const;
    string getColor() const;
    int getAnio() const;
    void guardarEnArchivo() const;
    chrono::system_clock::time_point getHora() const;
    friend ostream &operator<<(ostream &os, const Coche &coche);
    string toString() const;

};
#endif // COCHE_H