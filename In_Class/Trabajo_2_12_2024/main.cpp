#include <iostream>
#include <functional>

class MyClass {
private:
    int value;
    std::function<int(int, int)> addOperation;

public:
    MyClass(int v) : value(v) {
        // Lambda para restar valores
        addOperation = [](int a, int b) { return a - b; };
    }

    // Sobrecarga del operador +
    MyClass operator+(const MyClass& other) const {
        return MyClass(addOperation(this->value, other.value));
    }

    void print() const {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    int n, m;
    printf("Ingrese el primer numero:\n");
    scanf("%d", &n);  // Corregimos el formato
    printf("Ingrese el segundo numero:\n");
    scanf("%d", &m);  // Corregimos el formato

    MyClass a(n), b(m);
    MyClass c = a + b; // Llama al operador + sobrecargado

    c.print(); // Muestra el resultado de la operación

    return 0;
}
