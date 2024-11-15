#include "Operaciones.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Operaciones::Operaciones() {
    srand(static_cast<unsigned>(time(0)));
}

void Operaciones::segmentar(int**& matriz, int dim) {
    matriz = (int**)malloc(dim * sizeof(int*));
    for (int j = 0; j < dim; j++) {
        matriz[j] = (int*)malloc(dim * sizeof(int));
    }
}

void Operaciones::encerar(int** matriz, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = 0;
        }
    }
}

void Operaciones::imprimir(int** matriz, int dim) const {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void Operaciones::generar(int** matriz, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = rand() % 3;  
        }
    }
}

void Operaciones::procesarPot(int** matriz, int dim, int exp) {
    int** resultado = (int**)malloc(dim * sizeof(int*));
    int** temp = (int**)malloc(dim * sizeof(int*));

    for (int i = 0; i < dim; i++) {
        resultado[i] = (int*)malloc(dim * sizeof(int));
        temp[i] = (int*)malloc(dim * sizeof(int));
        for (int j = 0; j < dim; j++) {
            resultado[i][j] = (i == j) ? 1 : 0; 
            temp[i][j] = matriz[i][j];
        }
    }

    for (int e = 0; e < exp; e++) {
        int** intermedio = (int**)malloc(dim * sizeof(int*));
        for (int i = 0; i < dim; i++) {
            intermedio[i] = (int*)malloc(dim * sizeof(int));
            for (int j = 0; j < dim; j++) {
                intermedio[i][j] = 0;
                for (int k = 0; k < dim; k++) {
                    intermedio[i][j] += resultado[i][k] * temp[k][j];
                }
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                resultado[i][j] = intermedio[i][j];
            }
            free(intermedio[i]);
        }
        free(intermedio);
    }

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matriz[i][j] = resultado[i][j];
        }
        free(temp[i]);
        free(resultado[i]);
    }
    free(temp);
    free(resultado);
}

void Operaciones::procesarMulti(int **m1, int **m2, int **resultado, int dim) {
    encerar(resultado, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k = 0; k < dim; k++) {
                resultado[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

void Operaciones::sumar(int **m1, int **m2, int **resultado, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            resultado[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void Operaciones::copiarMatriz(int** origen, int** destino, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}
