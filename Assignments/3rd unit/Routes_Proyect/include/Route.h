#ifndef ROUTE_H
#define ROUTE_H

#include "Ubication.h"
#include "Trafic.h"
#include <string>

class Route {
private:
    std::string name;
    double distance;
    Ubication initial;
    Ubication last;
    double speed;
    Trafic trafic;

public:
    Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed);
    Route();
    Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, Trafic trafic);
    std::string getName() const;
    double getDistance() const;
    Ubication getInitialUbication() const;
    Ubication getLastUbication() const;
    Trafic getTrafic()const;
    double getSpeed() const;
    void setName(const std::string& name);
    void setDistance(double distance);
    void setInitialUbication(const Ubication& initial);
    void setLastUbication(const Ubication& last);
    void setSpeed(double speed);
    void definir_ruta(std::string name,double distance, Ubication initial, Ubication last, int size);
    void guardar_en_archivo();
    void agregar_trafico(Trafic trafic);
};

#endif // ROUTE_H