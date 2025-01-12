/*
Universidad de las Fuerzas Armadas ESPE
Graficador de arboles KD
Alexis Viteri
Fecha de creacion:  12/01/2025
Ultima fecha de modificacion:   12/01/2025
Estructura de Datos
NRC:  1978
*/
#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

class Menu {
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
