#include "Level4Strategy.hpp"
#include <vector>
#include <algorithm>

std::pair<int, int> Level4Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    // ✅ if board is empty place at center
    bool boardEmpty = true;
    for (int r = 0; r < size && boardEmpty; r++)
        for (int c = 0; c < size && boardEmpty; c++)
            if (board.getCell(r, c) != CellState::empty)
                boardEmpty = false;

    if (boardEmpty)
        return { size / 2, size / 2 };

    // ✅ use candidate moves instead of all empty cells
    auto moves = getCandidateMoves(board, me);

    for (const auto& move : moves)
    {
        board.setCell(move.first, move.second, me);
        int score = minimax(board, MAX_DEPTH - 1, false, me, opponent,
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max());
        board.setCell(move.first, move.second, CellState::empty);

        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int Level4Strategy::minimax(Board& board, int depth, bool isMaximizing,
    CellState me, CellState opponent, int alpha, int beta)
{
    CellState winner = checkWinner(board);
    if (winner == me)       return WIN_SCORE + depth;
    if (winner == opponent) return LOSE_SCORE - depth;
    if (isBoardFull(board) || depth == 0)
        return evaluateBoard(board, me, opponent);

    // ✅ use candidate moves — only cells near existing pieces
    auto moves = getCandidateMoves(board, isMaximizing ? me : opponent);

    // ✅ cap moves considered
    if ((int)moves.size() > 10)
        moves.resize(10);

    if (isMaximizing)
    {
        int maxScore = std::numeric_limits<int>::min();
        for (const auto& move : moves)
        {
            board.setCell(move.first, move.second, me);
            int score = minimax(board, depth - 1, false, me, opponent, alpha, beta);
            board.setCell(move.first, move.second, CellState::empty);
            maxScore = std::max(maxScore, score);
            alpha = std::max(alpha, score);
            if (beta <= alpha) return maxScore;
        }
        return maxScore;
    }
    else
    {
        int minScore = std::numeric_limits<int>::max();
        for (const auto& move : moves)
        {
            board.setCell(move.first, move.second, opponent);
            int score = minimax(board, depth - 1, true, me, opponent, alpha, beta);
            board.setCell(move.first, move.second, CellState::empty);
            minScore = std::min(minScore, score);
            beta = std::min(beta, score);
            if (beta <= alpha) return minScore;
        }
        return minScore;
    }
}

int Level4Strategy::evaluateBoard(Board& board, CellState me, CellState opponent)
{
    return evaluateThreat(board, me) - evaluateThreat(board, opponent);
}

int Level4Strategy::evaluateThreat(Board& board, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);
    int score = 0;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != state) continue;

            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = countLine(board, row, col, deltaRows[d], deltaCols[d], state);
                if (count == winCondition - 1) score += 100;
                else if (count == winCondition - 2) score += 10;
                else if (count >= 2)                score += count;
            }
        }
    }
    return score;
}

int Level4Strategy::countLine(Board& board, int row, int col,
    int deltaRow, int deltaCol, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);
    int count = 1;

    for (int i = 1; i < winCondition; i++)
    {
        int r = row + i * deltaRow;
        int c = col + i * deltaCol;
        if (r < 0 || r >= size || c < 0 || c >= size) break;
        if (board.getCell(r, c) == state)              count++;
        else if (board.getCell(r, c) != CellState::empty) return 0;
        else break;
    }

    for (int i = 1; i < winCondition; i++)
    {
        int r = row - i * deltaRow;
        int c = col - i * deltaCol;
        if (r < 0 || r >= size || c < 0 || c >= size) break;
        if (board.getCell(r, c) == state)              count++;
        else if (board.getCell(r, c) != CellState::empty) return 0;
        else break;
    }

    return count;
}

// ✅ new — only consider cells near existing pieces
std::vector<std::pair<int, int>> Level4Strategy::getCandidateMoves(Board& board, CellState currentPlayer)
{
    int size = board.getSize();
    int radius = (size <= 5) ? 2 : 1; // ✅ smaller radius for large boards

    std::vector<std::pair<int, int>> moves;

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != CellState::empty) continue;

            bool hasNeighbour = false;
            for (int dr = -radius; dr <= radius && !hasNeighbour; dr++)
                for (int dc = -radius; dc <= radius && !hasNeighbour; dc++)
                {
                    if (dr == 0 && dc == 0) continue;
                    int r = row + dr;
                    int c = col + dc;
                    if (r >= 0 && r < size && c >= 0 && c < size)
                        if (board.getCell(r, c) != CellState::empty)
                            hasNeighbour = true;
                }

            if (hasNeighbour)
                moves.push_back({ row, col });
        }
    }

    return moves;
}

CellState Level4Strategy::checkWinner(Board& board)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);

    int deltaRows[] = { 0, 1, 1,  1 };
    int deltaCols[] = { 1, 0, 1, -1 };

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            CellState current = board.getCell(row, col);
            if (current == CellState::empty) continue;

            for (int d = 0; d < 4; d++)
            {
                int count = 1;
                for (int i = 1; i < winCondition; i++)
                {
                    int r = row + i * deltaRows[d];
                    int c = col + i * deltaCols[d];
                    if (r < 0 || r >= size || c < 0 || c >= size) break;
                    if (board.getCell(r, c) == current) count++;
                    else break;
                }
                if (count >= winCondition) return current;
            }
        }
    }
    return CellState::empty;
}

bool Level4Strategy::isBoardFull(Board& board)
{
    int size = board.getSize();
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            if (board.getCell(row, col) == CellState::empty)
                return false;
    return true;
}