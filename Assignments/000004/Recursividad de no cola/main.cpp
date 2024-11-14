#include <iostream>
using namespace std;

int power(int base, int exp) {
    if (exp == 0)
        return 1;
    int result = base * power(base, exp - 1);
    return result;  // Operación después de la llamada recursiva
}

int main() {
    int base = 2, exp = 3;
    cout << base << "^" << exp << " = " << power(base, exp) << endl;
    return 0;
}
