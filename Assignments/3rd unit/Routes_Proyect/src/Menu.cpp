#include "../include/Menu.h"
#include "../include/Ubication.h"
#include  "../include/KD_Tree.h"
#include <iostream>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <functional>
#include "../include/Validation.h"
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

Menu::Menu() : selectedIndex(0), title("") {}

void Menu::addOption(const string &option)
{
    options.push_back(option);
}

void Menu::addTitle(const string &title)
{
    this->title = title;
}

void Menu::displayMenu()
{
    bool running = true;

    while (running)
    {
        CLEAR();
        if (!title.empty())
        {
            cout << title << "\n";
        }
        cout << "\n";
        for (size_t i = 0; i < options.size(); ++i)
        {
            if (static_cast<int>(i) == selectedIndex)
            {
                cout << "==> " << options[i] << " \n";
            }
            else
            {
                cout << "  " << options[i] << "\n";
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
//------------------------------------------------------------------------------------------------------------------------

void Menu::principal_menu(int size,KD_Tree<Ubication>& ubication_tree)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    string archivo, comando, name, name1, name2;
    int x,y,continuador;
    Ubication ubication;
    Validation validation;
    while (running)
    {
        options.clear();
        addOption("Definir nueva ubicacion");
        addOption("Definir nueva ruta");
        addOption("Modificar ruta existente");
        addOption("Definir niveles de trafico");
        addOption("Modificar niveles de trafico");
        addOption("Iniciar simulacion de viaje");
        addOption("Imprimir rutas");
        addOption("Imprimir ubicaciones");
        addOption("Imprimir graficas estadisticas");
        addOption("Ayuda");
        addOption("Salir");
        addTitle("\t Gestor de rutas");
        displayMenu();

        switch (getSelectedOption())
        {
        case 0:
        {
            cout << "Definir nueva ubicacion" << endl;
            x=ubication.ingresar_coordenada(size,0);
            y=ubication.ingresar_coordenada(size,1);
            name=validation.ingresarStringConEspacios("\nIngrese el nombre del lugar: ");
            cout<<endl;
            ubication.ingresar_ubicacion(name,x,y);
            ubication_tree.insert(ubication,x,y);
            system("pause");
            break;
        }
        case 1:
        {
            cout << "Definir nueva ruta" << endl;
            name=validation.ingresarStringConEspacios("Ingrese el nombre de la ruta:  ");
            name1= validation.ingresarStringConEspacios("Ingrese el punto inicial de la ruta: ");
            name2= validation.ingresarStringConEspacios("Ingrese la siguiente ubicacion:  ");
            while (continuador==0)
            {
                continuador=auxiliar_menu();
                if(continuador==0){
                    name1=validation.ingresarStringConEspacios("Ingrese el nombre de la ubicacion");
                }  
            }
            
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Modificar ruta existente" << endl;
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Definir niveles de trafico" << endl;
            system("pause");
            break;
        }
        case 4:
        {
            cout << "Modificar niveles de trafico" << endl;
            system("pause");
            break;
        }
        case 5:
        {
            cout << "Iniciar simulacion de viaje" << endl;
            system("pause");
            break;
        }
        case 6:
        {
            cout << "Imprimir rutas" << endl;
            system("pause");
            break;
        }
        case 7:
        {
            cout << "Imprimir ubicaciones" << endl;
            ubication_tree.print_ubicaciones();
            system("pause");
            break;
        }
        case 8:
        {
            cout << "Imprimir graficas estadisticas" << endl;
            system("pause");
            break;
        }
        case 9:
        {
            cout << "Ayuda" << endl;
            archivo = "resources/ayuda.html";
            comando = "start " + archivo;
            system(comando.c_str());
            system("pause");
            break;
        }
        case 10:
        {
            cout << "Salir";
            running = false;
            break;
        }

        default:
            break;
        }
    }
}
int Menu::auxiliar_menu(){
    bool running = true;
    
    while (running) {
        options.clear();
        addOption("Ingresar nueva ubicacion");
        addOption("Finalizar Ruta");
        addTitle("\t Seleccione para continuar");
        displayMenu();
    }
    return getSelectedOption();
}