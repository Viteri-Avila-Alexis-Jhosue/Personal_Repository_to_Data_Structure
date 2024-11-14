#include <iostream>
using namespace std;

bool isEven(int n);

bool isOdd(int n) {
    if (n == 0)
        return false;
    return isEven(n - 1);
}

bool isEven(int n) {
    if (n == 0)
        return true;
    return isOdd(n - 1);
}

int main() {
    int n = 5;
    if (isEven(n))
        cout << n << " es par" << endl;
    else
        cout << n << " es impar" << endl;
    return 0;
}
