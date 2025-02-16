#include "../include/Route.h"
#include "../include/Validation.h"
#include "../include/Trafic.h"
#include <iostream>
#include <cmath>

Route::Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed)
    : name(name), distance(distance), initial(initial), last(last), speed(speed) {}

Route::Route() : name(""), distance(0.0), speed(0.0) {
    initial = Ubication(0, 0, "");  // Puedes inicializar con valores por defecto
    last = Ubication(0, 0, "");
    trafic = Trafic("","",0);
}

Route::Route(const std::string& name, double distance, const Ubication& initial, const Ubication& last, double speed, Trafic trafic)
    : name(name), distance(distance), initial(initial), last(last), speed(speed), trafic(trafic) {}

std::string Route::getName() const { return name; }

double Route::getDistance() const { return distance; }

Ubication Route::getInitialUbication() const { return initial; }

Ubication Route::getLastUbication() const { return last; }

Trafic Route::getTrafic() const { return trafic;}

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

void Route::agregar_trafico(Trafic trafic) {
    this->trafic = trafic;
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
    if (!trafic.getInitialHour().empty() && !trafic.getLastHour().empty() && trafic.getLevel() > 0) {
        file << "," << trafic.getInitialHour() << ","
             << trafic.getLastHour() << ","
             << trafic.getLevel();
    }

    file << "\n";

    // Cerrar el archivo
    file.close();
}
