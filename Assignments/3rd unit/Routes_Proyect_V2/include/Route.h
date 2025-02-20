#ifndef ROUTE_H
#define ROUTE_H

#include "Ubication.h"
#include "Trafic.h"
#include <string>
#include <vector>

class Route {
private:
    std::string name;
    double distance;
    Ubication initial;
    Ubication last;
    double speed;
    std::vector<Trafic> trafics; // Ahora almacena múltiples objetos Trafic

public:
    Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed);
    Route();
    Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, std::vector<Trafic> trafics);
    std::vector<Trafic> agruparIntervalosConsecutivos(const std::vector<Trafic>& trafics) const;
    std::string getName() const;
    double getDistance() const;
    Ubication getInitialUbication() const;
    Ubication getLastUbication() const;
    std::vector<Trafic> getTrafics() const;
    double getSpeed() const;

    void setName(const std::string& name);
    void setDistance(double distance);
    void setInitialUbication(const Ubication& initial);
    void setLastUbication(const Ubication& last);
    void setSpeed(double speed);

    void definir_ruta(std::string name, double distance, Ubication initial, Ubication last, int size);
    void guardar_en_archivo();
    void agregar_trafico(const Trafic& trafic);
    
    static bool eliminarTramoDelArchivo(const std::string& nombreRuta, int xInicial, int yInicial, int xFinal, int yFinal);
    static bool eliminarRutaDelArchivo(const std::string& nombreRuta);
};

#endif // ROUTE_H
