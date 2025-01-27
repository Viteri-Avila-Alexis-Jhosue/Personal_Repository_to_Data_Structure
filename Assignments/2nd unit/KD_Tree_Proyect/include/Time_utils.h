#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <string>
#include <chrono>

std::chrono::system_clock::time_point convertirStringATimePoint(const std::string& fecha);
std::chrono::system_clock::time_point convertirStringATimePointHora(const std::string& hora);
std::chrono::system_clock::time_point definirFechaImprobable();
std::chrono::system_clock::time_point convertirStringATimePoint02(const std::string& fecha);
std::chrono::minutes convertirStringAMinutos(const std::string& hora);
std::chrono::minutes convertirHoraAMinutos(const std::chrono::system_clock::time_point& fechaHora);

#endif // TIME_UTILS_H