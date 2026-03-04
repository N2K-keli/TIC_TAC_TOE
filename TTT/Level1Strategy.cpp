#include "Level1Strategy.hpp"

std::pair<int, int> Level1Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();

    //  collect all empty cells
    std::vector<std::pair<int, int>> emptyCells;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) == CellState::empty)
            {
                emptyCells.push_back({ row, col });
            }
        }
    }

    //  pick a random empty cell
    if (!emptyCells.empty())
    {
        int randomIndex = std::rand() % emptyCells.size();
        return emptyCells[randomIndex];
    }

    //  fallback — should never reach here if game logic is correct
    return { -1, -1 };
}