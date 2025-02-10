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
    Trafic level;

public:
    Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, const Trafic& level);
    std::string getName() const;
    double getDistance() const;
    Ubication getInitialUbication() const;
    Ubication getLastUbication() const;
    double getSpeed() const;
    Trafic getTraficLevel() const;
    void definir_ruta();
    void guerdar_en_archivo();
};

#endif // ROUTE_H