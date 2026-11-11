#include "Player.h"

using namespace std;

static bool findWinningCell(const Board& board, char symbol, Move& result)
{
    for (Move move : board.freeCells()) {
        if (board.isWinning(move, symbol)) {
            result = move;
            return true;
        }
    }
    return false;
}

Move chooseMove(const Board& board, char me, char enemy, mt19937& rng)
{
    Move move;
    if (findWinningCell(board, me, move)) {
        return move;
    }
    if (findWinningCell(board, enemy, move)) {
        return move;
    }
    vector<Move> cells = board.freeCells();
    uniform_int_distribution<int> dist(0, (int)cells.size() - 1);
    return cells[dist(rng)];
}

MoveGenerator player(const Board& board, char me, char enemy, mt19937& rng)
{
    while (!board.isFull()) {
        co_yield chooseMove(board, me, enemy, rng);
    }
}
