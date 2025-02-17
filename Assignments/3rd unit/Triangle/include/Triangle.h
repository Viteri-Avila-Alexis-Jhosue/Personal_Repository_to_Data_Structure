#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Triangle {
public:
    Triangle(int initialNumber, int increment);
    void generateNumbers();
    void solveMagicTriangle();
    void displayTriangle() const;

private:
    int initialNumber;
    int increment;
    std::vector<int> numbers;
    std::vector<std::vector<int>> triangle;
    bool isMagicTriangle() const;
};

#endif // TRIANGLE_H