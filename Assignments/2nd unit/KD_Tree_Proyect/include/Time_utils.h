#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <string>
#include <chrono>

std::chrono::system_clock::time_point convertirStringATimePoint(const std::string& fecha);
std::chrono::system_clock::time_point convertirStringATimePointHora(const std::string& hora);
std::chrono::system_clock::time_point definirFechaImprobable();

#endif // TIME_UTILS_H