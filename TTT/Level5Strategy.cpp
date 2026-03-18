#include "Level5Strategy.hpp"
#include <algorithm>
#include <cmath>

std::pair<int, int> Level5Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    int size = board.getSize();

    // if board is empty place at center immediately
    bool boardEmpty = true;
    for (int r = 0; r < size && boardEmpty; r++)
        for (int c = 0; c < size && boardEmpty; c++)
            if (board.getCell(r, c) != CellState::empty)
                boardEmpty = false;

    if (boardEmpty)
        return { size / 2, size / 2 };

    //  use getCandidateMoves — only cells near existing pieces
    auto moves = getCandidateMoves(board, me);

    for (const auto& move : moves)
    {
        board.setCell(move.first, move.second, me);
        int score = minimax(board, 0, false, me, opponent,
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
int Level5Strategy::minimax(Board& board, int depth, bool isMaximizing,
    CellState me, CellState opponent, int alpha, int beta)
{
    CellState winner = checkWinner(board);
    if (winner == me)       return WIN_SCORE - depth;
    if (winner == opponent) return LOSE_SCORE + depth;
    if (isBoardFull(board)) return 0;

    int size = board.getSize();

    //  much stricter depth limits based on board size
    int maxDepth = (size <= 3) ? 8 : (size == 4) ? 5 : (size == 5) ? 4 : 2;

    if (depth >= maxDepth)
        return evaluateBoard(board, me, opponent);

    auto moves = getCandidateMoves(board, isMaximizing ? me : opponent);

    //  cap moves considered — never evaluate more than 15 candidates
    if ((int)moves.size() > 15)
        moves.resize(15);

    if (isMaximizing)
    {
        int maxScore = std::numeric_limits<int>::min();
        for (const auto& move : moves)
        {
            board.setCell(move.first, move.second, me);
            int score = minimax(board, depth + 1, false, me, opponent, alpha, beta);
            board.setCell(move.first, move.second, CellState::empty);
            maxScore = std::max(maxScore, score);
            alpha = std::max(alpha, score);
            if (beta <= alpha) break;
        }
        return maxScore;
    }
    else
    {
        int minScore = std::numeric_limits<int>::max();
        for (const auto& move : moves)
        {
            board.setCell(move.first, move.second, opponent);
            int score = minimax(board, depth + 1, true, me, opponent, alpha, beta);
            board.setCell(move.first, move.second, CellState::empty);
            minScore = std::min(minScore, score);
            beta = std::min(beta, score);
            if (beta <= alpha) break;
        }
        return minScore;
    }
}

int Level5Strategy::evaluateBoard(Board& board, CellState me, CellState opponent)
{
    
    return evaluatePosition(board, me) - evaluatePosition(board, opponent);
}

int Level5Strategy::evaluatePosition(Board& board, CellState state)
{
    int size = board.getSize();
    int winCondition = std::min(size, 5);
    int totalScore = 0;

    // Evaluate all rows
    for (int row = 0; row < size; row++)
    {
        auto line = extractLine(board, row, 0, 0, 1, size);
        totalScore += scoreLine(line, state);
    }

    // Evaluate all columns
    for (int col = 0; col < size; col++)
    {
        auto line = extractLine(board, 0, col, 1, 0, size);
        totalScore += scoreLine(line, state);
    }

    // Evaluate diagonals (top-left to bottom-right)
    for (int start = -(size - winCondition); start <= (size - winCondition); start++)
    {
        int row = (start < 0) ? -start : 0;
        int col = (start > 0) ? start : 0;
        int length = size - std::abs(start);
        if (length >= winCondition)
        {
            auto line = extractLine(board, row, col, 1, 1, length);
            totalScore += scoreLine(line, state);
        }
    }

    // Evaluate diagonals (top-right to bottom-left)
    for (int start = winCondition - 1; start < size + (size - winCondition); start++)
    {
        int row = (start < size) ? 0 : start - size + 1;
        int col = (start < size) ? start : size - 1;
        int length = std::min(start + 1, 2 * size - start - 1);
        if (length >= winCondition && row < size && col >= 0)
        {
            auto line = extractLine(board, row, col, 1, -1, std::min(length, size));
            totalScore += scoreLine(line, state);
        }
    }

    return totalScore;
}

int Level5Strategy::scoreLine(const std::vector<CellState>& line, CellState state)
{
    int size = line.size();
    int winCondition = std::min((int)size, 5);
    int totalScore = 0;

    // Analyze each possible window of winCondition length
    for (int i = 0; i <= size - winCondition; i++)
    {
        int count = 0;
        int empty = 0;
        bool hasOpponent = false;

        for (int j = i; j < i + winCondition; j++)
        {
            if (line[j] == state)
                count++;
            else if (line[j] == CellState::empty)
                empty++;
            else
                hasOpponent = true;
        }

        // Skip if blocked by opponent
        if (hasOpponent)
            continue;

        // Check if ends are open
        bool leftOpen = (i > 0 && line[i - 1] == CellState::empty);
        bool rightOpen = (i + winCondition < size && line[i + winCondition] == CellState::empty);

        // Score based on pattern
        if (count == winCondition - 1 && empty == 1)
        {
            if (leftOpen && rightOpen)
                totalScore += FOUR_OPEN;
            else if (leftOpen || rightOpen)
                totalScore += FOUR_HALF;
        }
        else if (count == winCondition - 2 && empty == 2)
        {
            if (leftOpen && rightOpen)
                totalScore += THREE_OPEN;
            else if (leftOpen || rightOpen)
                totalScore += THREE_HALF;
        }
        else if (count == winCondition - 3 && empty == 3)
        {
            if (leftOpen && rightOpen)
                totalScore += TWO_OPEN;
            else if (leftOpen || rightOpen)
                totalScore += TWO_HALF;
        }
    }

    return totalScore;
}

std::vector<CellState> Level5Strategy::extractLine(Board& board, int startRow, int startCol,
    int deltaRow, int deltaCol, int length)
{
    std::vector<CellState> line;
    int size = board.getSize();

    for (int i = 0; i < length; i++)
    {
        int row = startRow + i * deltaRow;
        int col = startCol + i * deltaCol;

        if (row >= 0 && row < size && col >= 0 && col < size)
            line.push_back(board.getCell(row, col));
        else
            break;
    }

    return line;
}

int Level5Strategy::detectForks(Board& board, CellState state)
{
    int size = board.getSize();
    int forkCount = 0;

    // A fork is when placing a piece creates multiple winning threats
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) != CellState::empty)
                continue;

            // Temporarily place piece
            board.setCell(row, col, state);

            // Count how many ways this could lead to a win
            int threats = 0;

            // Check all directions
            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                bool startOpen = false, endOpen = false;
                int count = countConsecutive(board, row, col, deltaRows[d], deltaCols[d],
                    state, startOpen, endOpen);

                int winCondition = std::min(size, 5);
                if (count >= winCondition - 1 && (startOpen || endOpen))
                    threats++;
            }

            // Undo placement
            board.setCell(row, col, CellState::empty);

            if (threats >= 2)
                forkCount++;
        }
    }

    return forkCount;
}

