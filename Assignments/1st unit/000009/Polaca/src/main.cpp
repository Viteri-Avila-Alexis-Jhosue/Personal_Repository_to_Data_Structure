#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cctype>
#include "Menu.h"
using namespace std;

// Función para determinar la precedencia de un operador
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}
bool validarParentesis(const string& expr) {
    stack<char> pila;
    for (char c : expr) {
        if (c == '(') pila.push(c);
        else if (c == ')') {
            if (pila.empty()) return false;
            pila.pop();
        }
    }
    return pila.empty();
}

// Función para evaluar una operación
double evalOperacion(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Función para verificar si una expresión es válida
bool validarExpresion(const string& expr) {
    for (char c : expr) {
        if (!isdigit(c) && !isalpha(c) && string("+-*/^()").find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

// Convertir infijo a postfijo
string infijoAPostfijo(const string& expr) {
    stack<char> pila;
    string resultado;

    for (char c : expr) {
        if (isdigit(c) || isalpha(c)) { // Si es un operando
            resultado += c;
        } else if (c == '(') { // Si es un paréntesis izquierdo
            pila.push(c);
        } else if (c == ')') { // Si es un paréntesis derecho
            while (!pila.empty() && pila.top() != '(') {
                resultado += pila.top();
                pila.pop();
            }
            pila.pop(); // Quitar el '('
        } else { // Si es un operador
            while (!pila.empty() && precedencia(pila.top()) >= precedencia(c)) {
                resultado += pila.top();
                pila.pop();
            }
            pila.push(c);
        }
    }

    // Vaciar la pila
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }

    return resultado;
}

// Convertir infijo a prefijo
string infijoAPrefijo(const string& expr) {
    string invertida = expr;
    reverse(invertida.begin(), invertida.end()); // Invertir la expresión

    for (char& c : invertida) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    string postfija = infijoAPostfijo(invertida); // Usar la conversión a postfija
    reverse(postfija.begin(), postfija.end()); // Invertir nuevamente
    return postfija;
}

// Evaluar una expresión en notación postfija
double evaluarPostfija(const string& expr) {
    stack<double> pila;
    for (char c : expr) {
        if (isdigit(c)) { // Si es un número
            pila.push(c - '0'); // Convertir char a int
        } else { // Si es un operador
            double b = pila.top(); pila.pop();
            double a = pila.top(); pila.pop();
            pila.push(evalOperacion(a, b, c));
        }
    }
    return pila.top();
}

// Evaluar una expresión en notación prefija
double evaluarPrefija(const string& expr) {
    stack<double> pila;
    for (auto it = expr.rbegin(); it != expr.rend(); ++it) {
        char c = *it;
        if (isdigit(c)) { // Si es un número
            pila.push(c - '0'); // Convertir char a int
        } else { // Si es un operador
            double a = pila.top(); pila.pop();
            double b = pila.top(); pila.pop();
            pila.push(evalOperacion(a, b, c));
        }
    }
    return pila.top();
}

int main() {
    string expresion;
    int opcion;

    do {
        Menu menu;
        menu.addOption("1. Infijo");
        menu.addOption("2. Polaca");
        menu.addOption("3. Polaca inversa");
        menu.addOption("4. Salir");
        menu.displayMenu();
        opcion = menu.getSelectedOption() + 1;
        cin.ignore(); // Limpiar el buffer antes de usar getline

        if (opcion == 4) {
            cout << "Saliendo del programa...\n";
            break;
        }

        cout << "Ingrese la expresion: ";
        getline(cin, expresion);

        // Validar la expresión
        if (!validarExpresion(expresion)) {
            cout << "La expresion contiene caracteres invalidos o espacios.\n";
            cout << "Presione cualquier tecla para continuar...";
            cin.get();
            continue;
        }

        switch (opcion) {
            case 1: { // Infijo
                string postfija = infijoAPostfijo(expresion);
                string prefija = infijoAPrefijo(expresion);
                cout << "Polaca inversa: " << postfija << endl;
                cout << "Polaca: " << prefija << endl;
                cout << "Resultado: " << evaluarPostfija(postfija) << endl;
                break;
            }
            case 2: { // Prefijo
                double resultado = evaluarPrefija(expresion);
                cout << "Resultado: " << resultado << endl;
                break;
            }
            case 3: { // Postfijo
                double resultado = evaluarPostfija(expresion);
                cout << "Resultado: " << resultado << endl;
                break;
            }
            default:
                cout << "Opción inválida.\n";
        }

        // Pausar antes de regresar al menú
        cout << "\nPresione cualquier tecla para continuar...";
        cin.get();
    } while (opcion != 4);

    return 0;
}