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

void Menu::principal_menu(int size, KD_Tree<Ubication> &ubication_tree, KD_Tree<Route> &routes_tree)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    string archivo, comando, name, name1, name2, initial_hour, last_hour;
    int x, y, continuador, cosa, a, b, level;
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
        addOption("Calculo de rutas optimas");
        addOption("Imprimir rutas");
        addOption("Imprimir ubicaciones");
        addOption("Imprimir graficas");
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
            if (routes_tree.findNodeByName(routeName))
            {
                cout << "Error: Ya existe una ruta con el nombre '" << routeName << "'" << endl;
                system("pause");
                break;
            }

            Ubication previousUbication;
            bool addingRoutes = true;
            bool rutaCreada = false;

            while (addingRoutes)
            {
                // Mostrar el menú auxiliar para decidir si agregar una nueva ubicación o finalizar la ruta
                int option = auxiliar_menu();

                switch (option)
                {
                case 0: // Ingresar nueva ubicación
                {
                    Ubication initialUbication;
                    Ubication lastUbication;

                    if (previousUbication.getName() == "")
                    {
                        // Primera ubicación
                        cout << "Ingrese las coordenadas de la primera ubicación: " << endl;
                        int x1 = ubication.ingresar_coordenada(size, 0);
                        int y1 = ubication.ingresar_coordenada(size, 1);

                        // Verificar que la ubicación inicial exista
                        auto initialUbicationNode = ubication_tree.findNode(x1, y1);
                        if (initialUbicationNode == nullptr)
                        {
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
                        if (lastUbicationNode == nullptr)
                        {
                            cout << "Error: No existe una ubicación con las coordenadas (" << x2 << ", " << y2 << ")" << endl;
                            system("pause");
                            break;
                        }

                        lastUbication = lastUbicationNode->data;
                    }
                    else
                    {
                        // Ubicaciones posteriores
                        auto initialUbicationNode = ubication_tree.findNode(previousUbication.getX(), previousUbication.getY());
                        initialUbication = initialUbicationNode->data;

                        cout << "Tramo desde " << initialUbication.getName() << " hasta: ?" << endl;
                        cout << "Ingrese las coordenadas de la segunda ubicación: " << endl;
                        int x2 = ubication.ingresar_coordenada(size, 0);
                        int y2 = ubication.ingresar_coordenada(size, 1);

                        // Verificar que la ubicación final exista
                        auto lastUbicationNode = ubication_tree.findNode(x2, y2);
                        if (lastUbicationNode == nullptr)
                        {
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
                    rutaCreada = true;
                    cout << "\nRuta agregada exitosamente." << endl;
                    system("pause");
                    break;
                }
                case 1: // Finalizar ruta
                {       // Finalizar ruta
                    addingRoutes = false;
                    if (rutaCreada)
                    {
                        cout << "Finalizando la creación de la ruta '" << routeName << "'." << endl;
                    }
                    else
                    {
                        cout << "No se ha creado la ruta '" << routeName << "' porque no se agregó ningún tramo." << endl;
                    }
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
            system("pause");
            break;
        }
        case 2:
        {
            cout << "Modificar ruta existente" << endl;
            routeCh_menu(size, ubication_tree, routes_tree);
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Definir niveles de trafico" << endl;

            // Solicitar el nombre de la ruta
            string routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta: ");

            // Verificar si la ruta existe en el árbol de rutas
            Route *ruta = routes_tree.getNodeByName(routeName);
            if (!ruta)
            {
                cout << "\nNo se encontró la ruta con el nombre: '" << routeName << "'." << endl;
                system("pause");
                break;
            }

            // Solicitar la primera ubicación y verificar si coincide con la ruta
            x, y;
            do
            {
                cout << "\nIngrese la primera Ubicacion: ";
                x = ubication.ingresar_coordenada(size, 0);
                y = ubication.ingresar_coordenada(size, 1);

                // Comparar con la ubicación inicial de la ruta
                ruta = routes_tree.getNodeByNameAndCoordinates(routeName, x, y);
                if (!ruta)
                {
                    cout << "Error: La ubicación con las coordenadas (" << x << ", " << y << ") no coincide con ningún tramo de la ruta '" << routeName << "'." << endl;
                }
                else
                {
                    break;
                }
            } while (true);
            do
            {
                cout << "Ingrese la segunda Ubicacion: ";
                a = ubication.ingresar_coordenada(size, 0);
                b = ubication.ingresar_coordenada(size, 1);

                Route *tramoFinal = routes_tree.getNodeByNameAndLastCoordinates(routeName, a, b);
                if (!tramoFinal)
                {
                    cout << "Error: La ubicación con las coordenadas (" << a << ", " << b << ") no coincide con ningún tramo de la ruta '" << routeName << "'." << endl;
                }
                else
                {
                    break;
                }
            } while (true);

            // Solicitar las horas de duración del tráfico
            cout << "Definir las horas de duracion del trafico\n";
            string initial_hour = validation.ingresarHora("Ingrese la hora de inicio del trafico:");
            string last_hour = validation.ingresarHora("Ingrese la hora de finalizacion del trafico:");

            // Solicitar el nivel de tráfico
            int level = level_menu();

            // Crear el objeto Trafic
            Trafic trafic(initial_hour, last_hour, level);

            // Aplicar tráfico a los tramos intermedios
            try
            {
                routes_tree.aplicarTraficoEntreUbicaciones(routeName, x, y, a, b, trafic);
                cout << "El tráfico ha sido asignado correctamente a la ruta: " << routeName << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Error: " << e.what() << endl;
            }

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
            cout << "Calculo de rutas optimas" << endl;
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
            cout << "Imprimir graficas" << endl;
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
        addOption("Ingresar ubicacion");
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

int Menu::level_menu()
{
    bool running = true;
    while (running)
    {
        options.clear();
        addOption(" Trafico bajo");
        addOption(" Trafico medio");
        addOption(" Trafico alto");
        addTitle("\t Seleccione el nivel de trafico");
        displayMenu();
        running = false; // Salir del bucle si se selecciona una opción válida
    }

    return getSelectedOption() + 1;
}

void Menu::routeCh_menu(int size, KD_Tree<Ubication> &ubication_tree, KD_Tree<Route> &routes_tree)
{
    bool running = true;
    Validation validation;
    Route *ruta;
    Route *initial;
    Route *last1;
    string routeName;
    Ubication ubication;
    while (running)
    {
        options.clear();
        addOption(" Cambiar el nombre de la ruta");
        addOption(" Modificar la velocidad en un tramo");
        addOption(" Modificar la distancia entre ubicaciones de un tramo");
        addOption(" Ampliar ruta");
        addOption(" Eliminar ruta");
        addOption(" Salir");
        addTitle("\t ¿Qué desea cambiar en la ruta?");
        displayMenu();

        switch (getSelectedOption())
        {
        case 0:
        { // Cambiar el nombre de la ruta
            routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta a cambiar: ");
            ruta = routes_tree.getNodeByName(routeName);
            if (!ruta)
            {
                cout << "\nNo se encontró la ruta con el nombre: '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            else
            {
                string nuevoNombre = validation.ingresarStringConEspacios("Ingrese el nuevo nombre de la ruta: ");

                // Verificar si el nuevo nombre ya existe
                if (routes_tree.getNodeByName(nuevoNombre))
                {
                    cout << "\nError: Ya existe una ruta con el nombre '" << nuevoNombre << "'." << endl;
                    system("pause");
                    break;
                }

                // Cambiar el nombre en todos los tramos de la ruta
                Route *tramo = routes_tree.getNodeByName(routeName);
                while (tramo)
                {
                    tramo->setName(nuevoNombre);                  // Cambiar el nombre del tramo actual
                    tramo = routes_tree.getNodeByName(routeName); // Buscar el siguiente tramo con el nombre original
                }

                cout << "\nEl nombre de la ruta ha sido cambiado a: " << nuevoNombre << endl;
                system("pause");
            }
            break;
        }

        case 1:
        { // Modificar la velocidad en un tramo
            routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta: ");
            ruta = routes_tree.getNodeByName(routeName);
            if (!ruta)
            {
                cout << "\nNo se encontró la ruta con el nombre: '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            else
            {
                cout << endl;
                int x = validation.ingresarInt("Ingrese la coordenada X de la ubicación inicial del tramo: ");
                cout << endl;
                int y = validation.ingresarInt("Ingrese la coordenada Y de la ubicación inicial del tramo: ");
                Route *tramo = routes_tree.getNodeByNameAndCoordinates(routeName, x, y);
                cout << "paso";
                if (!tramo)
                {
                    cout << "\nNo se encontró el tramo con las coordenadas (" << x << ", " << y << ")." << endl;
                    system("pause");
                    break;
                }
                else
                {
                    double nuevaVelocidad;
                    do
                    {
                        nuevaVelocidad = validation.ingresarDouble("\nIngrese la nueva velocidad para el tramo (0 < velocidad <= 150): ");
                        if (nuevaVelocidad <= 0 || nuevaVelocidad > 150)
                        {
                            cout << "\nError: La velocidad debe ser mayor a 0 y menor o igual a 150." << endl;
                        }
                    } while (nuevaVelocidad <= 0 || nuevaVelocidad > 150);

                    tramo->setSpeed(nuevaVelocidad);
                    cout << "\nLa velocidad del tramo ha sido modificada a: " << nuevaVelocidad << endl;
                    system("pause");
                }
            }
            break;
        }

        case 2:
        { // Modificar la distancia entre ubicaciones de un tramo
            routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta: ");
            ruta = routes_tree.getNodeByName(routeName);
            if (!ruta)
            {
                cout << "\nNo se encontró la ruta con el nombre: '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            else
            {
                int x = validation.ingresarInt("Ingrese la coordenada X de la ubicación inicial del tramo: ");
                int y = validation.ingresarInt("Ingrese la coordenada Y de la ubicación inicial del tramo: ");
                Route *tramo = routes_tree.getNodeByNameAndCoordinates(routeName, x, y);
                if (!tramo)
                {
                    cout << "\nNo se encontró el tramo con las coordenadas (" << x << ", " << y << ")." << endl;
                    system("pause");
                    break;
                }
                else
                {
                    // Calcular la distancia recta entre las ubicaciones inicial y final
                    Ubication inicio = tramo->getInitialUbication();
                    Ubication fin = tramo->getLastUbication();
                    double dx = fin.getX() - inicio.getX();
                    double dy = fin.getY() - inicio.getY();
                    double distanciaMinima = std::sqrt(dx * dx + dy * dy);

                    double nuevaDistancia;
                    do
                    {
                        nuevaDistancia = validation.ingresarDouble("Ingrese la nueva distancia entre las ubicaciones : ");
                        if (nuevaDistancia < distanciaMinima)
                        {
                            cout << "Error: La distancia no puede ser menor que la distancia recta (" << distanciaMinima << ")." << endl;
                        }
                    } while (nuevaDistancia < distanciaMinima);

                    tramo->setDistance(nuevaDistancia);
                    cout << "La distancia del tramo ha sido modificada a: " << nuevaDistancia << endl;
                    system("pause");
                }
            }
            break;
        }
        case 3:
        {
            cout << "Ampliar ruta" << endl;
            string routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta a ampliar:  ");

            // Obtener las ubicaciones inicial y final de la ruta
            initial = routes_tree.obtenerUbicacionInicial(routeName);
            last1 = routes_tree.obtenerUbicacionFinal(routeName);

            if (initial == nullptr || last1 == nullptr)
            {
                cout << "Error: No se encontró la ruta '" << routeName << "' o no es válida." << endl;
                system("pause");
                break;
            }

            cout << "\nLa ubicación desde la cual puede ampliar es:  " << endl;
            cout << "(" << last1->getLastUbication().getX() << "; " << last1->getLastUbication().getY() << ")" << endl;
            cout << "O, en el sentido contrario, un tramo hasta:  " << endl;
            cout << "(" << initial->getInitialUbication().getX() << "; " << initial->getInitialUbication().getY() << ")" << endl;
            system("pause");
            // Usar el menú para preguntar desde dónde se desea ampliar
            int choice = enlarge_route();

            Ubication startUbication;
            if (choice == 0)
            {
                startUbication = initial->getInitialUbication();
                cout << "Tramo desde ? hasta " << startUbication.getName() << endl;
            }
            else if (choice == 1)
            {
                startUbication = last1->getLastUbication();
                cout << "Tramo desde " << startUbication.getName() << "hasta ?" << endl;
            }
            else
            {
                cout << "Saliendo." << endl;
                system("pause");
                break;
            }

            cout << "Ingrese las coordenadas de la nueva ubicación: " << endl;
            int newX = ubication.ingresar_coordenada(size, 0);
            int newY = ubication.ingresar_coordenada(size, 1);

            // Verificar que la ubicación ingresada exista en el árbol de ubicaciones
            auto newUbicationNode = ubication_tree.findNode(newX, newY);
            if (newUbicationNode == nullptr)
            {
                cout << "Error: No existe una ubicación con las coordenadas (" << newX << ", " << newY << ")" << endl;
                system("pause");
                break;
            }

            Ubication newUbication = newUbicationNode->data;

            // Determinar el sentido de ampliación
            if (choice == 0)
            {
                // Ampliar al inicio
                int distance = distance_menu();
                Route newRoute;
                newRoute.definir_ruta(routeName, distance, newUbication, initial->getInitialUbication(), size);
                routes_tree.insert(newRoute, newUbication.getX(), newUbication.getY());
                cout << "Ruta ampliada exitosamente al inicio." << endl;
            }
            else if (choice == 1)
            {
                // Ampliar al final
                int distance = distance_menu();
                Route newRoute;
                newRoute.definir_ruta(routeName, distance, last1->getLastUbication(), newUbication, size);
                routes_tree.insert(newRoute, last1->getLastUbication().getX(), last1->getLastUbication().getY());
                cout << "Ruta ampliada exitosamente al final." << endl;
            }

            system("pause");
            break;
        }

        case 4:
        {
            cout << "Eliminar ruta" << endl;
            delete_route(routes_tree);
            system("pause");
            break;
        }
        case 5:
        {
            running = false;
            break;
        }

        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            system("pause");
            running = true; // Volver a mostrar el menú
            break;
        }
    }
}
void Menu::delete_route(KD_Tree<Route> &routes_tree)
{
    Validation validation;
    bool running = true;
    while (running)
    {
        options.clear();
        addOption(" Eliminar una ruta completa");
        addOption(" Eliminar un tramo de una ruta");
        addOption(" Salir");
        addTitle(" ");
        displayMenu();
        switch (getSelectedOption())
        {
        case 0:
        {
            cout << "Eliminar una ruta completa" << endl;
            string routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta a eliminar: ");
            if (!routes_tree.findNodeByName(routeName))
            {
                cout << "Error: No existe una ruta con el nombre '" << routeName << "'" << endl;
                system("pause");
                break;
            }
            routes_tree.eliminarRutaCompleta(routeName);
            cout << "Ruta '" << routeName << "' eliminada exitosamente." << endl;
            system("pause");
            break;
        }
        case 1: // Eliminar un tramo de una ruta
        {
            cout << "Eliminar un tramo de una ruta" << endl;
            string routeName = validation.ingresarStringConEspacios("Ingrese el nombre de la ruta: ");
            if (!routes_tree.findNodeByName(routeName))
            {
                cout << "Error: No existe una ruta con el nombre '" << routeName << "'" << endl;
                system("pause");
                break;
            }
            Route *initial = routes_tree.obtenerUbicacionInicial(routeName);
            Route *last1 = routes_tree.obtenerUbicacionFinal(routeName);

            if (initial == nullptr || last1 == nullptr)
            {
                cout << "Error: No se pudo obtener la información de la ruta '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            cout << "\nLos tramos que se pueden eliminar son:\nEl tramo desde:   ";
            cout << initial->getInitialUbication().getName();
            cout << " (" << initial->getInitialUbication().getX() << "; " << initial->getInitialUbication().getY() << ")\t";
            cout << "hasta:   ";
            cout << initial->getLastUbication().getName();
            cout << " (" << initial->getLastUbication().getX() << "; " << initial->getLastUbication().getY() << ")" << endl;
            cout << "El tramo desde:  ";
            cout << last1->getInitialUbication().getName();
            cout << " (" << last1->getInitialUbication().getX() << "; " << last1->getInitialUbication().getY() << ")\t";
            cout << "hasta:  ";
            cout << last1->getLastUbication().getName();
            cout << " (" << last1->getLastUbication().getX() << "; " << last1->getLastUbication().getY() << ")" << endl;
            int xInicial = validation.ingresarInt("Ingrese la coordenada X inicial: ");
            int yInicial = validation.ingresarInt("\nIngrese la coordenada Y inicial: ");
            Route *ruta = routes_tree.getNodeByNameAndCoordinates(routeName, xInicial, yInicial);
            if (!ruta)
            {
                cout << "Error: La ubicación con las coordenadas (" << xInicial << ", " << yInicial << ") no coincide con ningún tramo de la ruta '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            else if ((xInicial != initial->getInitialUbication().getX() || yInicial != initial->getInitialUbication().getY()) &&
                     (xInicial != last1->getInitialUbication().getX() || yInicial != last1->getInitialUbication().getY()))
            {
                cout << "Error: La ubicación con las coordenadas (" << xInicial << ", " << yInicial << ") no se puede eliminar de la ruta '" << routeName << "'." << endl;
                system("pause");
                break;
            }
            routes_tree.eliminarTramo(routeName, xInicial, yInicial, ruta->getLastUbication().getX(), ruta->getLastUbication().getY());
            cout << "Tramo eliminado exitosamente." << endl;
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

int Menu::enlarge_route()
{
    bool running = true;
    while (running)
    {
        options.clear();
        addOption(" Ampliar al inicio");
        addOption(" Apliar al final");
        addOption(" No ampliar");
        addTitle("\t En que sentido desea ampliar?");
        displayMenu();
        running = false; // Salir del bucle si se selecciona una opción válida
    }

    return getSelectedOption();
}