#ifndef TRAFIC_H
#define TRAFIC_H
#include "Ubication.h"
#include <string>

class Trafic {
private:
    std::string initial_hour;
    std::string last_hour;
    int level;

public:
    Trafic(const std::string& initial_hour, const std::string& last_hour, int level);
    Trafic();
    std::string getInitialHour() const;
    std::string getLastHour() const;
    int getLevel() const;
    Ubication getInitialUbication() const;
    Ubication getLastUbication() const;
    void ingresar_nivel_de_trafico();
    void guardar_en_archivo();
};

#endif // TRAFIC_H