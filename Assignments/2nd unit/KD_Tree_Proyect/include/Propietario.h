#ifndef PROPIETARIO_H
#define PROPIETARIO_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Propietario 
{
private:
    string nombre;
    string apellido;
    string cedula;
    string correo;
    vector<string> placas; 

public:

    Propietario();
    Propietario(string nombre, string apellido, string cedula, string correo, vector<string> placas);    
    Propietario(string nombre, string apellido, string cedula, string correo);

    void setNombre(const string &nombre);
    void setApellido(const string &apellido);
    void setCedula(const string &cedula);
    void setCorreo(const string &correo);

   
    string getNombre() const;
    string getApellido() const;
    string getCedula() const;
    string getCorreo() const;

    
    void agregarPlaca(const string &placa);
    vector<string>& getPlacas() ;
    void eliminarPlaca(const std::string &placa);
    void ingresar_propietario();
    void guardar_en_archivo() const;
    string toString() const;
};
#endif // PROPIETARIO_H