#pragma once

#include <random>

#include "Board.h"
#include "MoveGenerator.h"

using namespace std;

Move chooseMove(const Board& board, char me, char enemy, mt19937& rng);

MoveGenerator player(const Board& board, char me, char enemy, mt19937& rng);
