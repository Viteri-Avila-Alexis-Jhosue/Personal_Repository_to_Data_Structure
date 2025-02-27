#include <iostream>
#include <map>
#include <functional>
#include <windows.h>
#include "../include/Ejercicios.h"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    int ejercicios_opcion, ejercicio_num;
    Ejercicios ejercicio;
    cout << "\t\tIngrese el numero de pagina del ejercicio:" << endl;
    cin >> ejercicios_opcion;
    // Mapeo de páginas y funciones correspondientes
    map<int, function<void()>> paginaFunciones = {
        {6, [&]() { ejercicio.ex_pag6(); }},
        {7, [&]() { ejercicio.ex_pag7(); }},
        {8, [&]() { ejercicio.ex_pag8(); }},
        {10, [&]() { ejercicio.ex_pag10(); }},
        {11, [&]() { ejercicio.ex_pag11(); }},
        {12, [&]() { ejercicio.ex_pag12(); }},
        {15, [&]() { ejercicio.ex_pag15(); }},
        {16, [&]() { ejercicio.ex_pag16(); }},
        {17, [&]() { ejercicio.ex_pag17(); }},
        {18, [&]() { ejercicio.ex_pag18(); }},
        {20, [&]() { ejercicio.ex_pag20(); }},
        {21, [&]() {
            cout << "Ingrese el número de ejercicio (2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 2) ejercicio.ex_pag21_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag21_3();
        }},
        {22, [&]() { ejercicio.ex_pag22(); }},
        {25, [&]() {
            cout << "Ingrese el número de ejercicio (1 o 2): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag25_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag25_2();
        }},
        {27, [&]() { ejercicio.ex_pag27(); }},
        {28, [&]() { ejercicio.ex_pag28(); }},
        {29, [&]() { ejercicio.ex_pag29(); }},
        {32, [&]() { ejercicio.ex_pag32(); }},
        {37, [&]() { ejercicio.ex_pag37(); }},
        {38, [&]() { ejercicio.ex_pag38(); }},
        {39, [&]() { ejercicio.ex_pag39(); }},
        {40, [&]() { ejercicio.ex_pag40(); }},
        {41, [&]() { ejercicio.ex_pag41(); }},
        {42, [&]() { ejercicio.ex_pag42(); }},
        {45, [&]() { ejercicio.ex_pag45(); }},
        {46, [&]() { ejercicio.ex_pag46(); }},
        {47, [&]() { ejercicio.ex_pag47(); }},
        {48, [&]() { ejercicio.ex_pag48(); }},
        {49, [&]() { ejercicio.ex_pag49(); }},
        {51, [&]() { ejercicio.ex_pag51(); }},
        {52, [&]() { ejercicio.ex_pag52(); }},
        {53, [&]() { ejercicio.ex_pag53(); }},
        {56, [&]() { ejercicio.ex_pag56(); }},
        {58, [&]() { ejercicio.ex_pag58(); }},
        {59, [&]() { ejercicio.ex_pag59(); }},
        {62, [&]() { ejercicio.ex_pag62(); }},
        {63, [&]() { ejercicio.ex_pag63(); }},
        {65, [&]() { ejercicio.ex_pag65(); }},
        {68, [&]() { ejercicio.ex_pag68(); }},
        {69, [&]() { ejercicio.ex_pag69(); }},
        {70, [&]() { ejercicio.ex_pag70(); }},
        {71, [&]() { ejercicio.ex_pag71(); }},
        {73, [&]() { ejercicio.ex_pag73(); }},
        {74, [&]() { ejercicio.ex_pag74(); }},
        {76, [&]() { ejercicio.ex_pag76(); }},
        {78, [&]() { ejercicio.ex_pag78(); }},
        {81, [&]() { ejercicio.ex_pag81(); }},
        {82, [&]() { ejercicio.ex_pag82(); }},
        {83, [&]() { ejercicio.ex_pag83(); }},
        {85, [&]() { ejercicio.ex_pag85(); }},
        {89, [&]() {
            cout << "Ingrese el número de ejercicio (1 o 2): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag89_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag89_2();
        }},
        {90, [&]() { ejercicio.ex_pag90(); }},
        {92, [&]() {
            cout << "Ingrese el número de ejercicio (1 o 2): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag92_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag92_2();
        }},
        {93, [&]() {
            cout << "Ingrese el número de ejercicio (3 o 4): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 3) ejercicio.ex_pag93_3();
            else if (ejercicio_num == 4) ejercicio.ex_pag93_4();
        }},
        {95, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag95_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag95_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag95_3();
        }},
        {97, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag97_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag97_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag97_3();
        }},
        {99, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2, 3 o 4): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag99_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag99_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag99_3();
            else if (ejercicio_num == 4) ejercicio.ex_pag99_4();
        }},
        {101, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag101_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag101_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag101_3();
        }},
        {103, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag103_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag103_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag103_3();
        }},
        {105, [&]() {
            cout << "Ingrese el número de ejercicio (1, 2 o 3): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag105_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag105_2();
            else if (ejercicio_num == 3) ejercicio.ex_pag105_3();
        }},
        {107, [&]() { ejercicio.ex_pag107(); }},
        {108, [&]() { ejercicio.ex_pag108(); }},
        {110, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 8): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag110_1(); break;
                case 2: ejercicio.ex_pag110_2(); break;
                case 3: ejercicio.ex_pag110_3(); break;
                case 4: ejercicio.ex_pag110_4(); break;
                case 5: ejercicio.ex_pag110_5(); break;
                case 6: ejercicio.ex_pag110_6(); break;
                case 7: ejercicio.ex_pag110_7(); break;
                case 8: ejercicio.ex_pag110_8(); break;
            }
        }},
        {111, [&]() {
            cout << "Ingrese el número de ejercicio (9 o 10): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 9) ejercicio.ex_pag111_9();
            else if (ejercicio_num == 10) ejercicio.ex_pag111_10();
        }},
        {112, [&]() {
            cout << "Ingrese el número de ejercicio (11 al 15): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 11: ejercicio.ex_pag112_11(); break;
                case 12: ejercicio.ex_pag112_12(); break;
                case 13: ejercicio.ex_pag112_13(); break;
                case 14: ejercicio.ex_pag112_14(); break;
                case 15: ejercicio.ex_pag112_15(); break;
            }
        }},
        {113, [&]() {
            cout << "Ingrese el número de ejercicio (16 al 18): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 16: ejercicio.ex_pag113_16(); break;
                case 17: ejercicio.ex_pag113_17(); break;
                case 18: ejercicio.ex_pag113_18(); break;
            }
        }},
        {114, [&]() { ejercicio.ex_pag114(); }},
        {115, [&]() { ejercicio.ex_pag115(); }},
        {116, [&]() { ejercicio.ex_pag116(); }},
        {117, [&]() { ejercicio.ex_pag117(); }},
        {118, [&]() { ejercicio.ex_pag118(); }},
        {120, [&]() {
            cout << "Ingrese el número de ejercicio (6 o 7): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 6) ejercicio.ex_pag120_6();
            else if (ejercicio_num == 7) ejercicio.ex_pag120_7();
        }},
        {121, [&]() { ejercicio.ex_pag121(); }},
        {123, [&]() { ejercicio.ex_pag123(); }},
        {125, [&]() { ejercicio.ex_pag125(); }},
        {127, [&]() { ejercicio.ex_pag127(); }},
        {129, [&]() { ejercicio.ex_pag129(); }},
        {132, [&]() { ejercicio.ex_pag132(); }},
        {136, [&]() { ejercicio.ex_pag136(); }},
        {138, [&]() { ejercicio.ex_pag138(); }},
        {139, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 7): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag139_1(); break;
                case 2: ejercicio.ex_pag139_2(); break;
                case 3: ejercicio.ex_pag139_3(); break;
                case 4: ejercicio.ex_pag139_4(); break;
                case 5: ejercicio.ex_pag139_5(); break;
                case 6: ejercicio.ex_pag139_6(); break;
                case 7: ejercicio.ex_pag139_7(); break;
            }
        }},
        {140, [&]() { ejercicio.ex_pag140(); }},
        {141, [&]() {
            cout << "Ingrese el número de ejercicio (9 al 12): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 9: ejercicio.ex_pag141_9(); break;
                case 10: ejercicio.ex_pag141_10(); break;
                case 11: ejercicio.ex_pag141_11(); break;
                case 12: ejercicio.ex_pag141_12(); break;
            }
        }},
        {142, [&]() {
            cout << "Ingrese el número de ejercicio (13 o 14): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 13) ejercicio.ex_pag142_13();
            else if (ejercicio_num == 14) ejercicio.ex_pag142_14();
        }},
        {143, [&]() {
            cout << "Ingrese el número de ejercicio (15 o 16): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 15) ejercicio.ex_pag143_15();
            else if (ejercicio_num == 16) ejercicio.ex_pag143_16();
        }},
        {144, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 4): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag144_1(); break;
                case 2: ejercicio.ex_pag144_2(); break;
                case 3: ejercicio.ex_pag144_3(); break;
                case 4: ejercicio.ex_pag144_4(); break;
            }
        }},
        {145, [&]() {
            cout << "Ingrese el número de ejercicio (5 al 12): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 5: ejercicio.ex_pag145_5(); break;
                case 6: ejercicio.ex_pag145_6(); break;
                case 7: ejercicio.ex_pag145_7(); break;
                case 8: ejercicio.ex_pag145_8(); break;
                case 9: ejercicio.ex_pag145_9(); break;
                case 10: ejercicio.ex_pag145_10(); break;
                case 11: ejercicio.ex_pag145_11(); break;
                case 12: ejercicio.ex_pag145_12(); break;
            }
        }},
        {146, [&]() {
            cout << "Ingrese el número de ejercicio (13 al 16): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 13: ejercicio.ex_pag146_13(); break;
                case 14: ejercicio.ex_pag146_14(); break;
                case 15: ejercicio.ex_pag146_15(); break;
                case 16: ejercicio.ex_pag146_16(); break;
            }
        }},
        {147, [&]() { ejercicio.ex_pag147(); }},
        {148, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 4): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag148_1(); break;
                case 2: ejercicio.ex_pag148_2(); break;
                case 3: ejercicio.ex_pag148_3(); break;
                case 4: ejercicio.ex_pag148_4(); break;
            }
        }},
        {149, [&]() {
            cout << "Ingrese el número de ejercicio (5 al 8): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 5: ejercicio.ex_pag149_5(); break;
                case 6: ejercicio.ex_pag149_6(); break;
                case 7: ejercicio.ex_pag149_7(); break;
                case 8: ejercicio.ex_pag149_8(); break;
            }
        }},
        {150, [&]() { ejercicio.ex_pag150(); }},
        {151, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 6): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag151_1(); break;
                case 2: ejercicio.ex_pag151_2(); break;
                case 3: ejercicio.ex_pag151_3(); break;
                case 4: ejercicio.ex_pag151_4(); break;
                case 5: ejercicio.ex_pag151_5(); break;
                case 6: ejercicio.ex_pag151_6(); break;
            }
        }},
        {152, [&]() {
            cout << "Ingrese el número de ejercicio (7 o 8): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 7) ejercicio.ex_pag152_7();
            else if (ejercicio_num == 8) ejercicio.ex_pag152_8();
        }},
        {153, [&]() {
            cout << "Ingrese el número de ejercicio (1 o 2): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag153_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag153_2();
        }},
        {154, [&]() {
            cout << "Ingrese el número de ejercicio (3 o 4): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 3) ejercicio.ex_pag154_3();
            else if (ejercicio_num == 4) ejercicio.ex_pag154_4();
        }},
        {155, [&]() {
            cout << "Ingrese el número de ejercicio (5 o 6): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 5) ejercicio.ex_pag155_5();
            else if (ejercicio_num == 6) ejercicio.ex_pag155_6();
        }},
        {156, [&]() {
            cout << "Ingrese el número de ejercicio (7 o 8): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 7) ejercicio.ex_pag156_7();
            else if (ejercicio_num == 8) ejercicio.ex_pag156_8();
        }},
        {157, [&]() {
            cout << "Ingrese el número de ejercicio (1 o 2): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 1) ejercicio.ex_pag157_1();
            else if (ejercicio_num == 2) ejercicio.ex_pag157_2();
        }},
        {158, [&]() {
            cout << "Ingrese el número de ejercicio (3 o 4): ";
            cin >> ejercicio_num;
            if (ejercicio_num == 3) ejercicio.ex_pag158_3();
            else if (ejercicio_num == 4) ejercicio.ex_pag158_4();
        }},
        {159, [&]() {
            cout << "Ingrese el número de ejercicio (5 al 9): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 5: ejercicio.ex_pag159_5(); break;
                case 6: ejercicio.ex_pag159_6(); break;
                case 7: ejercicio.ex_pag159_7(); break;
                case 8: ejercicio.ex_pag159_8(); break;
                case 9: ejercicio.ex_pag159_9(); break;
            }
        }},
        {160, [&]() {
            cout << "Ingrese el número de ejercicio (1 al 4): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 1: ejercicio.ex_pag160_1(); break;
                case 2: ejercicio.ex_pag160_2(); break;
                case 3: ejercicio.ex_pag160_3(); break;
                case 4: ejercicio.ex_pag160_4(); break;
            }
        }},
        {161, [&]() {
            cout << "Ingrese el número de ejercicio (5 al 8): ";
            cin >> ejercicio_num;
            switch (ejercicio_num) {
                case 5: ejercicio.ex_pag161_5(); break;
                case 6: ejercicio.ex_pag161_6(); break;
                case 7: ejercicio.ex_pag161_7(); break;
                case 8: ejercicio.ex_pag161_8(); break;
            }
        }},
    };

    // Verificar si la página existe en el mapeo
    if (paginaFunciones.find(ejercicios_opcion) != paginaFunciones.end()) {
        paginaFunciones[ejercicios_opcion](); // Llamar a la función correspondiente
    } else {
        cout << "Página no válida." << endl;
    }

    return 0;
}