#pragma once
#include <iostream>

class Matriz {
private:
    int **matriz;
    int dim;

public:
    Matriz(int);
    ~Matriz();
    int getDim() const;
    int** getMatriz();
    void setMatriz(int**);
};
