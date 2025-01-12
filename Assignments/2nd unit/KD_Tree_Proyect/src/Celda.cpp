
#include "../include/Celda.h"
#include "../include/Coche.h" 
#include "../include/Validaciones.h" 
#include "../include/Time_utils.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

// Constructor predeterminado
Celda::Celda() : coche() {}

// Constructor con parámetros
Celda::Celda(float x,float y, Coche coche) : coche(coche) {}
// Constructor que toma los parámetros adicionales de hora de ingreso y hora de salida
Celda::Celda(float x, float y, Coche coche, std::chrono::system_clock::time_point horaIngreso, std::chrono::system_clock::time_point horaSalida)
    : x(x), y(y), coche(coche), horaIngreso(horaIngreso), horaSalida(horaSalida) {
    // Inicialización adicional si es necesario
}

// Getter para el objeto Coche
Coche Celda::getCoche() const {
    return coche;
}

// Setter para el objeto Coche
void Celda::setCoche(const Coche& coche) {
    this->coche = coche;
}

// Setter para la coordenada x
void Celda::setX(float x) {
    this->x = x;
}

// Setter para la coordenada y

void Celda::setY(float y) {
    this->y = y;
}

// Getter para la coordenada x
float Celda::getX() const {
    return x;
}

// Getter para la coordenada y
float Celda::getY() const {
    return y;
}
//getter para la hora de ingreso
chrono::system_clock::time_point Celda::getHoraIngreso() const {
    return horaIngreso;
}
//getter para la hora de salida
chrono::system_clock::time_point Celda::getHoraSalida() const {
    return horaSalida;
}
//setter para la hora de ingreso
void Celda::setHoraIngreso(chrono::system_clock::time_point hora) {
    horaIngreso = hora;
}
//setter para la hora de salida
void Celda::setHoraSalida(chrono::system_clock::time_point hora) {
    horaSalida = hora;
}

// Método para guardar en el archivo autos_historial.txt
void Celda::guardarEnArchivo() const {
    // Abrir el archivo autos_historial.txt en modo de adición
    std::ofstream file("output//autos_historial.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo autos_historial.txt para escribir." << std::endl;
        return;
    }
     
    // Obtener los datos del coche
    const Coche& coche = getCoche();
    
    // Asignar la hora de entrada en este momento
    std::time_t ingreso_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    std::string horaIngresoStr = std::ctime(&ingreso_time);
    horaIngresoStr.pop_back(); // Eliminar el salto de línea al final

    // La hora de salida siempre será "N/A"
    std::string horaSalidaStr = "N/A";

    // Escribir los datos en el archivo
    file << x << ","
         << y << ","
         << coche.getPlaca() << ","
         << coche.getModelo() << ","
         << coche.getColor() << ","
         << coche.getMarca() << ","
         << horaIngresoStr << ","
         << horaSalidaStr << "\n";
         
    file.close();  // Cerrar el archivo
}
void Celda::ingresar_al_parqueadero(Coche coche) {
    Validaciones validaciones;
    string a,b;
    a = validaciones.ingresarCedula("Ingrese la coordenada x: ");
    b = validaciones.ingresarCedula("Ingrese la coordenada y: ");
    setX(stof(a));
    setY(stof(b));
    setCoche(coche);
    setHoraSalida(definirFechaImprobable());

    guardarEnArchivo();
}
std::string Celda::toString() const {
    std::cout << "Celda: (" << x << ", " << y << ")" << std::endl;

    // Conversión de std::chrono::system_clock::time_point a time_t
    std::time_t tiempoIngreso = std::chrono::system_clock::to_time_t(horaIngreso);
    std::time_t tiempoSalida = std::chrono::system_clock::to_time_t(horaSalida);

    // Mostrar las fechas correctamente
    std::cout << "Hora de ingreso: " << std::ctime(&tiempoIngreso);
    std::cout << "Hora de salida: " << std::ctime(&tiempoSalida);
    
    std::cout << "Datos del coche: " << std::endl;
    coche.toString(); // Asegúrate de que coche.toString() esté bien definido también.

    return "";
}


#include "Time_utils.h"

void Celda::retirar_del_parqueadero() {
    // Asignar la hora de salida al momento actual
    horaSalida = std::chrono::system_clock::now();

    // Definir la hora improbable
    std::chrono::system_clock::time_point fecha_improbable = definirFechaImprobable();

    // Leer el archivo `autos_historial.txt` y almacenar líneas actualizadas
    std::ifstream archivo_lectura("output//autos_historial.txt");
    std::vector<std::string> lineas;
    std::string linea;

    if (archivo_lectura.is_open()) {
        while (std::getline(archivo_lectura, linea)) {
            std::istringstream stream(linea);
            std::string x_archivo, y_archivo, placa_archivo, modelo_archivo, color_archivo, marca_archivo, horaIngreso_archivo, horaSalida_archivo;

            // Leer campos del archivo
            std::getline(stream, x_archivo, ',');
            std::getline(stream, y_archivo, ',');
            std::getline(stream, placa_archivo, ',');
            std::getline(stream, modelo_archivo, ',');
            std::getline(stream, color_archivo, ',');
            std::getline(stream, marca_archivo, ',');
            std::getline(stream, horaIngreso_archivo, ',');
            std::getline(stream, horaSalida_archivo, ',');

            // Convertir la hora de salida del archivo a time_point
            std::chrono::system_clock::time_point horaSalida_archivo_tp;
            if (horaSalida_archivo == "N/A") {
                horaSalida_archivo_tp = definirFechaImprobable();
            } else {
                horaSalida_archivo_tp = convertirStringATimePoint(horaSalida_archivo);
            }

            // Si la placa coincide y la hora de salida es igual a la fecha improbable, actualizamos la línea
            if (placa_archivo == coche.getPlaca() && horaSalida_archivo_tp == fecha_improbable) {
                std::ostringstream nueva_linea;
                auto horaSalida_time_t = std::chrono::system_clock::to_time_t(horaSalida);

                nueva_linea << x_archivo << "," << y_archivo << "," << placa_archivo << "," << modelo_archivo << "," 
                            << color_archivo << "," << marca_archivo << "," << horaIngreso_archivo << "," 
                            << std::put_time(std::localtime(&horaSalida_time_t), "%a %b %d %H:%M:%S %Y");

                lineas.push_back(nueva_linea.str());
            } else {
                // Si no coinciden, mantener la línea original
                lineas.push_back(linea);
            }
        }
        archivo_lectura.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para leer el historial de autos." << std::endl;
        return;
    }

    // Escribir las líneas actualizadas en el archivo
    std::ofstream archivo_escritura("output//autos_historial.txt", std::ios::trunc);
    if (archivo_escritura.is_open()) {
        for (const auto& linea_actualizada : lineas) {
            archivo_escritura << linea_actualizada << std::endl;
        }
        archivo_escritura.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para actualizar el historial de autos." << std::endl;
    }
}