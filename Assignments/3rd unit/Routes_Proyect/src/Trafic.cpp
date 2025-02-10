#include "../include/Trafic.h"
# include "../include/Ubication.h"
Trafic::Trafic(const std::string& initial_hour, const std::string& last_hour, const std::string& level, const Ubication& initial, const Ubication& last)
    : initial_hour(initial_hour), last_hour(last_hour), level(level), initial(initial), last(last) {}

std::string Trafic::getInitialHour() const { return initial_hour; }

std::string Trafic::getLastHour() const { return last_hour; }

std::string Trafic::getLevel() const { return level; }

Ubication Trafic::getInitialUbication() const { return initial; }

Ubication Trafic::getLastUbication() const { return last; }