int Level5Strategy::countConsecutive(Board& board, int row, int col, int deltaRow, int deltaCol,
    CellState state, bool& startOpen, bool& endOpen)
{
    int size = board.getSize();
    int count = 1;

    // Count forward
    int r = row + deltaRow;
    int c = col + deltaCol;
    while (r >= 0 && r < size && c >= 0 && c < size && board.getCell(r, c) == state)
    {
        count++;
        r += deltaRow;
        c += deltaCol;
    }
    endOpen = (r >= 0 && r < size && c >= 0 && c < size && board.getCell(r, c) == CellState::empty);

    // Count backward
    r = row - deltaRow;
    c = col - deltaCol;
    while (r >= 0 && r < size && c >= 0 && c < size && board.getCell(r, c) == state)
    {
        count++;
        r -= deltaRow;
        c -= deltaCol;
    }
    startOpen = (r >= 0 && r < size && c >= 0 && c < size && board.getCell(r, c) == CellState::empty);

    return count;
}

std::vector<std::pair<int, int>> Level5Strategy::orderMoves(Board& board, CellState currentPlayer)
{
    int size = board.getSize();
    std::vector<std::pair<std::pair<int, int>, int>> movesWithScores;

    // Collect all empty cells with quick evaluation
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            if (board.getCell(row, col) == CellState::empty)
            {
                int score = quickEvaluateMove(board, row, col, currentPlayer);
                movesWithScores.push_back({ {row, col}, score });
            }
        }
    }

    // Sort moves by score (highest first for better pruning)
    std::sort(movesWithScores.begin(), movesWithScores.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    // Extract just the moves
    std::vector<std::pair<int, int>> orderedMoves;
    for (const auto& moveScore : movesWithScores)
        orderedMoves.push_back(moveScore.first);

    return orderedMoves;
}

int Level5Strategy::quickEvaluateMove(Board& board, int row, int col, CellState state)
{
    int size = board.getSize();
    int score = 0;

    // Prefer center positions
    int centerRow = size / 2;
    int centerCol = size / 2;
    int distanceFromCenter = std::abs(row - centerRow) + std::abs(col - centerCol);
    score -= distanceFromCenter * 10;

    // Prefer positions near existing pieces
    int deltaRows[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int deltaCols[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int d = 0; d < 8; d++)
    {
        int r = row + deltaRows[d];
        int c = col + deltaCols[d];
        if (r >= 0 && r < size && c >= 0 && c < size)
        {
            if (board.getCell(r, c) != CellState::empty)
                score += 50;
        }
    }

    return score;
}

CellState Level5Strategy::checkWinner(Board& board)
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

            int deltaRows[] = { 0, 1, 1,  1 };
            int deltaCols[] = { 1, 0, 1, -1 };

            for (int d = 0; d < 4; d++)
            {
                int count = 1;

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

    return CellState::empty;
}

bool Level5Strategy::isBoardFull(Board& board)
{
    int size = board.getSize();

    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            if (board.getCell(row, col) == CellState::empty)
                return false;

    return true;
}
std::vector<std::pair<int, int>> Level5Strategy::getCandidateMoves(Board& board, CellState currentPlayer)
{
    int size = board.getSize();
    int radius = (size <= 5) ? 2 : 1; //  smaller radius for large boards

    std::vector<std::pair<std::pair<int, int>, int>> movesWithScores;

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
            {
                int score = quickEvaluateMove(board, row, col, currentPlayer);
                movesWithScores.push_back({ { row, col }, score });
            }
        }
    }

    std::sort(movesWithScores.begin(), movesWithScores.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    std::vector<std::pair<int, int>> result;
    for (const auto& ms : movesWithScores)
        result.push_back(ms.first);

    return result;
}
