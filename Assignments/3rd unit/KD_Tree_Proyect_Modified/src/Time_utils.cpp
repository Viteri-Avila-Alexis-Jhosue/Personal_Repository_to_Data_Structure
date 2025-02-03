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
    tm_default.tm_year = 1 - 1900;  
    tm_default.tm_mon = 0;          
    tm_default.tm_mday = 1;         
    return std::chrono::system_clock::from_time_t(std::mktime(&tm_default));
}

std::chrono::system_clock::time_point convertirStringATimePoint02(const std::string& fecha) {
    std::tm tm = {};
    std::istringstream ss(fecha);
    ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y"); // Formato completo
    if (ss.fail()) {
        return std::chrono::system_clock::time_point(); // Retorna un punto inválido
    }
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::chrono::minutes convertirStringAMinutos(const std::string& hora) {
    std::tm tm = {};
    std::istringstream ss(hora);
    ss >> std::get_time(&tm, "%H:%M:%S");

    if (ss.fail()) {
        throw std::invalid_argument("Formato de hora inválido: " + hora);
    }

    return std::chrono::hours(tm.tm_hour) + std::chrono::minutes(tm.tm_min);
}

std::chrono::minutes convertirHoraAMinutos(const std::chrono::system_clock::time_point& fechaHora) {
    std::time_t tiempo = std::chrono::system_clock::to_time_t(fechaHora);
    std::tm* tm = std::localtime(&tiempo);
    return std::chrono::minutes(tm->tm_hour * 60 + tm->tm_min);
}