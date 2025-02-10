#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include "KD_Tree.h"
#include "Ubication.h"
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
    void principal_menu(int size,KD_Tree<Ubication>& ubication_tree);
    int auxiliar_menu();
};

#endif // MENU_H
