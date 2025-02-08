#include <iostream>
#include <string>
#include "../include/User.h"
#include "../include/Validation.h"
#include "../include/Tree.h"
#include "../include/Menu.h"
using namespace std;

int main()
{
    Menu menu;
    Tree<User> tree;
    tree.load_from_file("output//Users.txt");
    system("pause");
    menu.principal_menu(tree);
    tree.~Tree();
    return 0;
}
