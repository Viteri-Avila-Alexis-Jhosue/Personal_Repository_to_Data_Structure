#include "../include/Trafic.h"
# include "../include/Ubication.h"
Trafic::Trafic(const std::string& initial_hour, const std::string& last_hour, int level)
    : initial_hour(initial_hour), last_hour(last_hour), level(level) {}

Trafic::Trafic(): initial_hour(""), last_hour(""), level(0){};

std::string Trafic::getInitialHour() const { return initial_hour; }

std::string Trafic::getLastHour() const { return last_hour; }

int Trafic::getLevel() const { return level; }
