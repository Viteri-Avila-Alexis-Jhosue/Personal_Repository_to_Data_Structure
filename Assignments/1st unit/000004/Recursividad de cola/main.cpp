#include <iostream>
using namespace std;

int sumTail(int n, int acumulado = 0) {
    if (n == 0)
        return acumulado;
    return sumTail(n - 1, acumulado + n);
}

int main() {
    int n = 5;
    cout << "Suma de los primeros " << n << " numeros es " << sumTail(n) << endl;
    return 0;
}
