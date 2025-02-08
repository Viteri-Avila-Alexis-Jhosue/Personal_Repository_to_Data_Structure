/*
Universidad de las Fuerzas Armadas ESPE
Programa para crear menu
Alexis Viteri
Fecha de creacion:  23/10/2024
Ultima fecha de modificacion:   03/02/2025
Estructura de Datos
NRC:  1978
*/
#include "../include/Tree.h"
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
    void principal_menu(Tree<User>& tree);
    void auxiliar_menu(Tree<User>& tree);
};

#endif // MENU_H
