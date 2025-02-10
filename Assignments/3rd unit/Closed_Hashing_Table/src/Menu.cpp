#include "../include/Menu.h"
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
# include "../include/Validation.h"
# include "../include/Closed_Hash.h"
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

void Menu::principal_menu()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    while (running)
    {
        options.clear();
        addOption("Tabla de enteros");
        addOption("Tabla de String");
        addOption("Salir");
        addTitle("\t Seleccione el tipo de datos");
        displayMenu();

        switch (getSelectedOption())
        {
        case 0:
        {
            cout << "Tabla de enteros" << endl;
            auxiliar_menu(0);
            system("pause");
            break;
        }
        case 1:
        {
            cout << "Tabla de String" << endl;
            auxiliar_menu(1);
            system("pause");
            break;
        }
        case 2:
        {
            running = false;
            break;
        }

        default:
            break;
        }
    }
}
void Menu::auxiliar_menu(int type)
{
    int num, num1;
    string palabra;
    Validation validation;
    bool running = true;
    Closed_Hash<Node> hashTableL(29, 0);
    Closed_Hash<Node> hashTableC(29, 1);
    Closed_Hash<Node> hashTableD(29, 2);

    while (running)
    {
        options.clear();
        addOption("Lineal");
        addOption("Cuadratica");
        addOption("Doble");
        addOption("Volver al menu principal");
        addTitle("\t Seleccione el Tipo ");
        displayMenu();

        switch (getSelectedOption())
        {
        case 0:
        {
            cout << " ineal " << endl;
            if(type==0){
                num = validation.ingresarInt("INGRESE SU NUMERO:\t");
                cout << endl;
                Node node(num, to_string(num));
                hashTableL.insert(node);
                hashTableL.display();
            } else {
                palabra = validation.ingresarString("INGRESE SU PALABRA:\t");
                cout << endl;
                num1 = hashTableL.convert_string_to_int(palabra);
                Node node(num1, palabra);
                hashTableL.insert(node);
                hashTableL.display();
            }
            system("pause");
            break;
        }
        case 1:
        {
            cout << "Cuadratica " << endl;
            if(type==0){
                num = validation.ingresarInt("INGRESE SU NUMERO:\t");
                cout << endl;
                Node node(num, to_string(num));
                hashTableC.insert(node);
                hashTableC.display();
            } else {
                palabra = validation.ingresarString("INGRESE SU PALABRA:\t");
                cout << endl;
                num1 = hashTableC.convert_string_to_int(palabra);
                Node node(num1, palabra);
                hashTableC.insert(node);
                hashTableC.display();
            }
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Doble " << endl;
            if(type==0){
                num = validation.ingresarInt("INGRESE SU NUMERO:\t");
                cout << endl;
                Node node(num, to_string(num));
                hashTableD.insert(node);
                hashTableD.display();
            } else {
                palabra = validation.ingresarString("INGRESE SU PALABRA:\t");
                cout << endl;
                num1 = hashTableD.convert_string_to_int(palabra);
                Node node(num1, palabra);
                hashTableD.insert(node);
                hashTableD.display();
            }
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Volviendo al menu principal" << endl;
            running = false;
            break;
        }

        default:
            break;
        }
    }
}