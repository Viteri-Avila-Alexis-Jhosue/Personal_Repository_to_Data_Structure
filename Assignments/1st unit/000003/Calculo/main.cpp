#include <iostream>
#include <cstdio>
#include "Calculo.cpp"
using namespace std;

int main() {
    float a, b;
    printf("Calculadora para numeros mayores a cero\n\n");
    do {
        printf("Ingrese un numero a: ");
        scanf("%f", &a);
        printf("Ingrese un numero b: ");
        scanf("%f", &b);
        if (a <= 0 || b <= 0) {
            printf("El numero ingresado no es valido. Ingrese un numero mayor a cero\n\n");
        }
    } while (a <= 0 || b <= 0);

    Calculo<float> calculo;
    calculo.setA(a);
    calculo.setB(b);

    float resultadoSuma = calculo.sumar();
    float resultadoResta = calculo.restar();
    float resultadoMultiplicacion = calculo.multiplicar();

    printf("La suma es: %f\n", resultadoSuma);
    printf("La resta es: %f\n", resultadoResta);
    printf("La multiplicacion es: %f\n", resultadoMultiplicacion);

    return 0;
}
