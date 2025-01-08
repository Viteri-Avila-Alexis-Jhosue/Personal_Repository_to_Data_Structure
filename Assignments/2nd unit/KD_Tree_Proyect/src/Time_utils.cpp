#include "../include/Time_utils.h"
#include <sstream>
#include <iomanip>

std::chrono::system_clock::time_point convertirStringATimePoint(const std::string& fecha) {
    std::tm tm = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::chrono::system_clock::time_point convertirStringATimePointHora(const std::string& hora) {
    std::tm tm = {};
    std::istringstream ss(hora);
    ss >> std::get_time(&tm, "%H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::chrono::system_clock::time_point definirFechaImprobable() {
    struct std::tm tm_default = {};
    tm_default.tm_year = 1 - 1900;  // Año 1
    tm_default.tm_mon = 0;          // Enero
    tm_default.tm_mday = 1;         // Día 1
    return std::chrono::system_clock::from_time_t(std::mktime(&tm_default));
}