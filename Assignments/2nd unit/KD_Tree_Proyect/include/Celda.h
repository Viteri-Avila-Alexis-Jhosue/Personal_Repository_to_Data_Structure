#ifndef CELDA_H
#define CELDA_H

#include "Coche.h"
class Celda {
private:
    Coche coche;
    float x;
    float y;
    chrono::system_clock::time_point horaIngreso;
    chrono::system_clock::time_point horaSalida;
public:
    // Constructor predeterminado
    Celda();
    // Constructor con parámetros
    Celda(float x, float y,Coche coche);
    Celda(float x, float y, Coche coche, chrono::system_clock::time_point horaIngreso, chrono::system_clock::time_point horaSalida);
    // Getter para el objeto Coche
    Coche getCoche() const;
    // Setter para el objeto Coche
    void setCoche(const Coche& coche);

    void guardarEnArchivo() const;
    void setX(float x);
    void setY(float y);
    float getX() const;
    float getY() const;
    void ingresar_al_parqueadero(Coche coche, int size,float a, float b);
    void retirar_del_parqueadero();
    void setHoraIngreso(chrono::system_clock::time_point hora);
    void setHoraSalida(chrono::system_clock::time_point hora);
    chrono::system_clock::time_point getHoraIngreso() const;
    chrono::system_clock::time_point getHoraSalida() const;
    string toString() const;
    float ingresar_coordenada(int size, int coordenada);
};

#endif // CELDA_H
