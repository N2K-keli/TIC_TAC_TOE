#include "Level2Strategy.hpp"
#include <vector>
#include <cstdlib>

std::pair<int, int> Level2Strategy::findWinningMove(Board& board, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != CellState::empty) continue;

            //  temporarily place the symbol
            board.setCell(row, col, state);

            //  check all directions from this cell
            bool wins = false;

            // directions: right, down, diagonal down-right, diagonal down-left
            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = 1;

                //  count forward
                for (int i = 1; i < winCondition; i++)
                {
                    int r = row + i * deltaRows[d];
                    int c = col + i * deltaCols[d];
                    if (r < 0 || r >= size || c < 0 || c >= size) break;
                    if (board.getCell(r, c) == state) count++;
                    else break;
                }

                //  count backward
                for (int i = 1; i < winCondition; i++)
                {
                    int r = row - i * deltaRows[d];
                    int c = col - i * deltaCols[d];
                    if (r < 0 || r >= size || c < 0 || c >= size) break;
                    if (board.getCell(r, c) == state) count++;
                    else break;
                }

                if (count >= winCondition)
                {
                    wins = true;
                    break;
                }
            }

            //  undo the temporary placement
            board.setCell(row, col, CellState::empty);

            if (wins) return { row, col };
        }
    }
    return { -1, -1 }; //  no winning move found
}

std::pair<int, int> Level2Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();

    //  Step 1 — can I win? take it
    auto winMove = findWinningMove(board, me);
    if (winMove.first != -1) return winMove;

    //  Step 2 — can opponent win? block it
    auto blockMove = findWinningMove(board, opponent);
    if (blockMove.first != -1) return blockMove;

    //  Step 3 — random fallback
    std::vector<std::pair<int, int>> emptyCells;
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            if (board.getCell(row, col) == CellState::empty)
                emptyCells.push_back({ row, col });

    if (!emptyCells.empty())
        return emptyCells[std::rand() % emptyCells.size()];

    return { -1, -1 };
}