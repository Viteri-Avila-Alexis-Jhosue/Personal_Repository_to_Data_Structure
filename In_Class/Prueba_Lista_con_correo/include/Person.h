/*
Universidad de las Fuerzas Armadas ESPE
Libreria para operaciones con datos de personas
Alexis Viteri
Fecha de creacion:  21/11/2024
Ultima fecha de modificacion:   21/11/2024
Estructura de Datos
NRC:  1978
*/

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <regex>

using namespace std;

class Person {
    private:
    std::string nombre1;
    std::string nombre2;
    std::string apellido1;
    std::string apellido2;
    std::string correoInstitucional;
public:
    Person();
    Person(const std::string& nombre1, const std::string& nombre2,
            const std::string& apellido1, const std::string& apellido2,
            const std::string& correoInstitucional);
    void validateCellPhone(int cellPhone);
    void validateId( int id);
    void validateEmail( const string& email);
    void validateCellPhone( const string& cellPhone);
    string createInstitutionalEmail(const string& name1, const string& name2, const string &lastname, const string &institution);
    int calculateAge( int birthYear, int currentYear);
    std::string getNombreCompleto() const;
    std::string getCorreoInstitucional() const;

    // Sobrecarga del operador `<<`
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};

#endif
