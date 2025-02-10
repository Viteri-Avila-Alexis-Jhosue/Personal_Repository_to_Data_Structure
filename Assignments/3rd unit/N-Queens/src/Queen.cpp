#include "../include/Queen.h"
#include <cmath> // Para usar la función abs

Queen::Queen(int row, int col) : row(row), col(col) {}

int Queen::getRow() const {
    return row;
}

int Queen::getCol() const {
    return col;
}

bool Queen::isConflict(const Queen& other) const {
    return row == other.row || col == other.col || abs(row - other.row) == abs(col - other.col);
}