#include "../include/Route.h"
#include "../include/Validation.h"
#include "../include/Trafic.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>


Route::Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed)
    : name(name), distance(distance), initial(initial), last(last), speed(speed) {}

Route::Route() : name(""), distance(0.0), speed(0.0) {
    initial = Ubication(0, 0, "");
    last = Ubication(0, 0, "");
}

Route::Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, std::vector<Trafic> trafics)
    : name(name), distance(distance), initial(initial), last(last), speed(speed), trafics(trafics) {}

std::string Route::getName() const { return name; }

double Route::getDistance() const { return distance; }

Ubication Route::getInitialUbication() const { return initial; }

Ubication Route::getLastUbication() const { return last; }

std::vector<Trafic> Route::getTrafics() const { return trafics; }

double Route::getSpeed() const { return speed; }

void Route::setName(const std::string& name) {
    this->name = name;
}

void Route::setDistance(double distance) {
    this->distance = floor(distance * 100) / 100;
}


void Route::setInitialUbication(const Ubication& initial) {
    this->initial = initial;
}

void Route::setLastUbication(const Ubication& last) {
    this->last = last;
}

void Route::setSpeed(double speed) {
    this->speed = speed;
}

void Route::definir_ruta(std::string name, double distance, Ubication initial, Ubication last, int size) {
    Validation validation;
    setName(name);
    setInitialUbication(initial);
    setLastUbication(last);

    if (distance == 1) {
        // Ingresar distancia personalizada
        do {
            distance = validation.ingresarDouble("Ingrese la distancia personalizada:  ");
            if (distance > 2 * size) {
                std::cout << "\nError: La distancia no puede ser mayor a " << 2 * size << ". Inténtalo de nuevo." << std::endl;
            }
        } while (distance > 2 * size);
    } else {
        // Calcular la distancia euclidiana entre las ubicaciones inicial y final
        double dx = last.getX() - initial.getX();
        double dy = last.getY() - initial.getY();
        distance = sqrt(dx * dx + dy * dy);
    }
    setDistance(distance);

    // Validar velocidad dentro del rango permitido (mayor a 0 y hasta 150)
    do {
        speed = validation.ingresarDouble("Ingrese la velocidad (0 < velocidad <= 150):   ");
        if (speed <= 0 || speed > 150) {
            std::cout << "\nError: La velocidad debe estar en el rango (0, 150]. Inténtalo de nuevo." << std::endl;
        }
    } while (speed <= 0 || speed > 150);

    setSpeed(speed);
}


void Route::guardar_en_archivo() {
    // Abrir el archivo en modo "append" (agregar al final)
    std::ofstream file("output//Rutas.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "\nError: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
        return;
    }

    // Escribir los datos de la ruta en el archivo
    file << name << ","
         << initial.getX() << ","
         << initial.getY() << ","
         << initial.getName() << ","
         << last.getX() << ","
         << last.getY() << ","
         << last.getName() << ","
         << distance << ","
         << speed;
         for (const auto& trafic : trafics) {
            if (!trafic.getInitialHour().empty() && !trafic.getLastHour().empty() && trafic.getLevel() > 0) {
                file << "," << trafic.getInitialHour() << ","
                     << trafic.getLastHour() << ","
                     << trafic.getLevel();
            }
        }

    file << "\n";

    // Cerrar el archivo
    file.close();
}
bool Route::eliminarRutaDelArchivo(const std::string& nombreRuta) {
    std::ifstream inputFile("output//Rutas.txt");
    if (!inputFile.is_open()) {
        std::cerr << "\nError: No se pudo abrir el archivo de Rutas para leer." << std::endl;
        return false;
    }

    std::vector<std::string> lineas;
    std::string linea;

    // Leer todas las líneas del archivo
    while (std::getline(inputFile, linea)) {
        // Si la línea no comienza con el nombre de la ruta, la guardamos
        if (linea.find(nombreRuta + ",") != 0) {
            lineas.push_back(linea);
        }
    }
    inputFile.close();

    // Escribir las líneas restantes de vuelta al archivo
    std::ofstream outputFile("output//Rutas.txt", std::ios::trunc); // Abrir en modo truncar (sobrescribir)
    if (!outputFile.is_open()) {
        std::cerr << "\nError: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
        return false;
    }

    for (const auto& l : lineas) {
        outputFile << l << "\n";
    }
    outputFile.close();

    return true;
}

