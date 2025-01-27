
#include "../include/Propietario.h"
#include "../include/Validaciones.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

Propietario::Propietario()
    : nombre(""), apellido(""), cedula(""), correo("") {}


Propietario::Propietario(string nombre, string apellido, string cedula, string correo)
    : nombre(nombre), apellido(apellido), cedula(cedula), correo(correo) {}

Propietario::Propietario(string nombre, string apellido, string cedula,string correo, vector<string> placas) {
    // Inicializar los miembros de la clase con los valores proporcionados
    this->nombre = nombre;
    this->apellido = apellido;
    this->cedula = cedula;
    this->correo = correo;
    this->placas = placas;
}

void Propietario::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

void Propietario::setApellido(const string &apellido)
{
    this->apellido = apellido;
}

void Propietario::setCedula(const string &cedula)
{
    this->cedula = cedula;
}

void Propietario::setCorreo(const string &correo)
{
    this->correo = correo;
}


string Propietario::getNombre() const
{
    return nombre;
}

string Propietario::getApellido() const
{
    return apellido;
}

string Propietario::getCedula() const
{
    return cedula;
}

string Propietario::getCorreo() const
{
    return correo;
}

void Propietario::agregarPlaca(const string &placa)
{
    placas.push_back(placa);
}

vector<string>& Propietario::getPlacas() 
{
    return placas;
}

string Propietario::toString() const
{
    string result = "Nombre: " + nombre + ", Apellido: " + apellido + ", Cedula: " + cedula + ", Correo: " + correo +  ", Placas: ";
    for (const auto &placa : placas)
    {
        result += placa + " ";
    }
    return result;
}
void Propietario::ingresar_propietario()
{
    Validaciones validaciones;
    nombre = validaciones.ingresarString("Ingrese el nombre del propietario: ");
    validaciones.to_upper(nombre);
    apellido = validaciones.ingresarString("Ingrese el apellido del propietario: ");
    apellido = validaciones.to_upper(apellido);
    do
    {
        cedula = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
        if (!validaciones.validarCedula(cedula))
        {
            cout << "Cedula invalida, intente de nuevo" << endl;
        }
    } while (!validaciones.validarCedula(cedula));
    do{
        correo = validaciones.ingresarCorreo("Ingrese el correo del propietario: ");
        if (!validaciones.validarCorreo(correo))
        {
            cout << "Correo invalido, intente de nuevo" << endl;
        }
    } while (!validaciones.validarCorreo(correo));
    
}
void Propietario::guardar_en_archivo() const {
    std::ifstream archivo_lectura("output//propietarios.txt");
    std::vector<std::string> lineas;
    std::string linea;
    bool encontrado = false;

    // Leer todo el archivo y guardar las líneas que no tienen la misma cédula
    if (archivo_lectura.is_open()) {
        while (std::getline(archivo_lectura, linea)) {
            std::istringstream stream(linea);
            std::string nombre_archivo, apellido_archivo, cedula_archivo;
            std::getline(stream, nombre_archivo, ',');
            std::getline(stream, apellido_archivo, ',');
            std::getline(stream, cedula_archivo, ',');

            // Si la cédula en el archivo es la misma que la del propietario, no lo agregues
            if (cedula_archivo == cedula) {
                encontrado = true;  // Propietario encontrado, no se agrega
            } else {
                lineas.push_back(linea);  // Guardar las líneas sin la cédula repetida
            }
        }
        archivo_lectura.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para leer los propietarios." << std::endl;
        return;
    }

    // Abrir el archivo en modo escritura para sobrescribir con los nuevos datos
    std::ofstream archivo_escritura("output//propietarios.txt", std::ios::trunc);
    if (archivo_escritura.is_open()) {
        // Escribir todas las líneas guardadas
        for (const auto& line : lineas) {
            archivo_escritura << line << std::endl;
        }

        // Ahora agregar el propietario actual
        archivo_escritura << nombre << "," << apellido << "," << cedula << "," << correo;
        for (const auto& placa : placas) {
            archivo_escritura << "," << placa;
        }
        archivo_escritura << std::endl;

        archivo_escritura.close();
    } else {
        std::cerr << "No se pudo abrir el archivo para guardar el propietario." << std::endl;
    }
}
void Propietario::eliminarPlaca(const std::string &placa) {
    auto it = std::find(placas.begin(), placas.end(), placa);
    if (it != placas.end()) {
        placas.erase(it);
        std::cout << "Placa eliminada: " << placa << std::endl;
    } else {
        std::cout << "La placa " << placa << " no está registrada para este propietario." << std::endl;
    }
}