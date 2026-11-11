#include "Board.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>

using namespace std;

Board::Board(int size, int winLength)
    : n(size), k(winLength), filled(0), cells(size, vector<char>(size, '.'))
{
}

bool Board::inside(int row, int col) const
{
    return row >= 0 && row < n && col >= 0 && col < n;
}

bool Board::isFree(int row, int col) const
{
    return inside(row, col) && cells[row][col] == '.';
}

bool Board::isFull() const
{
    return filled == n * n;
}

vector<Move> Board::freeCells() const
{
    vector<Move> result;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (cells[r][c] == '.') {
                result.push_back({r, c});
            }
        }
    }
    return result;
}

void Board::put(Move move, char symbol)
{
    if (!isFree(move.row, move.col)) {
        throw logic_error("сопрограма зробила некоректний хід");
    }
    cells[move.row][move.col] = symbol;
    filled++;
}

int Board::countLine(Move from, int dr, int dc, char symbol) const
{
    int count = 0;
    int r = from.row + dr;
    int c = from.col + dc;
    while (inside(r, c) && cells[r][c] == symbol) {
        count++;
        r += dr;
        c += dc;
    }
    return count;
}

bool Board::isWinning(Move move, char symbol) const
{
    const int dr[4] = {0, 1, 1, 1};
    const int dc[4] = {1, 0, 1, -1};
    for (int d = 0; d < 4; d++) {
        int count = 1 + countLine(move, dr[d], dc[d], symbol) + countLine(move, -dr[d], -dc[d], symbol);
        if (count >= k) {
            return true;
        }
    }
    return false;
}

void Board::print() const
{
    cout << "   ";
    for (int c = 0; c < n; c++) {
        cout << setw(3) << c + 1;
    }
    cout << "\n";
    for (int r = 0; r < n; r++) {
        cout << setw(3) << r + 1;
        for (int c = 0; c < n; c++) {
            cout << setw(3) << cells[r][c];
        }
        cout << "\n";
    }
    cout << "\n";
}
