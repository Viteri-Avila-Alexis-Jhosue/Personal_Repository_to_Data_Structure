#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Queen.h"

class State {
public:
    State(int n);
    void placeQueen(int row, int col);
    void removeQueen();
    bool isSafe(int row, int col) const;
    void print() const;
    int getN() const;
    const std::vector<Queen>& getQueens() const;

private:
    int n;
    std::vector<Queen> queens;
};

#endif // STATE_H