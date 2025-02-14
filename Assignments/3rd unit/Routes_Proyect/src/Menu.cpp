#include "../include/Menu.h"
#include "../include/Ubication.h"
#include "../include/KD_Tree.h"
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

void Menu::principal_menu(int size, KD_Tree<Ubication> &ubication_tree, KD_Tree<Route> routes_tree)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    string archivo, comando, name, name1, name2;
    int x, y, continuador, cosa;
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
            x = ubication.ingresar_coordenada(size, 0);
            y = ubication.ingresar_coordenada(size, 1);

            // Verificar si ya existe una ubicación con las coordenadas dadas
            if (ubication_tree.findNode(x, y) != nullptr)
            {
                cout << "Error: Ya existe una ubicacion con las coordenadas (" << x << ", " << y << ")" << endl;
            }
            else
            {
                name = validation.ingresarStringConEspacios("\nIngrese el nombre del lugar: ");
                cout << endl;
                ubication.ingresar_ubicacion(name, x, y);
                ubication_tree.insert(ubication, x, y);
            }

            system("pause");
            break;
        }
        case 1:
{
    cout << "Definir nueva ruta" << endl;
    string routeName = validation.ingresarStringConEspacios("\nIngrese el nombre de la ruta: ");
    
    // Verificar si ya existe una ruta con el mismo nombre
    if (routes_tree.findNodeByName(routeName)) {
        cout << "Error: Ya existe una ruta con el nombre '" << routeName << "'" << endl;
        system("pause");
        break;
    }

    Ubication previousUbication;
    bool addingRoutes = true;

    while (addingRoutes) {
        // Mostrar el menú auxiliar para decidir si agregar una nueva ubicación o finalizar la ruta
        int option = auxiliar_menu();

        switch (option) {
            case 0: // Ingresar nueva ubicación
            {
                Ubication initialUbication;
                Ubication lastUbication;

                if (previousUbication.getName() == "") {
                    // Primera ubicación
                    cout << "Ingrese las coordenadas de la primera ubicación: " << endl;
                    int x1 = ubication.ingresar_coordenada(size, 0);
                    int y1 = ubication.ingresar_coordenada(size, 1);

                    // Verificar que la ubicación inicial exista
                    auto initialUbicationNode = ubication_tree.findNode(x1, y1);
                    if (initialUbicationNode == nullptr) {
                        cout << "Error: No existe una ubicación con las coordenadas (" << x1 << ", " << y1 << ")" << endl;
                        system("pause");
                        break;
                    }

                    initialUbication = initialUbicationNode->data;

                    cout << "\nIngrese las coordenadas de la segunda ubicación: " << endl;
                    int x2 = ubication.ingresar_coordenada(size, 0);
                    int y2 = ubication.ingresar_coordenada(size, 1);

                    // Verificar que la ubicación final exista
                    auto lastUbicationNode = ubication_tree.findNode(x2, y2);
                    if (lastUbicationNode == nullptr) {
                        cout << "Error: No existe una ubicación con las coordenadas (" << x2 << ", " << y2 << ")" << endl;
                        system("pause");
                        break;
                    }

                    lastUbication = lastUbicationNode->data;
                } else {
                    // Ubicaciones posteriores
                    auto initialUbicationNode = ubication_tree.findNode(previousUbication.getX(), previousUbication.getY());
                    initialUbication = initialUbicationNode->data;

                    cout << "Tramo desde " << initialUbication.getName() << " hasta: ?" << endl;
                    cout << "Ingrese las coordenadas de la segunda ubicación: " << endl;
                    int x2 = ubication.ingresar_coordenada(size, 0);
                    int y2 = ubication.ingresar_coordenada(size, 1);

                    // Verificar que la ubicación final exista
                    auto lastUbicationNode = ubication_tree.findNode(x2, y2);
                    if (lastUbicationNode == nullptr) {
                        cout << "Error: No existe una ubicación con las coordenadas (" << x2 << ", " << y2 << ")" << endl;
                        system("pause");
                        break;
                    }

                    lastUbication = lastUbicationNode->data;
                }

                // Definir la distancia
                int distance = distance_menu();

                // Crear la ruta
                Route newRoute;
                newRoute.definir_ruta(routeName, distance, initialUbication, lastUbication, size);

                // Insertar la ruta en el árbol de rutas
                routes_tree.insert(newRoute, initialUbication.getX(), initialUbication.getY());
                previousUbication = lastUbication; // Actualizar la ubicación anterior

                cout << "\nRuta agregada exitosamente." << endl;
                system("pause");
                break;
            }
            case 1: // Finalizar ruta
            {
                addingRoutes = false;
                cout << "Finalizando la creación de la ruta '" << routeName << "'." << endl;
                break;
            }
            default:
            {
                cout << "Opción no válida. Inténtelo de nuevo." << endl;
                system("pause");
                break;
            }
        }
    }

    cout << "Ruta '" << routeName << "' creada exitosamente." << endl;
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
            routes_tree.print_routes();
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

int Menu::auxiliar_menu()
{
    bool running = true;
    int selectedOption = -1;

    while (running)
    {
        options.clear();
        addOption("Ingresar nueva ubicacion");
        addOption("Finalizar Ruta");
        addTitle("\t Seleccione para continuar");
        displayMenu();

        selectedOption = getSelectedOption(); // Almacenar la opción seleccionada

        if (selectedOption == 0 || selectedOption == 1)
        {
            running = false; // Salir del bucle si se selecciona una opción válida
        }
        else
        {
            cout << "Opción no válida. Inténtelo de nuevo." << endl;
            system("pause");
        }
    }

    return selectedOption; // Devuelve 0 (Ingresar nueva ubicación) o 1 (Finalizar Ruta)
}

int Menu::distance_menu()
{
    bool running = true;
    while (running)
    {
        options.clear();
        addOption("Asignar distancia recta (Automáticamente)");
        addOption("Asignar distancia no recta (Manualmente)");
        addTitle("\t Seleccione para continuar");
        displayMenu();
        running = false; // Salir del bucle si se selecciona una opción válida
    }

    return getSelectedOption(); // Devuelve 0 (automático) o 1 (manual)
}