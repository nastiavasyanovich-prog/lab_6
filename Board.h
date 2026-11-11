#pragma once

#include <vector>

using namespace std;

struct Move {
    int row;
    int col;
};

class Board {
public:
    Board(int size, int winLength);

    bool isFree(int row, int col) const;
    bool isFull() const;
    vector<Move> freeCells() const;
    void put(Move move, char symbol);
    bool isWinning(Move move, char symbol) const;
    void print() const;

private:
    int n;
    int k;
    int filled;
    vector<vector<char>> cells;

    bool inside(int row, int col) const;
    int countLine(Move from, int dr, int dc, char symbol) const;
};
