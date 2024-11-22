/*
Universidad de las Fuerzas Armadas ESPE
Libreria para operaciones con datos de Personas
Alexis Viteri
Fecha de creacion:  21/11/2024
Ultima fecha de modificacion:   21/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Person.h"
#include <iostream>
#include <stdexcept>
#include <regex>
#include <cmath>

using namespace std;
Person::Person() : nombre1(""), nombre2(""), apellido1(""), apellido2(""), correoInstitucional("") {}

Person::Person(const std::string& nombre1, const std::string& nombre2,
                 const std::string& apellido1, const std::string& apellido2,
                 const std::string& correoInstitucional)
    : nombre1(nombre1), nombre2(nombre2), apellido1(apellido1),
      apellido2(apellido2), correoInstitucional(correoInstitucional) {}

std::string Person::getNombreCompleto() const {
    return nombre1 + " " + nombre2 + " " + apellido1 + " " + apellido2;
}

std::string Person::getCorreoInstitucional() const {
    return correoInstitucional;
}

std::ostream& operator<<(std::ostream& os, const Person& Person) {
    os << Person.getNombreCompleto() << " | Correo: " << Person.getCorreoInstitucional();
    return os;
}
// Validar el ID (debe ser un número de 10 dígitos)
void Person::validateId(int id) {
    string idStr = to_string(id);

    while (idStr.length() < 10) idStr = "0" + idStr; // Agregar ceros iniciales si faltan

    if (idStr.length() != 10) {
        throw invalid_argument("La cédula debe tener exactamente 10 dígitos.");
    }

    int provincia = stoi(idStr.substr(0, 2));
    if (provincia < 1 || provincia > 24) {
        throw invalid_argument("El código de provincia en la cédula no es válido.");
    }

    int total = 0;
    for (int i = 0; i < 9; i++) {
        int digit = idStr[i] - '0';
        if (i % 2 == 0) { // Posiciones impares
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        total += digit;
    }

    int verificador = idStr[9] - '0';
    int residuo = total % 10;
    int resultado = residuo == 0 ? 0 : 10 - residuo;

    if (verificador != resultado) {
        throw invalid_argument("La cédula ingresada no es válida.");
    }

    cout << "Cédula válida." << endl;
}


// Validar el correo electrónico (formato estándar)
void Person::validateEmail(const string& email) {
    regex emailPattern(R"((\w+)(\.\w+)*@(\w+\.)+\w{2,})");
    if (!regex_match(email, emailPattern)) {
        throw invalid_argument("El correo electrónico no es válido.");
    }
    cout << "Correo electrónico válido." << endl;
}

// Validar el número de teléfono (debe ser un número de 10 dígitos)
void Person::validateCellPhone(const string& cellPhone) {
    if (cellPhone.length() != 10 || cellPhone[0] != '0') {
        throw invalid_argument("El número de teléfono debe comenzar con '0' y tener exactamente 10 dígitos.");
    }
    regex phonePattern(R"(^0\d{9}$)");
    if (!regex_match(cellPhone, phonePattern)) {
        throw invalid_argument("El número de teléfono no cumple con el formato esperado.");
    }
    cout << "Número de teléfono válido." << endl;
}

void Person::validateCellPhone(int cellPhone) {
    string phoneStr = to_string(cellPhone);
    while (phoneStr.length() < 10) phoneStr = "0" + phoneStr; // Agregar ceros iniciales si faltan
    validateCellPhone(phoneStr);
}


// Crear un correo electrónico institucional
string Person::createInstitutionalEmail(const string& name1, const string& name2, const string& lastname, const string& institution) {
    string email = name1.substr(0, 1) + name2.substr(0, 1) + lastname + institution;
    for (auto& c : email) {
        c = tolower(c); // Convertir a minúsculas
    }
    cout << "Correo institucional generado: " << email << endl;
    return email;
}

// Calcular la edad en función del año de nacimiento
int Person::calculateAge(int birthYear, int currentYear) {
    if (birthYear > currentYear) {
        throw invalid_argument("El año de nacimiento no puede ser mayor que el año actual.");
    }
    int age = currentYear - birthYear;
    cout << "Edad calculada: " << age << " años." << endl;
    return age;
}
