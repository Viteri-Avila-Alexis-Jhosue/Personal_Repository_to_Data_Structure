#pragma once
#include "Matriz.h"

class Operaciones {
public:
    Operaciones();
    void segmentar(int**& matriz, int dim);
    void encerar(int** matriz, int dim);
    void imprimir(int** matriz, int dim) const;
    void generar(int** matriz, int dim);
    void procesarPot(int** matriz, int dim, int exp);
    void procesarMulti(int** m1, int** m2, int** resultado, int dim);
    void sumar(int** m1, int** m2, int** resultado, int dim);
    void copiarMatriz(int** origen, int** destino, int dim);
};
