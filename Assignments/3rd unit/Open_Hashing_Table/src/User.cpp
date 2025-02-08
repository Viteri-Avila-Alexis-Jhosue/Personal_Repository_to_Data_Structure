#include "../include/User.h"
#include "../include/Validation.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <fstream>
using namespace std;

User::User()
{
    id = 0;
    name = "";
    lastName = "";
    password = "";
}

User::User(int id, string name, string lastName, string password)
{
    this->id = id;
    this->name = name;
    this->lastName = lastName;
    this->password = password;
}

string User::getName() const
{
    return name;
}

void User::setName(string name)
{
    this->name = name;
}

string User::getLastName() const
{
    return lastName;
}

void User::setLastName(string lastName)
{
    this->lastName = lastName;
}

string User::getPassword() const
{
    return password;
}

void User::setPassword(string password)
{
    this->password = password;
}

int User::getId() const
{
    return id;
}

void User::setId(int id)
{
    this->id = id;
}

void User::ingresar_datos()
{
    Validation validation;
    id = validation.ingresarInt("Ingrese el id: ");
    cout << endl;
    name = validation.ingresarStringConEspacios("Ingrese el nombre: ");
    cout << endl;
    lastName = validation.ingresarStringConEspacios("Ingrese el apellido: ");
    cout << endl;
    password = validation.ingresarString("Ingrese la contraseña: ");
    cout << endl;
}

void User::guardar_en_archivo()
{
    std::ofstream file("output//Users.txt", std::ios::app);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo autos.txt para escribir." << std::endl;
        return;
    }
    file << id << ","
         << name << ","
         << lastName << ","
         << password << "\n";

    file.close();
}