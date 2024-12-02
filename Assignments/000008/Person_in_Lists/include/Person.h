/*
Universidad de las Fuerzas Armadas ESPE
Libreria para operaciones con datos de personas
Alexis Viteri
Fecha de creacion:  21/11/2024
Ultima fecha de modificacion:   26/11/2024
Estructura de Datos
NRC:  1978
*/

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <list>
#include "Nodo.h"
#include "Circular_list.h"
#include "Double_list.h"
#include "Simple_list.h"
using namespace std;

class Person {
public:
    string createInstitutionalEmailList(
        const string& name1,
        const string& name2,
        const string& lastname,
        const string& institution,
        const Nodo* head);
    void validateCellPhone(int cellPhone);
    bool validateId(int id);
    void validateEmail(const string& email);
    void validateCellPhone(const string& cellPhone);
    string createInstitutionalEmail(const string& name1, const string& name2, const string& lastname, const string& institution);
    int calculateAge(int birthYear, int currentYear);
};

#endif
