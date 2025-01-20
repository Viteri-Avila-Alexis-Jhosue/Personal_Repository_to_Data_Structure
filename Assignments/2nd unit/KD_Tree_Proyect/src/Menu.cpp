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
#include "../include/Ordenamientos.h"
#include "../include/Coche.h"
#include "../include/Propietario.h"
#include "../include/Validaciones.h"
#include "../include/Celda.h"
#include "../include/KD_Tree.h"
using namespace std;
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX // Evita conflictos con las macros min y max
#endif
#include <windows.h> // Para limpiar pantalla en Windows
#undef byte // Evitar ambigüedad con std::byte
#define CLEAR() system("cls")
#else
#include <cstdlib>
#define CLEAR() system("clear")
#endif


Menu::Menu() : selectedIndex(0), title("") {}

void Menu::addOption(const string& option) {
    options.push_back(option);
}

void Menu::addTitle(const string& title) {
    this->title = title;
}

void Menu::displayMenu() {
    bool running = true;

    while (running) {
        CLEAR();
        if (!title.empty()) {
            cout << title << "\n";
        }
        cout << "\n";
        for (size_t i = 0; i < options.size(); ++i) {
            if (static_cast<int>(i) == selectedIndex) {
                cout << "==> " << options[i] << " \n";
            } else {
                cout << "  " << options[i] << "\n";
            }
        }
        int key = _getch();
        switch (key) {
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

int Menu::getSelectedOption() {
    return selectedIndex;
}
//---------------------------------------------------------------------------------------------------------
//--------------------------------Menus de la aplicacion---------------------------------------------------
//---------------------------------------------------------------------------------------------------------
void Menu::principal_menu(KD_Tree<Coche>& arbol_coches, KD_Tree<Propietario>& arbol_propietarios, KD_Tree<Celda>& arbol_celdas, int size) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    bool running = true;
    string archivo, comando;
    while (running) {  
        options.clear(); 
        addOption("Insertar Coche ");
        addOption("Mostrar Lista de Coches");
        addOption("Busqueda de Coche Por Placa");
        addOption("Busqueda Avanzada");
        addOption("Menu de Gestion de Propietarios");
        addOption("Liberar el parqueadero");
        addOption("Ordenar lista de coches");
        addOption("Imprimir estado del parqueadero");
        addOption("Ayuda");
        addOption("Salir");

        addTitle("\t Menu Principal");

        displayMenu();
        float x, y,a,b;
        Coche coche;
        Celda celda;
        Celda *celda_encontrada;
        Validaciones validaciones;
        string cedula_propietario;
        Propietario* propietarioEncontrado;
        Coche* coche_encontrado;
        string placa_registrada, depurador;
        int seleccionador, sel;
        bool confirmador;
        switch (getSelectedOption()) {
            case 0:
            cout << "Opción seleccionada: Insertar Coche\n";
            seleccionador = menuTipoAuto();
            if (seleccionador == 0) {
            placa_registrada = validaciones.ingresarPlaca("Ingrese la placa del coche: ");
            } else if (seleccionador == 1) {
            placa_registrada = validaciones.ingresarPlacaMoto("Ingrese la placa de la moto: ");
            } else {
            cout << "Volviendo al menú principal...\n";
            break;
            }
            propietarioEncontrado = arbol_propietarios.buscarPorPlaca(placa_registrada);
            celda_encontrada = arbol_celdas.buscarPorPlacaEnCelda(placa_registrada);
            if (propietarioEncontrado != nullptr) {
                cout << "Placa encontrada\n";
                std::chrono::system_clock::time_point fecha_improbable=definirFechaImprobable();
                if (celda_encontrada != nullptr && celda_encontrada->getHoraSalida() == fecha_improbable) {
                    cout << "El coche todavía no ha salido. Volviendo al menú principal.\n";
                    system("pause");
                    break;  
                } else {
                    coche_encontrado = arbol_coches.buscarPorPlacaEnCoches(placa_registrada);
                    a= celda.ingresar_coordenada(size, 0);
                    b= celda.ingresar_coordenada(size, 1);
                    confirmador=arbol_celdas.buscar_coordenadas_en_parqueadero(a,b);
                    if(confirmador){
                        celda.ingresar_al_parqueadero(*coche_encontrado, size,a,b);
                        arbol_celdas.insert(celda, a, b);
                        cout << "El coche ha ingresado al parqueadero.\n";
                    }else{
                        cout<<"La celda ya esta ocupada"<<endl;
                    }
                }
            } else {
                // No se encontró la placa, buscar por cédula
                cedula_propietario = validaciones.ingresarCedula("Ingrese la cédula del propietario: ");
                propietarioEncontrado = arbol_propietarios.buscarPorCedula(cedula_propietario);

                if (propietarioEncontrado != nullptr) {
                    cout << "Propietario encontrado. Procediendo a registrar un nuevo coche.\n";
                    coche.ingresar_coche_nuevo(seleccionador);
                    propietarioEncontrado->agregarPlaca(coche.getPlaca());
                    propietarioEncontrado->guardar_en_archivo();
                    coche.guardarEnArchivo();
                    
                    // Convertir placa y marca a coordenadas para el árbol KD
                    x = arbol_coches.convertirStringAFloat(coche.getPlaca());
                    y = arbol_coches.convertirStringAFloat(coche.getMarca());
                    arbol_coches.insert(coche, x, y);
                    // Registrar celda
                    a= celda.ingresar_coordenada(size, 0);
                    b= celda.ingresar_coordenada(size, 1);
                    confirmador=arbol_celdas.buscar_coordenadas_en_parqueadero(a,b);
                    if(confirmador){
                        celda.ingresar_al_parqueadero(coche,size,a,b);
                        arbol_celdas.insert(celda, a, b);
                        cout << "Nuevo coche registrado e ingresado al parqueadero.\n";
                    }else{
                        cout<<"La celda ya esta ocupada"<<endl;
                    }
                } else {
                    cout << "Propietario no encontrado. Volviendo al menú principal.\n";
                }
            }
            system("pause");
            break;

            case 1:
                menu_mostrar_lista(arbol_celdas);
                system("pause");
                break;
            case 2:
                menu_buscar_por_placa(arbol_celdas);
                system("pause");
                break;
            case 3:
                menu_busqueda_avanzada(arbol_celdas, arbol_coches);
                system("pause");
                break;
            case 4:
                menu_gestion_propietarios( arbol_propietarios);
                system("pause");
                break;
            case 5:
                cout << "Opción seleccionada: Liberar el parqueadero\n";
                sel=menuTipoAuto();
                if (sel == 0) {
                placa_registrada = validaciones.ingresarPlaca("Ingrese la placa del coche: ");
                } else if (sel == 1) {
                placa_registrada = validaciones.ingresarPlacaMoto("Ingrese la placa de la moto: ");
                } else {
                cout << "Volviendo al menú principal...\n";
                break;
                }
                celda_encontrada = arbol_celdas.buscarPorPlacaEnCelda(placa_registrada);
                if(celda_encontrada != nullptr){
                    celda_encontrada = arbol_celdas.buscarPorPlacaYFechaImprobable(placa_registrada);
                    celda_encontrada->retirar_del_parqueadero();
                    cout << "Coche retirado del parqueadero.\n";
                    system("pause");
                }else{  
                    cout << "Automóvil no encontrado en el parqueadero.\n";
                    system("pause");
                }
                break;
            case 6:
                menu_ordenamientos(arbol_coches);
                system("pause");
                break;
            case 7:
                arbol_celdas.imprimir_parqueadero(size);
                break;
            case 8:
                cout << "Opción seleccionada: Ayuda\n";
                archivo = "resources/ayuda.html";
                comando = "start " + archivo;
                system(comando.c_str());
                system("pause");
                break;
            case 9: 
                cout << "Opción seleccionada: Salir\n";
                running = false; 
                break;
        }
    }
}
void Menu::menu_mostrar_lista(KD_Tree<Celda>& arbol_celdas) {
    bool running = true;
    
    while (running) {
        options.clear(); // Limpiar opciones anteriores
        addOption("Mostrar coches en parqueadero");
        addOption("Mostrar historial completo de coches");
        addOption("Volver al Menu Principal");

        addTitle("\t Menu de Mostrar Lista");

        displayMenu();

        switch (getSelectedOption()) {
            case 0:
                cout << "Opción seleccionada: Mostrar Lista de Coches en el parqueadero\n";
                arbol_celdas.imprimirCeldas();
                system("pause");
                break;
            case 1:
                cout << "Opción seleccionada: Mostrar Historial completo\n";
                arbol_celdas.imprimirNodos();
                system("pause");
                break;
            case 2:
                cout << "Opción seleccionada: Volver al Menu Principal\n";
                running = false;  // Terminar el bucle y volver al menú principal
                break;
        }
    }
}
void Menu::menu_buscar_por_placa(KD_Tree<Celda>& arbol_celdas) {
    bool running = true;
    int sel;
    Validaciones validaciones;
    string placa_buscada;
    while (running) {
    options.clear(); // Limpiar opciones anteriores
    addOption("Buscar en el parqueadero");
    addOption("Buscar en el historial de coches");
    addOption("Volver al Menu Principal");

    addTitle("\t Menu de Busqueda por Placa");

    displayMenu();

    switch (getSelectedOption()) {
        case 0:
            cout << "Opción seleccionada: Buscar en el parqueadero\n";
            sel=menuTipoAuto();
            if (sel == 0) {
            placa_buscada = validaciones.ingresarPlaca("Ingrese la placa del coche: ");
            } else if (sel == 1) {
            placa_buscada = validaciones.ingresarPlacaMoto("Ingrese la placa de la moto: ");
            } else {
            cout << "Volviendo al menú principal...\n";
            break;
            }
            arbol_celdas.buscarPorFechaImprobable(placa_buscada);

            system("pause");
            break;
        case 1:
            cout << "Opción seleccionada: Buscar en el historial de coches\n";
            sel=menuTipoAuto();
            if (sel == 0) {
            placa_buscada = validaciones.ingresarPlaca("Ingrese la placa del coche: ");
            } else if (sel == 1) {
            placa_buscada = validaciones.ingresarPlacaMoto("Ingrese la placa de la moto: ");
            } else {
            cout << "Volviendo al menú principal...\n";
            break;
            }
            arbol_celdas.buscarPorPlacaEnCelda(placa_buscada);
            system("pause");
            break;
        case 2:
            cout << "Opción seleccionada: Volver al Menu Principal\n";
            running = false;
            break;}
    }
}   
void Menu::menu_busqueda_avanzada(KD_Tree<Celda>& arbol_celdas, KD_Tree<Coche>& arbol_coches) {
    bool running = true;
    int opcion;
    Validaciones validaciones;
    string fecha_inicio, fecha_fin, hora_inicio, hora_fin, modelo, color, marca;
    while (running) {
    options.clear(); // Limpiar opciones anteriores
    addOption("Buscar en el parqueadero");
    addOption("Buscar en el historial de coches");
    addOption("Volver al Menu Principal");

    addTitle("\tBusqueda Avanzada");

    displayMenu();

    switch (getSelectedOption()) {
    case 0:
        opcion = menu_busqueda_avanzada_opciones(arbol_celdas, arbol_coches);
        switch (opcion) {
            case 0:
                cout << "Opción seleccionada: Buscar por Modelo\n";
                modelo = validaciones.ingresarString("Ingrese el modelo del coche a buscar: ");
                arbol_celdas.buscar_por_modelo_parqueadero(modelo);
                system("pause");
                break;
            case 1:
                cout << "Opción seleccionada: Buscar por Color\n";
                color = validaciones.ingresarString("Ingrese el color del coche a buscar: ");
                arbol_celdas.buscar_por_color_parqueadero(color);
                system("pause");
                break;
            case 2:
                cout << "Opción seleccionada: Buscar por Fecha\n";
                fecha_inicio = validaciones.ingresarFecha("Ingrese la fecha de inicio (dd/mm/aaaa): ");
                fecha_fin = validaciones.ingresarFecha("Ingrese la fecha de fin (dd/mm/aaaa): ");
                arbol_celdas.buscar_por_fecha_parqueadero(fecha_inicio, fecha_fin);
                system("pause");
                break;
            case 3:
                cout << "Opción seleccionada: Buscar por Marca\n";
                marca = validaciones.ingresarString("Ingrese la marca del coche a buscar: ");
                arbol_celdas.buscar_por_marca_parqueadero(marca);
                system("pause");
                break;
            case 4:
                cout << "Opción seleccionada: Buscar por Hora\n";
                hora_inicio = validaciones.ingresarHora("Ingrese la hora de inicio (hh:mm:ss): ");
                hora_fin = validaciones.ingresarHora("Ingrese la hora de fin (hh:mm:ss): ");
                arbol_celdas.buscar_por_hora_parqueadero(hora_inicio, hora_fin);
                system("pause");
                break;
            default:
                break;
        }
        break;
    case 1:
        opcion = menu_busqueda_avanzada_opciones(arbol_celdas, arbol_coches);
        switch (opcion) {
            case 0:
                cout << "Opción seleccionada: Buscar por Modelo en Historial\n";
                modelo = validaciones.ingresarString("Ingrese el modelo del coche a buscar: ");
                arbol_celdas.buscarPorModelo(modelo);
                system("pause");
                break;
            case 1:
                cout << "Opción seleccionada: Buscar por Color en Historial\n";
                color = validaciones.ingresarString("Ingrese el color del coche a buscar: ");
                arbol_celdas.buscarPorColor(color);
                system("pause");
                break;
            case 2:
                cout << "Opción seleccionada: Buscar por Fecha en Historial\n";
                fecha_inicio = validaciones.ingresarFecha("Ingrese la fecha de inicio (dd/mm/aaaa): ");
                fecha_fin = validaciones.ingresarFecha("Ingrese la fecha de fin (dd/mm/aaaa): ");
                arbol_celdas.buscarPorFecha(fecha_inicio, fecha_fin);
                system("pause");
                break;
            case 3:
                cout << "Opción seleccionada: Buscar por Marca en Historial\n";
                marca = validaciones.ingresarString("Ingrese la marca del coche a buscar: ");
                arbol_celdas.buscarPorMarca(marca);
                system("pause");
                break;
            case 4:
                cout << "Opción seleccionada: Buscar por Hora en Historial\n";
                hora_inicio = validaciones.ingresarHora("Ingrese la hora de inicio (hh:mm:ss): ");
                hora_fin = validaciones.ingresarHora("Ingrese la hora de fin (hh:mm:ss): ");
                arbol_celdas.buscarPorHora(hora_inicio, hora_fin);
                system("pause");
                break;
            default:
                break;
        }
        break;
    case 2:
        cout << "Opción seleccionada: Volver al Menu Principal\n";
        running = false;
        break;
    default:
        break;
        }
    }
}
int Menu::menu_busqueda_avanzada_opciones(KD_Tree<Celda>& arbol_celdas, KD_Tree<Coche>& arbol_coches) {
    bool running = true;
    while (running) {
        options.clear(); // Limpiar opciones anteriores
        addOption("Buscar por Modelo");
        addOption("Buscar por Color");
        addOption("Buscar por Fecha");
        addOption("Buscar por Marca");
        addOption("Buscar por Hora");
        addOption("Volver al Menu Principal");

        addTitle("\t Menu de Busqueda Avanzada");

        displayMenu();

        if (getSelectedOption() == 5) {
            cout << "Opción seleccionada: Volver al Menu Principal\n";
            running = false;
        }else
        {
            return getSelectedOption(); // Devolver la opción seleccionada
        }
    }

    return getSelectedOption(); // Devolver la opción seleccionada
}

void Menu::menu_gestion_propietarios(KD_Tree<Propietario>& arbol_propietarios) {
    bool running = true;
    while (running) {
    options.clear(); // Limpiar opciones anteriores
    addOption("Agregar Propietario");
    addOption("Mostrar Propietarios");
    addOption("Buscar Propietario por Cedula");
    addOption("Eliminar Placa de Propietario");
    addOption("Volver al Menu Principal");

    addTitle("\t Menu de Gestion de Propietarios");

    displayMenu();
    Propietario propietario;
    Validaciones validaciones;
    string cedula_buscada, placa_a_eliminar;
    float x, y;
    int sel;
    switch (getSelectedOption()) {
        case 0:
            cout << "Opción seleccionada: Agregar Propietario\n";
            propietario.ingresar_propietario();
            x= arbol_propietarios.convertirStringAFloat(propietario.getNombre());
            y= arbol_propietarios.convertirStringAFloat(propietario.getApellido());
            arbol_propietarios.insert(propietario, x, y);
            propietario.guardar_en_archivo();
            system("pause");
            break;
        case 1:
            cout << "Opción seleccionada: Mostrar Propietarios\n";
            arbol_propietarios.imprimir_propietarios();
            system("pause");
            break;
        case 2:
            cout << "Opción seleccionada: Buscar Propietario por Cedula\n";
            cedula_buscada = validaciones.ingresarCedula("Ingrese la cedula del propietario a buscar: ");
            if(!arbol_propietarios.buscarPorCedula(cedula_buscada)){
                cout << "Propietario no encontrado\n";
                }
            system("pause");
            break;
        case 3:
            cout << "Opción seleccionada: Eliminar Placa de Propietario\n";
            cedula_buscada = validaciones.ingresarCedula("Ingrese la cedula del propietario: ");
            sel=menuTipoAuto();
            if (sel == 0) {
            placa_a_eliminar = validaciones.ingresarPlaca("Ingrese la placa a eliminar: ");
            } else if (sel == 1) {
            placa_a_eliminar = validaciones.ingresarPlacaMoto("Ingrese la placa a eliminar: ");
            } else {
            cout << "Volviendo al menú principal...\n";
            break;
            }
            arbol_propietarios.eliminarPlacaPorCedula(cedula_buscada, placa_a_eliminar);
            system("pause");
            break;
        case 4:
            cout << "Opción seleccionada: Volver al Menu Principal\n";
            running = false;
            break;
    }
    }
}
void Menu::menu_ordenamientos(KD_Tree<Coche>& arbol_coches) {
    bool running = true;
    int opcion;
    Ordenamientos ordenamientos;
    while (running) {
        options.clear(); // Limpiar opciones anteriores
        addOption("Quick Sort");
        addOption("Bucket Sort");
        addOption("Bubble Sort");
        addOption("Shell Sort");
        addOption("Radix sort");
        addOption("Heap Sort");
        addOption("Volver al Menu Principal");

        addTitle("\t Menu de Ordenamientos");

        displayMenu();

        switch (getSelectedOption()) {
            case 0: { // Quick Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Quick Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Quick Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Quick Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Quick Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Quick Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 1: { // Bucket Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Bucket Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Bucket Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Bucket Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Bucket Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Bucket Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 2: { // Bubble Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Bubble Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Bubble Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Bubble Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);    
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Bubble Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);    
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Bubble Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 3: { // Shell Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Shell Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Shell Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Shell Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Shell Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Shell Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 4: { // Radix Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Radix Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Radix Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Radix Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Radix Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Radix Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 5: { // Heap Sort
                opcion = menu_ordenamientos_opciones(arbol_coches);
                switch (opcion) {
                    case 0: {
                        cout << "Opción seleccionada: ordenar por Placa en Heap Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 0);
                        system("pause");
                        break;
                    }
                    case 1: {
                        cout << "Opción seleccionada: ordenar por Apellido del Propietario en Heap Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 4);
                        system("pause");
                        break;
                    }
                    case 2: {
                        cout << "Opción seleccionada: ordenar por Color en Heap Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 1);
                        system("pause");
                        break;
                    }
                    case 3: {
                        cout << "Opción seleccionada: ordenar por Modelo en Heap Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 3);
                        system("pause");
                        break;
                    }
                    case 4: {
                        cout << "Opción seleccionada: ordenar por Marca en Heap Sort\n";
                        ordenamientos.imprimirOrdenado(arbol_coches, 2);
                        system("pause");
                        break;
                    }
                    default: {
                        cout << "Opción seleccionada: Volver al Menu Principal\n";
                        system("pause");
                        break;
                    }
                }
                break;
            }
            case 6: { // Volver al Menu Principal
                cout << "Opción seleccionada: Volver al Menu Principal\n";
                running = false;
                system("pause");
                break;
            }
            default: {
                cout << "Opción no válida. Inténtalo nuevamente.\n";
                system("pause");
                break;
            }
        }
    }
}

int Menu::menu_ordenamientos_opciones(KD_Tree<Coche>& arbol_coches) {
    bool running = true;
    while (running) {
    options.clear(); // Limpiar opciones anteriores
    addOption("Ordenar por Placa");
    addOption("Ordenar por Apellido del Propietario");
    addOption("Ordenar por Color");
    addOption("Ordenar por Modelo");
    addOption("Ordenar por Marca");
    addOption("Volver al Menu Principal");

    addTitle("\t Menu de Ordenamientos");

    displayMenu();

    switch (getSelectedOption()) {
        case 0:
            cout << "Opción seleccionada: Ordenar por Placa\n";
            return 0;
            system("pause");
            break;
        case 1:
            cout << "Opción seleccionada: Ordenar por Apellido del Propietario\n";
            return 1;
            system("pause");
            break;
        case 2:
            cout << "Opción seleccionada: Ordenar por Color\n";
            return 2;
            system("pause");
            break;
        case 3:
            cout << "Opción seleccionada: Ordenar por Modelo\n";
            return 3;
            system("pause");
            break;
        case 4:
            cout << "Opción seleccionada: Ordenar por Marca\n";
            return 4;
            system("pause");
            break;
        case 5:
            cout << "Opción seleccionada: Volver al Menu Principal\n";
            running = false;
            break;
        }
    }
    return getSelectedOption();
}

int Menu::menuTipoAuto(){
    bool running = true;
    while (running) {
    options.clear(); // Limpiar opciones anteriores
    addOption("Coche");
    addOption("Moto");
    addOption("Volver al Menu Principal");
    addTitle("Seleccione el tipo de vehiculo:");
    displayMenu();
    switch (getSelectedOption()) {
        case 0:
            cout << "Tipo de auto seleccionado: Coche\n";
            return 0;
            system("pause");
            break;
        case 1:
            cout << "Tipo de auto seleccionado: Moto\n";
            return 1;
            system("pause");
            break;
        case 2:
            cout << "Opción seleccionada: Volver al Menu Principal\n";
            running = false;
            break;
        }
    }
    return getSelectedOption();
}