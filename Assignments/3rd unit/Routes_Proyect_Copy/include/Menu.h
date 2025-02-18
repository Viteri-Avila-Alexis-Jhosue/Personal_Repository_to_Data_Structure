#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include "KD_Tree.h"
#include "Ubication.h"
#include "Route.h"
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
    void principal_menu(int size,KD_Tree<Ubication>& ubication_tree,KD_Tree<Route>& routes_tree);
    int auxiliar_menu();
    int distance_menu();
    int level_menu();
    void routeCh_menu(int size,KD_Tree<Ubication>& ubication_tree,KD_Tree<Route>& routes_tree);
    void delete_route(KD_Tree<Route>& routes_tree);
    int enlarge_route();
    void print_routes(KD_Tree<Route>& routes_tree);
};

#endif // MENU_H
