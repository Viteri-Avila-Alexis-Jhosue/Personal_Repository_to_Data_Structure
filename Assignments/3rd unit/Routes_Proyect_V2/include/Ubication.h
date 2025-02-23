#ifndef UBICATION_H
#define UBICATION_H

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class Ubication {
private:
    int x, y;
    std::string name;
    std::string description;

public:
    Ubication(int x, int y, const std::string& name);
    Ubication(int x, int y, const std::string& name, const std::string& description);
    Ubication();
    int getX() const;
    int getY() const;
    std::string getName() const;
    std::string getDescription() const;

    void setX(int x);
    void setY(int y);
    void setName(const std::string& name);
    void setDescription(const std::string& description);

    int ingresar_coordenada(int size, int coord);
    void ingresar_ubicacion(std::string name, int x, int y,std::string description);
    void guardar_en_archivo();
    static void eliminarUbicacion(const std::string& nombreUbicacion);
};

#endif // UBICATION_H