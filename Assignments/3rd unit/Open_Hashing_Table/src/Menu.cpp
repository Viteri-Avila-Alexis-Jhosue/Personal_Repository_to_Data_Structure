/*
Universidad de las Fuerzas Armadas ESPE
Programa para crear menu
Alexis Viteri
Fecha de creacion:  23/10/2024
Ultima fecha de modificacion:   23/11/2024
Estructura de Datos
NRC:  1978
*/
#include "../include/Menu.h"
#include "../include/User.h"
#include "../include/Tree.h"
#include <iostream>
#include <conio.h> // Para _getch()
#define WIN32_LEAN_AND_MEAN
using namespace std;
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#undef byte
#define CLEAR() system("cls")
#else
#include <cstdlib>
#define CLEAR() system("clear")
#endif

Menu::Menu() : selectedIndex(0) {}

void Menu::addOption(const std::string &option)
{
    options.push_back(option);
}

void Menu::displayMenu()
{
    bool running = true;

    while (running)
    {
        CLEAR();
        std::cout << "Seleccione una opcion usando las flechas y presione Enter:\n\n";

        for (size_t i = 0; i < options.size(); ++i)
        {
            if (static_cast<int>(i) == selectedIndex)
            {
                std::cout << "==> " << options[i] << " \n";
            }
            else
            {
                std::cout << "  " << options[i] << "\n";
            }
        }

        int key = _getch();
        switch (key)
        {
        case 72: // Flecha arriba
            selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
            break;
        case 80: // Flecha abajo
            selectedIndex = (selectedIndex + 1) % options.size();
            break;
        case 13: // Enter
            running = false;
            break;
        }
    }
}

int Menu::getSelectedOption()
{
    return selectedIndex;
}
//--------------------------------------------------------------------------------------------
//--------------------------Menus de la aplicacion--------------------------------------------
//--------------------------------------------------------------------------------------------
void Menu::principal_menu(Tree<User> &tree)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    User user;
    while (running)
    {
        options.clear();
        addOption("Ingresar usuario");
        addOption("Mostrar usuario");
        addOption("Hashear datos");
        addOption("Dibujar tabla hash");
        addOption("Salir");
        displayMenu();
        switch (getSelectedOption())
        {
        case 0:
        {
            std::cout << "Ingresar usuario\n";
            user.ingresar_datos();
            user.guardar_en_archivo();
            tree.insert(user);
            system("pause");
            break;
        }
        case 1:
        {
            std::cout << "Mostrar usuarios\n";
            tree.inOrder();
            system("pause");
            break;
        }
        case 2:
        {
            std::cout << "Hshear datos\n";
            tree.hashear_datos(13);
            system("pause");
            break;
        }
        case 3:
        {
            std::cout << "Dibujar tabla hash\n";
            auxiliar_menu(tree);
            break;
        }
        case 4:
        {
            std::cout << "Salir";
            running = false;
            break;
        }
        }
    }
}

void Menu::auxiliar_menu(Tree<User> &tree)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    while (running)
    {
        options.clear();
        addOption("Tabla id");
        addOption("Tabla nombre");
        addOption("Tabla apellido");
        addOption("Tabla contraseña");
        addOption("Salir");
        displayMenu();
        switch (getSelectedOption())
        {
        case 0:
        {
            cout << "Tabla id\n";
            tree.tabla_hash_id();
            system("pause");
            break;
        }
        case 1:
        {
            cout << "Tabla nombre\n";
            tree.tabla_hash_nombre();
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Tabla apellido\n";
            tree.tabla_hash_apellido();
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Tabla contraseña\n";
            tree.tabla_hash_contrasena();
            system("pause");
            break;
        }
        case 4:
        {
            cout << "Salir";
            running = false;
            system("pause");
            break;
        }
        }
    }
}
