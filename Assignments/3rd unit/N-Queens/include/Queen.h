#ifndef QUEEN_H
#define QUEEN_H

class Queen
{
public:
    Queen(int row, int col);
    int getRow() const;
    int getCol() const;
    bool isConflict(const Queen &other) const;

private:
    int row;
    int col;
};

#endif