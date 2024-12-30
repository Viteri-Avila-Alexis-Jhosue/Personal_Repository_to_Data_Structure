#include "Calculo.h"

template <typename T>
Calculo<T>::Calculo(T a, T b) : a(a), b(b) {}

template <typename T>
void Calculo<T>::setA(T valorA) {
    a = valorA;
}
template <typename T>
void Calculo<T>::setB(T valorB) {
    b = valorB;
}

template <typename T>
T Calculo<T>::getA()  {
    return a;
}

template <typename T>
T Calculo<T>::getB()  {
    return b;
}

// Función para sumar
template <typename T>
T Calculo<T>::sumar() {
    return a + b;
}

template <typename T>
T Calculo<T>::restar() {
    return a - b;
}

template <typename T>
T Calculo<T>::multiplicar() {
    return a * b;
}
