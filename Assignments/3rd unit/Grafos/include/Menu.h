#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
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
};

#endif // MENU_H
