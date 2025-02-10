#include "../include/Route.h"

Route::Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, const Trafic& level)
    : name(name), distance(distance), initial(initial), last(last), speed(speed), level(level) {}

std::string Route::getName() const { return name; }

double Route::getDistance() const { return distance; }

Ubication Route::getInitialUbication() const { return initial; }

Ubication Route::getLastUbication() const { return last; }

double Route::getSpeed() const { return speed; }

Trafic Route::getTraficLevel() const { return level; }