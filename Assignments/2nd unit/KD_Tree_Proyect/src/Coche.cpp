
#include <iostream>
#include "../include/Coche.h"
#include "../include/Menu.h"
#include "../include/Validaciones.h"
#include "../include/Propietario.h"
#include "../include/KD_Tree.h"
#include <string> 
#include <vector>
#include <cstdlib>
#include <iomanip>  
#include <fstream>

using namespace std;


Coche::Coche()
{
    this->placa = "";
    this->marca = "";
    this->modelo = "";
    this->color = "";
}

Coche::Coche(string placa, string modelo, string color, string marca, int anio, Propietario propietario)
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(anio), propietario(propietario) {}

Coche::Coche(string placa, string modelo, string color, string marca,
             Propietario propietario)
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(0), propietario(propietario) {}


void Coche::setPlaca(const string &placa){
    this->placa = placa;
}

void Coche::setModelo(const string &modelo){
    this->modelo = modelo;
}

void Coche::setMarca(const string &marca){
    this->marca = marca;
}

void Coche::setColor(const string &color){
    this->color = color;
}

string Coche::getPlaca() const{
    return placa;
}

string Coche::getMarca() const{
    return marca;
}

string Coche::getModelo() const{
    return modelo;
}

string Coche::getColor() const{
    return color;
}

int Coche::getAnio() const{
    return anio;
}

ostream &operator<<(ostream &os, const Coche &coche){
    os << "Placa: " << coche.placa << "\nMarca: " << coche.marca
       << "\nModelo: " << coche.modelo << "\nColor: " << coche.color
       << "\n----------------------------------------" << endl;

    return os;
}

Propietario Coche::getPropietario() const {
    return propietario;
}
void Coche::guardarEnArchivo() const {
    // Abrir el archivo autos.txt en modo de adición
    std::ofstream file("output//autos.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo autos.txt para escribir." << std::endl;
        return;
    }
    // Escribir los datos del coche en el archivo
    file << placa << ","
         << modelo << ","
         << color << ","
         << marca << "\n";

    file.close();  // Cerrar el archivo
}
void Coche::ingresar_coche_nuevo(int tipo){
    string tipostr;
    if(tipo==0){
        tipostr="l coche";
    }else{
        tipostr=" la moto";
    }
    Validaciones validaciones;
    string placa, modelo, color, marca;
    if(tipo==0){
        placa=validaciones.ingresarPlaca("Ingrese la placa del coche: ");
    }else{
        placa=validaciones.ingresarPlacaMoto("Ingrese la placa de la moto: ");
    }
    cout << "Ingrese el modelo de"<<tipostr<<" : ";
    modelo = validaciones.ingresarString("");
    cout << "Ingrese el color de"<<tipostr<<" : ";
    color = validaciones.ingresarString("");
    cout << "Ingrese la marca de"<<tipostr<<" : ";
    marca = validaciones.ingresarString("");
    setPlaca(placa);
    setModelo(modelo);
    setColor(color);
    setMarca(marca);
}
void ingresar_coche_existente(int tipo){
    Validaciones validaciones;
    string placa;
    placa = validaciones.ingresarPlaca("Ingrese la placa del coche: ");
    
}
string Coche::toString() const {
    std::stringstream ss;
    ss << "Placa: " << placa << "\n"
       << "Modelo: " << modelo << "\n"
       << "Color: " << color << "\n"
       << "Marca: " << marca << "\n";
    return ss.str();
}