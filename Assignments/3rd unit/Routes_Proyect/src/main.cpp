# include "../include/Menu.h"
# include "../include/KD_Tree.h"
# include "../include/Ubication.h"
# include "../include/Route.h"
# include <iostream>

int main(){
    int size=101;
    Menu menu;
    KD_Tree<Ubication> ubication_tree;
    KD_Tree<Route> routes_tree;
    ubication_tree.load_ubicaciones("output//Ubicaciones.txt");
    routes_tree.load_routes("output//Rutas.txt");
    system("pause");
    menu.principal_menu(size, ubication_tree, routes_tree);
    ubication_tree.~KD_Tree();
    routes_tree.~KD_Tree();
}