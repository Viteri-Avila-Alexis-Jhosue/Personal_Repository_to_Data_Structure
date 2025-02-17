#include <iostream>
#include "../include/Triangle.h"
#include "../include/Validation.h"
using namespace std;
int main() {
    int initialNumber, increment;
    Validation validation;
    initialNumber=validation.ingresarInt("Introduce un numero entero inicial: ");
    cout <<endl;
    increment=validation.ingresarInt("Introduce el incremento: ");
    cout <<endl;
    Triangle triangle(initialNumber, increment);
    triangle.generateNumbers();
    triangle.solveMagicTriangle();
    triangle.displayTriangle();

    return 0;
}