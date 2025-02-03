#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include "../include/KD_Tree.h"
#include "../include/Nodo.h"
#include "../include/Coche.h"
#include "../include/Propietario.h"
#include "../include/Celda.h"
using namespace std;
class Menu {
private:
    vector<string> options;
    int selectedIndex;
    string title;
public:
    Menu();
    void addOption(const string& option);
    void displayMenu();
    int getSelectedOption();
    void addTitle(const string& title);
    void principal_menu(KD_Tree<Coche>& arbol_coches, KD_Tree<Propietario>& arbol_propietarios, KD_Tree<Celda>& arbol_celdas, int size,KD_Tree<Celda>& arbol_experimental);
    void menu_mostrar_lista(KD_Tree<Celda>& arbol_celdas);
    void menu_buscar_por_placa(KD_Tree<Celda>& arbol_celdas);
    void menu_busqueda_avanzada(KD_Tree<Celda>& arbol_celdas, KD_Tree<Coche>& arbol_coches);
    int menu_busqueda_avanzada_opciones(KD_Tree<Celda>& arbol_celdas, KD_Tree<Coche>& arbol_coches);
    void menu_gestion_propietarios(KD_Tree<Propietario>& arbol_propietarios);
    void menu_ordenamientos(KD_Tree<Coche>& arbol_coches);
    int menu_ordenamientos_opciones(KD_Tree<Coche>& arbol_coches);
    int menuTipoAuto();
    int menu_seleccion_objetivo();
    int menu_datos_arbol();
};

#endif // MENU_H
