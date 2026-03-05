#include "Level3Strategy.hpp"
#include <vector>
#include <cstdlib>

std::pair<int, int> Level3Strategy::findWinningMove(Board& board, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != CellState::empty) continue;

            // Temporarily place the symbol
            board.setCell(row, col, state);

            // Check all directions from this cell
            bool wins = false;
            // Directions: right, down, diagonal down-right, diagonal down-left
            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = 1;

                // Count forward
                for (int i = 1; i < winCondition; i++)
                {
                    int r = row + i * deltaRows[d];
                    int c = col + i * deltaCols[d];
                    if (r < 0 || r >= size || c < 0 || c >= size) break;
                    if (board.getCell(r, c) == state) count++;
                    else break;
                }

                // Count backward
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

            // Undo the temporary placement
            board.setCell(row, col, CellState::empty);

            if (wins) return { row, col };
        }
    }

    return { -1, -1 }; // No winning move found
}

std::pair<int, int> Level3Strategy::tryCenter(Board& board)
{
    int size = board.getSize();
    int center = size / 2;

    // Check if center exists and is empty
    if (board.getCell(center, center) == CellState::empty)
    {
        return { center, center };
    }

    return { -1, -1 };
}

std::pair<int, int> Level3Strategy::tryCorner(Board& board)
{
    int size = board.getSize();

    // Define corners
    std::vector<std::pair<int, int>> corners = {
        { 0, 0 },
        { 0, size - 1 },
        { size - 1, 0 },
        { size - 1, size - 1 }
    };

    // Shuffle corners for variety
    for (int i = corners.size() - 1; i > 0; i--)
    {
        int j = std::rand() % (i + 1);
        std::swap(corners[i], corners[j]);
    }

    // Try each corner
    for (const auto& corner : corners)
    {
        if (board.getCell(corner.first, corner.second) == CellState::empty)
        {
            return corner;
        }
    }

    return { -1, -1 };
}

std::pair<int, int> Level3Strategy::tryEdge(Board& board)
{
    int size = board.getSize();
    std::vector<std::pair<int, int>> edges;

    // Collect all edge cells (excluding corners)
    // Top and bottom edges
    for (int col = 1; col < size - 1; col++)
    {
        edges.push_back({ 0, col });           // Top edge
        edges.push_back({ size - 1, col });    // Bottom edge
    }

    // Left and right edges
    for (int row = 1; row < size - 1; row++)
    {
        edges.push_back({ row, 0 });           // Left edge
        edges.push_back({ row, size - 1 });    // Right edge
    }

    // Shuffle edges for variety
    for (int i = edges.size() - 1; i > 0; i--)
    {
        int j = std::rand() % (i + 1);
        std::swap(edges[i], edges[j]);
    }

    // Try each edge
    for (const auto& edge : edges)
    {
        if (board.getCell(edge.first, edge.second) == CellState::empty)
        {
            return edge;
        }
    }

    return { -1, -1 };
}

std::pair<int, int> Level3Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();

    // Step 1 — Can I win? Take it
    auto winMove = findWinningMove(board, me);
    if (winMove.first != -1) return winMove;

    // Step 2 — Can opponent win? Block it
    auto blockMove = findWinningMove(board, opponent);
    if (blockMove.first != -1) return blockMove;

    // Step 3 — Try to take center
    auto centerMove = tryCenter(board);
    if (centerMove.first != -1) return centerMove;

    // Step 4 — Try to take a corner
    auto cornerMove = tryCorner(board);
    if (cornerMove.first != -1) return cornerMove;

    // Step 5 — Try to take an edge
    auto edgeMove = tryEdge(board);
    if (edgeMove.first != -1) return edgeMove;

    // Step 6 — Random fallback (should rarely happen)
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

    if (!emptyCells.empty())
    {
        return emptyCells[std::rand() % emptyCells.size()];
    }

    return { -1, -1 };
}