bool Route::eliminarTramoDelArchivo(const std::string& nombreRuta, int xInicial, int yInicial, int xFinal, int yFinal) {
    std::ifstream inputFile("output//Rutas.txt");
    if (!inputFile.is_open()) {
        std::cerr << "\nError: No se pudo abrir el archivo de Rutas para leer." << std::endl;
        return false;
    }

    std::vector<std::string> lineas;
    std::string linea;

    // Leer todas las líneas del archivo
    while (std::getline(inputFile, linea)) {
        std::stringstream ss(linea);
        std::vector<std::string> datos;
        std::string elemento;

        // Separar la línea por comas y almacenarla en un vector
        while (std::getline(ss, elemento, ',')) {
            datos.push_back(elemento);
        }

        // Verificar si la línea tiene al menos 7 elementos (ruta, x1, y1, destino, x2, y2, destino final)
        if (datos.size() < 7) {
            std::cerr << "\nError: Formato incorrecto en la línea -> " << linea << std::endl;
            continue;  // Ignorar líneas con formato incorrecto
        }

        // Extraer valores de la línea
        std::string name = datos[0];  // Nombre de la ruta
        int xi = std::stoi(datos[1]); // X inicial
        int yi = std::stoi(datos[2]); // Y inicial
        int xf = std::stoi(datos[4]); // X final
        int yf = std::stoi(datos[5]); // Y final

        // Si la línea NO coincide con el tramo a eliminar, la guardamos
        if (!(name == nombreRuta && xi == xInicial && yi == yInicial && xf == xFinal && yf == yFinal)) {
            lineas.push_back(linea);
        }
    }
    inputFile.close();

    // Escribir las líneas restantes de vuelta al archivo
    std::ofstream outputFile("output//Rutas.txt", std::ios::trunc);
    if (!outputFile.is_open()) {
        std::cerr << "\nError: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
        return false;
    }

    for (const auto& l : lineas) {
        outputFile << l << "\n";
    }
    outputFile.close();

    return true;
}

std::vector<Trafic> Route::agruparIntervalosConsecutivos(const std::vector<Trafic>& trafics) const {
    if (trafics.empty()) return {};

    std::vector<Trafic> groupedTrafics;
    Trafic currentTrafic = trafics[0]; // Empezar con el primer intervalo

    for (size_t i = 1; i < trafics.size(); ++i) {
        const Trafic& nextTrafic = trafics[i];

        // Verificar si son consecutivos y tienen el mismo nivel
        if (currentTrafic.getLastHour() == nextTrafic.getInitialHour() && currentTrafic.getLevel() == nextTrafic.getLevel()) {
            // Combinar los intervalos
            currentTrafic.setLastHour(nextTrafic.getLastHour());
        } else {
            // Agregar el intervalo actual a la lista agrupada
            groupedTrafics.push_back(currentTrafic);
            currentTrafic = nextTrafic; // Empezar un nuevo intervalo
        }
    }

    // Agregar el último intervalo
    groupedTrafics.push_back(currentTrafic);

    return groupedTrafics;
}

void Route::agregar_trafico(const Trafic& trafic) {
    std::vector<Trafic> newTrafics;

    // Si el nivel es 0, eliminar los intervalos que coincidan con el tiempo especificado
    if (trafic.getLevel() == 0) {
        for (const auto& existingTrafic : trafics) {
            if (existingTrafic.overlapsWith(trafic)) {
                // Dividir el intervalo existente en tres partes:
                // - Parte antes del solapamiento
                if (existingTrafic.getInitialHour() < trafic.getInitialHour()) {
                    newTrafics.push_back(Trafic(existingTrafic.getInitialHour(), trafic.getInitialHour(), existingTrafic.getLevel()));
                }
                // - Parte después del solapamiento
                if (existingTrafic.getLastHour() > trafic.getLastHour()) {
                    newTrafics.push_back(Trafic(trafic.getLastHour(), existingTrafic.getLastHour(), existingTrafic.getLevel()));
                }
            } else {
                // No hay solapamiento, agregar el intervalo existente tal cual
                newTrafics.push_back(existingTrafic);
            }
        }
    } else {
        // Si el nivel no es 0, dividir intervalos solapados como antes
        for (const auto& existingTrafic : trafics) {
            if (existingTrafic.overlapsWith(trafic)) {
                // Dividir el intervalo existente en tres partes:
                // - Parte antes del solapamiento
                if (existingTrafic.getInitialHour() < trafic.getInitialHour()) {
                    newTrafics.push_back(Trafic(existingTrafic.getInitialHour(), trafic.getInitialHour(), existingTrafic.getLevel()));
                }
                // - Parte solapada (usar el nivel del nuevo tráfico)
                newTrafics.push_back(Trafic(
                    std::max(existingTrafic.getInitialHour(), trafic.getInitialHour()),
                    std::min(existingTrafic.getLastHour(), trafic.getLastHour()),
                    trafic.getLevel()
                ));
                // - Parte después del solapamiento
                if (existingTrafic.getLastHour() > trafic.getLastHour()) {
                    newTrafics.push_back(Trafic(trafic.getLastHour(), existingTrafic.getLastHour(), existingTrafic.getLevel()));
                }
            } else {
                // No hay solapamiento, agregar el intervalo existente tal cual
                newTrafics.push_back(existingTrafic);
            }
        }
        // Agregar el nuevo tráfico si no está completamente cubierto por los intervalos existentes
        newTrafics.push_back(trafic);
    }

    // Ordenar los intervalos por hora de inicio
    std::sort(newTrafics.begin(), newTrafics.end(), [](const Trafic& a, const Trafic& b) {
        return a.getInitialHour() < b.getInitialHour();
    });

    // Agrupar intervalos consecutivos con el mismo nivel
    trafics = agruparIntervalosConsecutivos(newTrafics);

    // Eliminar intervalos duplicados
    auto last = std::unique(trafics.begin(), trafics.end(), [](const Trafic& a, const Trafic& b) {
        return a.getInitialHour() == b.getInitialHour() &&
               a.getLastHour() == b.getLastHour() &&
               a.getLevel() == b.getLevel();
    });
    trafics.erase(last, trafics.end());
}