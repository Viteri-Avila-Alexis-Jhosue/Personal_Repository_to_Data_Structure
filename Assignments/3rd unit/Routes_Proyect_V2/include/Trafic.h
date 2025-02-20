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
    void setLevel(int newLevel) {
        level = newLevel;
    }
    bool overlapsWith(const Trafic& other) const {
        return (initial_hour < other.last_hour) && (last_hour > other.initial_hour);
    }
    void setLastHour(const std::string& hour) {
        last_hour = hour;
    }
};

#endif // TRAFIC_H