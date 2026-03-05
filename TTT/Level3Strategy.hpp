#pragma once
#include "CPUStrategy.hpp"

class Level3Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    // Checks if a specific player can win in one move
    // Returns the winning cell if found, {-1,-1} otherwise
    std::pair<int, int> findWinningMove(Board& board, CellState state);

    // Checks if the center cell is available
    std::pair<int, int> tryCenter(Board& board);

    // Tries to take a corner position
    std::pair<int, int> tryCorner(Board& board);

    // Tries to take an edge position
    std::pair<int, int> tryEdge(Board& board);
};