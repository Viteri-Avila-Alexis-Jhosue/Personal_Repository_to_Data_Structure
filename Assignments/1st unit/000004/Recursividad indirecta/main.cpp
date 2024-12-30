#include <iostream>
using namespace std;

void functionB(int n);

void functionA(int n) {
    if (n > 0) {
        cout << "A: " << n << endl;
        functionB(n - 1);
    }
}

void functionB(int n) {
    if (n > 1) {
        cout << "B: " << n << endl;
        functionA(n / 2);
    }
}

int main() {
    functionA(10);
    return 0;
}
