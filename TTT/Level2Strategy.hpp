#pragma once
#include "CPUStrategy.hpp"

class Level2Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    //  checks if a specific player can win in one move
    // returns the winning cell if found, {-1,-1} otherwise
    std::pair<int, int> findWinningMove(Board& board, CellState state);
};