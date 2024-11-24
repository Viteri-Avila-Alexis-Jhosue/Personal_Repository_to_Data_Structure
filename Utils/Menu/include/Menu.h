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

// Macro para exportar/importar funciones en Windows
#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

class DLL_EXPORT Menu {
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
