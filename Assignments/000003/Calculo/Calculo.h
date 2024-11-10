#ifndef CALCULO_H
#define CALCULO_H

#include <iostream>
using namespace std;

template <typename T>
class Calculo {
public:

    Calculo(T a = 0, T b = 0);

    void setA(T a);
    void setB(T b);
    T getA() ;
    T getB() ;

    T sumar();
    T restar();
    T multiplicar();

private:
    T a;
    T b;
};

#endif
