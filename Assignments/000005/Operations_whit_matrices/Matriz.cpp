#include "Matriz.h"
#include <cstdlib>

Matriz::Matriz(int dim) : dim(dim) {
    matriz = (int**)malloc(dim * sizeof(int*));
    for (int i = 0; i < dim; i++) {
        matriz[i] = (int*)malloc(dim * sizeof(int));
    }
}

Matriz::~Matriz() {
    for (int i = 0; i < dim; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int Matriz::getDim() const {
    return dim;
}

int** Matriz::getMatriz() {
    return matriz;
}

void Matriz::setMatriz(int **mat) {
    matriz = mat;
}
