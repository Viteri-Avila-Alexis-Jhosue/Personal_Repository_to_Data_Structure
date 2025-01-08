
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
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(anio), propietario(propietario), horaIngreso(chrono::system_clock::now()) {}

Coche::Coche(string placa, string modelo, string color, string marca,
             chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida, Propietario propietario)
    : placa(placa), modelo(modelo), color(color), marca(marca), anio(0), horaIngreso(horaIngreso), horaSalida(horaSalida), propietario(propietario) {}


void Coche::setHoraSalida(chrono::system_clock::time_point hora){
    horaSalida = hora;
}

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

chrono::system_clock::time_point Coche::getHoraSalida() const{
    return horaSalida;
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

chrono::system_clock::time_point Coche::getHora() const{
    return horaIngreso;
}



ostream &operator<<(ostream &os, const Coche &coche){
    os << "Placa: " << coche.placa << "\nMarca: " << coche.marca
       << "\nModelo: " << coche.modelo << "\nColor: " << coche.color
       << "\n----------------------------------------" << endl;

    time_t tiempoIngreso = chrono::system_clock::to_time_t(coche.horaIngreso);
    os << "\nHora de Ingreso: " << ctime(&tiempoIngreso)
       << "\n----------------------------------------" << endl;

    if (coche.horaSalida == chrono::system_clock::time_point())
    {
        os << "\nHora de Salida: N/A" << endl;
    }
    else
    {
        time_t tiempoSalida = chrono::system_clock::to_time_t(coche.horaSalida);
        os << "\nHora de Salida: " << ctime(&tiempoSalida)
           << "\n----------------------------------------" << endl;
    }

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

    // Convertir horaIngreso y horaSalida a formato legible
    std::time_t ingreso_time = chrono::system_clock::to_time_t(horaIngreso);
    std::string horaIngresoStr = std::ctime(&ingreso_time);
    horaIngresoStr.pop_back(); // Para eliminar el salto de línea al final

    std::string horaSalidaStr = "N/A";
    if (horaSalida != chrono::system_clock::time_point()) {
        std::time_t salida_time = chrono::system_clock::to_time_t(horaSalida);
        horaSalidaStr = std::ctime(&salida_time);
        horaSalidaStr.pop_back(); // Para eliminar el salto de línea al final
    }

    // Escribir los datos del coche en el archivo
    file << placa << ","
         << modelo << ","
         << color << ","
         << marca << ","
         << horaIngresoStr << ","
         << horaSalidaStr << "\n";

    file.close();  // Cerrar el archivo
}
void Coche::ingresar_coche_nuevo(){
    Validaciones validaciones;
    string placa, modelo, color, marca;
    cout << "Ingrese la placa del coche: ";
    placa = validaciones.ingresarPlaca("");
    cout << "Ingrese el modelo del coche: ";
    modelo = validaciones.ingresarString("");
    cout << "Ingrese el color del coche: ";
    color = validaciones.ingresarString("");
    cout << "Ingrese la marca del coche: ";
    marca = validaciones.ingresarString("");
    setPlaca(placa);
    setModelo(modelo);
    setColor(color);
    setMarca(marca);
}
void ingresar_coche_existente(){
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