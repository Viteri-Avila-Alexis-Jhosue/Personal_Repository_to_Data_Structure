#include <iostream>
#include "Matriz.h"
#include "Operaciones.h"

int ingresar(char *msj) {
    int dim;
    printf("\n%s\n", msj);
    scanf("%d", &dim);
    return dim;
}

void iniciar(int dim) {
    int pot;
    Matriz m1(dim), m2(dim), mr(dim); 
    Operaciones operaciones;

    operaciones.generar(m1.getMatriz(), dim);
    operaciones.generar(m2.getMatriz(), dim);

    printf("\nMatriz 1\n");
    operaciones.imprimir(m1.getMatriz(), dim);

    printf("\nMatriz 2\n");
    operaciones.imprimir(m2.getMatriz(), dim);

    pot = ingresar("Ingrese la potencia de la matriz");

    Matriz m1Copia(dim);
    operaciones.copiarMatriz(m1.getMatriz(), m1Copia.getMatriz(), dim);
    
    operaciones.procesarPot(m1Copia.getMatriz(), dim, pot);
    printf("\nMatriz R (Potencia)\n");
    operaciones.imprimir(m1Copia.getMatriz(), dim);

    operaciones.procesarMulti(m1.getMatriz(), m2.getMatriz(), mr.getMatriz(), dim);
    printf("\nMatriz Multiplicacion\n");
    operaciones.imprimir(mr.getMatriz(), dim);

    operaciones.sumar(m1.getMatriz(), m2.getMatriz(), mr.getMatriz(), dim);
    printf("\nMatriz Suma\n");
    operaciones.imprimir(mr.getMatriz(), dim);
}

int main(int argc, char** argv) {
    int dim = ingresar("Ingrese la dimension de la matriz");
    iniciar(dim);
    return 0;
}
