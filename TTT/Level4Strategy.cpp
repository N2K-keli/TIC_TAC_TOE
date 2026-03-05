#include "Level4Strategy.hpp"
#include <vector>
#include <algorithm>

std::pair<int, int> Level4Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    // Try each empty cell and evaluate using minimax
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) == CellState::empty)
            {
                // Make the move
                board.setCell(row, col, me);

                // Evaluate this move using minimax
                int score = minimax(board, MAX_DEPTH - 1, false, me, opponent,
                    std::numeric_limits<int>::min(),
                    std::numeric_limits<int>::max());

                // Undo the move
                board.setCell(row, col, CellState::empty);

                // Update best move
                if (score > bestScore)
                {
                    bestScore = score;
                    bestMove = { row, col };
                }
            }
        }
    }

    return bestMove;
}

int Level4Strategy::minimax(Board& board, int depth, bool isMaximizing,
    CellState me, CellState opponent, int alpha, int beta)
{
    // Check terminal conditions
    CellState winner = checkWinner(board);

    if (winner == me)
        return WIN_SCORE + depth; // Prefer faster wins
    if (winner == opponent)
        return LOSE_SCORE - depth; // Prefer slower losses
    if (isBoardFull(board) || depth == 0)
        return evaluateBoard(board, me, opponent);

    int size = board.getSize();

    if (isMaximizing)
    {
        int maxScore = std::numeric_limits<int>::min();

        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (board.getCell(row, col) == CellState::empty)
                {
                    board.setCell(row, col, me);
                    int score = minimax(board, depth - 1, false, me, opponent, alpha, beta);
                    board.setCell(row, col, CellState::empty);

                    maxScore = std::max(maxScore, score);
                    alpha = std::max(alpha, score);

                    if (beta <= alpha)
                        return maxScore; // Alpha-beta pruning
                }
            }
        }
        return maxScore;
    }
    else
    {
        int minScore = std::numeric_limits<int>::max();

        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (board.getCell(row, col) == CellState::empty)
                {
                    board.setCell(row, col, opponent);
                    int score = minimax(board, depth - 1, true, me, opponent, alpha, beta);
                    board.setCell(row, col, CellState::empty);

                    minScore = std::min(minScore, score);
                    beta = std::min(beta, score);

                    if (beta <= alpha)
                        return minScore; // Alpha-beta pruning
                }
            }
        }
        return minScore;
    }
}

int Level4Strategy::evaluateBoard(Board& board, CellState me, CellState opponent)
{
    // Evaluate based on potential threats and opportunities
    int myThreat = evaluateThreat(board, me);
    int opponentThreat = evaluateThreat(board, opponent);

    return myThreat - opponentThreat;
}

int Level4Strategy::evaluateThreat(Board& board, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);
    int score = 0;

    // Check all positions for potential threats
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != state)
                continue;

            // Directions: right, down, diagonal down-right, diagonal down-left
            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = countLine(board, row, col, deltaRows[d], deltaCols[d], state);

                // Score based on line length
                if (count == winCondition - 1)
                    score += 100; // One away from winning
                else if (count == winCondition - 2)
                    score += 10;  // Two away from winning
                else if (count >= 2)
                    score += count; // Building a line
            }
        }
    }

    return score;
}

int Level4Strategy::countLine(Board& board, int row, int col, int deltaRow, int deltaCol, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);
    int count = 1;

    // Count forward
    for (int i = 1; i < winCondition; i++)
    {
        int r = row + i * deltaRow;
        int c = col + i * deltaCol;
        if (r < 0 || r >= size || c < 0 || c >= size)
            break;
        if (board.getCell(r, c) == state)
            count++;
        else if (board.getCell(r, c) != CellState::empty)
            return 0; // Blocked by opponent
        else
            break;
    }

    // Count backward
    for (int i = 1; i < winCondition; i++)
    {
        int r = row - i * deltaRow;
        int c = col - i * deltaCol;
        if (r < 0 || r >= size || c < 0 || c >= size)
            break;
        if (board.getCell(r, c) == state)
            count++;
        else if (board.getCell(r, c) != CellState::empty)
            return 0; // Blocked by opponent
        else
            break;
    }

    return count;
}

CellState Level4Strategy::checkWinner(Board& board)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            CellState current = board.getCell(row, col);
            if (current == CellState::empty)
                continue;

            // Directions: right, down, diagonal down-right, diagonal down-left
            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = 1;

                // Count in one direction only (to avoid double counting)
                for (int i = 1; i < winCondition; i++)
                {
                    int r = row + i * deltaRows[d];
                    int c = col + i * deltaCols[d];
                    if (r < 0 || r >= size || c < 0 || c >= size)
                        break;
                    if (board.getCell(r, c) == current)
                        count++;
                    else
                        break;
                }

                if (count >= winCondition)
                    return current;
            }
        }
    }

    return CellState::empty; // No winner
}

bool Level4Strategy::isBoardFull(Board& board)
{
    int size = board.getSize();

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) == CellState::empty)
                return false;
        }
    }

    return true;
}