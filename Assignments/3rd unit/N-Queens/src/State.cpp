#include "../include/State.h"
#include <iostream>

State::State(int n) : n(n) {}

void State::placeQueen(int row, int col) {
    queens.emplace_back(row, col);
}

void State::removeQueen() {
    queens.pop_back();
}

bool State::isSafe(int row, int col) const {
    Queen newQueen(row, col);
    for (const Queen& queen : queens) {
        if (queen.isConflict(newQueen)) {
            return false;
        }
    }
    return true;
}

void State::print() const {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            bool isQueen = false;
            for (const Queen& queen : queens) {
                if (queen.getRow() == i && queen.getCol() == j) {
                    isQueen = true;
                    break;
                }
            }
            std::cout << (isQueen ? "Q " : ". ");
        }
        std::cout << std::endl;
    }
}

int State::getN() const {
    return n;
}

const std::vector<Queen>& State::getQueens() const {
    return queens;
}