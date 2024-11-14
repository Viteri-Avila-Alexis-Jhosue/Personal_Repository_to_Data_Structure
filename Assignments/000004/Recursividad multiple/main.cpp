#include <iostream>
using namespace std;

int fibonacciTree(int n) {
    if (n <= 1)
        return n;
    return fibonacciTree(n - 1) + fibonacciTree(n - 2);  // Genera un árbol de llamadas
}

int main() {
    int n = 8;
    cout << "Fibonacci de " << n << " es " << fibonacciTree(n) << endl;
    return 0;
}
