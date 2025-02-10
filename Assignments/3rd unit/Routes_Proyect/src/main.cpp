# include "../include/Menu.h"
# include "../include/KD_Tree.h"
# include "../include/Ubication.h"
# include <iostream>

int main(){
    int size=101;
    Menu menu;
    KD_Tree<Ubication> ubication_tree;
    ubication_tree.load_ubicaciones("output//Ubicaciones.txt");
    system("pause");
    menu.principal_menu(size, ubication_tree);
    ubication_tree.~KD_Tree();
}