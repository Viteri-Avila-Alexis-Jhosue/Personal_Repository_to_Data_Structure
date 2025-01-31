#include <iostream>
#include "../include/Menu.h"
#include "../include/KD_Tree.h"
#include "../include/Coche.h"
#include "../include/Propietario.h"
#include "../include/Celda.h"

int main() {
    Menu menu;
    int size=16;
    KD_Tree<Coche> arbol_coches;
    KD_Tree<Propietario> arbol_propietarios;
    KD_Tree<Celda> arbol_celdas;
    arbol_celdas.loadAutosHistorial("output//autos_historial.txt");
    arbol_propietarios.loadPropietarios("output//propietarios.txt");
    arbol_coches.loadAutos("output//autos.txt");
    system("pause");
    menu.principal_menu(arbol_coches, arbol_propietarios, arbol_celdas,size);
    arbol_celdas.~KD_Tree();
    arbol_propietarios.~KD_Tree();
    arbol_coches.~KD_Tree();
    return 0;
}