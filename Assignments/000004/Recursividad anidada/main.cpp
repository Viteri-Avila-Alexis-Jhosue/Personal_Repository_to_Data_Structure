#include <iostream>
using namespace std;

int sumaCuadrados(int n) {
    if (n <= 1)
        return 1;  // Caso base: si n es 1 o menos, retorna 1
    return n * n + sumaCuadrados(n - 1) + sumaCuadrados(n - 2);  // Llamadas anidadas
}

int main() {
    int n = 3;
    cout << "Suma de cuadrados desde " << n << " hasta 1 es: " << sumaCuadrados(n) << endl;
    return 0;
}

