#include <iostream>
#include "../include/Menu.h"
#include "../include/Coche.h"
#include "../include/ListaPropietarios.h"
#include "../include/Lista.h"

int main() {
ListaPropietarios listaPropietarios;
    listaPropietarios.cargarArchivo("output//propietarios.txt");
ListaCircularDoble<Coche> listaCochesHistorial;
    listaCochesHistorial.CargarArchivo("output//autos_historial.txt");

    ListaCircularDoble<Coche> listaCoches;
    listaCoches.CargarArchivo("output//autos.txt");

    menu(listaCoches, listaCochesHistorial, listaPropietarios);

    return 0;
}