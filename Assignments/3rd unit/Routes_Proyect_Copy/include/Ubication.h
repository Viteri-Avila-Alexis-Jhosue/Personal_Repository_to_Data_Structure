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

public:
    Ubication(int x, int y, const std::string& name);
    Ubication();
    int getX() const;
    int getY() const;
    std::string getName() const;

    void setX(int x);
    void setY(int y);
    void setName(const std::string& name);

    int ingresar_coordenada(int size, int coord);
    void ingresar_ubicacion(std::string name, int x, int y);
    void guardar_en_archivo();
};

#endif // UBICATION_H