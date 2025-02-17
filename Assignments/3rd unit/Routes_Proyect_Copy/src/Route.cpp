#include "../include/Route.h"
#include "../include/Validation.h"
#include "../include/Trafic.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>


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
    this->distance = distance;
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
            distance = validation.ingresarDouble("Ingrese la distancia personalizada");
            if (distance > 2 * size) {
                std::cout << "Error: La distancia no puede ser mayor a " << 2 * size << ". Inténtalo de nuevo." << std::endl;
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
            std::cout << "Error: La velocidad debe estar en el rango (0, 150]. Inténtalo de nuevo." << std::endl;
        }
    } while (speed <= 0 || speed > 150);

    setSpeed(speed);
    guardar_en_archivo();
}

void Route::agregar_trafico(const Trafic& trafic) {
    trafics.push_back(trafic);
}

void Route::guardar_en_archivo() {
    // Abrir el archivo en modo "append" (agregar al final)
    std::ofstream file("output//Rutas.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
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
        std::cerr << "Error: No se pudo abrir el archivo de Rutas para leer." << std::endl;
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
        std::cerr << "Error: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
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
        std::cerr << "Error: No se pudo abrir el archivo de Rutas para leer." << std::endl;
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
            std::cerr << "Error: Formato incorrecto en la línea -> " << linea << std::endl;
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
        std::cerr << "Error: No se pudo abrir el archivo de Rutas para escribir." << std::endl;
        return false;
    }

    for (const auto& l : lineas) {
        outputFile << l << "\n";
    }
    outputFile.close();

    return true;
}
