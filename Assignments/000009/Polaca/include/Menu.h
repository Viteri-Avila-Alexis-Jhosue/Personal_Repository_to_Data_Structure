/*
Universidad de las Fuerzas Armadas ESPE
Programa para crear menu
Alexis Viteri
Fecha de creacion:  23/10/2024
Ultima fecha de modificacion:   23/11/2024
Estructura de Datos
NRC:  1978
*/
#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>



class  Menu {
private:
    std::vector<std::string> options;
    int selectedIndex;

public:
    Menu();
    void addOption(const std::string& option);
    void displayMenu();
    int getSelectedOption();
};

#endif // MENU_H
