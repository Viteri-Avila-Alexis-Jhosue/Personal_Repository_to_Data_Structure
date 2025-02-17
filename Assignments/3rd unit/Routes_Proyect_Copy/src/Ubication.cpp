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

Ubication::Ubication(int x, int y, const std::string& name) : x(x), y(y), name(name) {}

int Ubication::getX() const { return x; }

int Ubication::getY() const { return y; }

std::string Ubication::getName() const { return name; }

void Ubication::setX(int x) {
    this->x = x;
}

void Ubication::setY(int y) {
    this->y = y;
}

void Ubication::setName(const std::string& name) {
    this->name = name;
}

int Ubication::ingresar_coordenada(int size, int coord){
    string coordenada;
    int a;
    Validation validaciones;
    if(coord==0){
        coordenada="x";
    }else{
        coordenada="y";
    }
    do{
        cout<<"\nIngrese la coordenada ["<<coordenada<<"] de la ubicacion:  ";
        a = validaciones.ingresarInt("");
        if(a>=size||a<0){
            cout<<"\nCoordenada fuera del rango, ingrese un valor entre 0 y "<< size-1<<" "<<endl;
            }
    }while(a>=size||a<0);
    return a;
}

void Ubication::ingresar_ubicacion(string name, int x, int y){
    setName(name);
    setX(x);
    setY(y);
    guardar_en_archivo();
}

void Ubication::guardar_en_archivo(){
    std::ofstream file("output//Ubicaciones.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de Ubicaciones para escribir." << std::endl;
        return;
    }
    file << x << ","
         << y << ","
         << name << "\n";
    file.close();  
}
Ubication::Ubication()
    :x(0), y(0), name(""){}