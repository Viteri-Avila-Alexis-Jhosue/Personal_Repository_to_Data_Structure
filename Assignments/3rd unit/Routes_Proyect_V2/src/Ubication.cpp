#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
#include "../include/Ubication.h"
#include "../include/Validation.h"

Ubication::Ubication(int x, int y, const std::string &name) : x(x), y(y), name(name) {}

Ubication::Ubication(int x, int y, const std::string &name, const std::string &description) : x(x), y(y), name(name), description(description) {}

int Ubication::getX() const { return x; }

int Ubication::getY() const { return y; }

std::string Ubication::getName() const { return name; }

std::string Ubication::getDescription() const { return description; }

void Ubication::setX(int x)
{
    this->x = x;
}

void Ubication::setY(int y)
{
    this->y = y;
}

void Ubication::setName(const std::string &name)
{
    this->name = name;
}

void Ubication::setDescription(const std::string &description)
{
    this->description = description;
}

int Ubication::ingresar_coordenada(int size, int coord)
{

    string coordenada;
    int a;
    Validation validaciones;
    if (coord == 0)
    {
        coordenada = "x";
    }
    else
    {
        coordenada = "y";
    }
    do
    {
        cout << "\nIngrese la coordenada [" << coordenada << "] de la ubicacion:  ";
        a = validaciones.ingresarInt("");
        if (a >= size || a < 0)
        {
            cout << "\nCoordenada fuera del rango, ingrese un valor entre 0 y " << size - 1 << " ";
        }
    } while (a >= size || a < 0);
    return a;
}

void Ubication::ingresar_ubicacion(string name, int x, int y, string description)
{
    setName(name);
    setX(x);
    setY(y);
    setDescription(description);
    guardar_en_archivo();
}

void Ubication::guardar_en_archivo()
{
    std::ofstream file("output//Ubicaciones.txt", std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo de Ubicaciones para escribir." << std::endl;
        return;
    }
    file << x << ","
         << y << ","
         << name << ","
         << description << "\n";
    file.close();
}
Ubication::Ubication()
    : x(0), y(0), name("") {}

void Ubication::eliminarUbicacion(const std::string &nombreUbicacion)
{
    std::ifstream archivoEntrada("output//Ubicaciones.txt");
    if (!archivoEntrada.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo de Ubicaciones para leer." << std::endl;
        return;
    }

    std::vector<std::string> lineas;
    std::string linea;

    // Leer todas las líneas del archivo
    while (std::getline(archivoEntrada, linea))
    {
        std::istringstream ss(linea);
        std::string xStr, yStr, nombre, descripcion;

        // Leer los campos de la línea
        std::getline(ss, xStr, ',');   // Leer la coordenada x
        std::getline(ss, yStr, ',');   // Leer la coordenada y
        std::getline(ss, nombre, ','); // Leer el nombre de la ubicación
        std::getline(ss, descripcion); // Leer la descripción

        // Si la ubicación no es la que se desea eliminar, guardar la línea
        if (nombre != nombreUbicacion)
        {
            lineas.push_back(linea);
        }
    }
    archivoEntrada.close();

    // Sobrescribir el archivo con las líneas restantes
    std::ofstream archivoSalida("output//Ubicaciones.txt", std::ios::trunc);
    if (!archivoSalida.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo de Ubicaciones para escribir." << std::endl;
        return;
    }

    for (const auto &l : lineas)
    {
        archivoSalida << l << "\n";
    }
    archivoSalida.close();
}