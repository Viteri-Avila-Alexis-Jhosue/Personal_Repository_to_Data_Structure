/*
Universidad de las Fuerzas Armadas ESPE
Programa Para el ingreso de datos en diferentes tipos de listas
Alexis Viteri
Fecha de creacion:  26/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

class Nodo {
private:
    int id;
    string name1;
    string name2;
    string lastname1;
    string lastname2;
    string institucionalEmail;
    Nodo* next;    // Puntero al siguiente nodo
    Nodo* prev;    // Puntero al nodo anterior

public:
    // Constructor
    Nodo(int id, string name1, string name2, string lastname1, string lastname2, string institucionalEmail);

    // Destructor
    ~Nodo();

    // Getters
    int getId() const;
    string getName1() const;
    string getName2() const;
    string getLastname1() const;
    string getLastname2() const;
    string getInstitucionalEmail() const;
    Nodo* getNext() const;
    Nodo* getPrev() const;

    // Setters
    void setId(int newId);
    void setName1(const string& newName1);
    void setName2(const string& newName2);
    void setLastname1(const string& newLastname1);
    void setLastname2(const string& newLastname2);
    void setInstitucionalEmail(const string& newEmail);
    void setNext(Nodo* newNext);
    void setPrev(Nodo* newPrev);
    void encriptarDatos(int clave);
};

#endif
