#pragma once
#include "CPUStrategy.hpp"
#include <limits>

class Level4Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    static constexpr int MAX_DEPTH = 4; // Look 4 moves ahead
    static constexpr int WIN_SCORE = 1000;
    static constexpr int LOSE_SCORE = -1000;
    static constexpr int DRAW_SCORE = 0;

    // Minimax with alpha-beta pruning
    int minimax(Board& board, int depth, bool isMaximizing, CellState me, CellState opponent, int alpha, int beta);

    // Evaluates the current board state
    int evaluateBoard(Board& board, CellState me, CellState opponent);

    // Checks if there's a winner on the board
    CellState checkWinner(Board& board);

    // Checks if the board is full (draw condition)
    bool isBoardFull(Board& board);

    // Counts consecutive symbols in all directions from a position
    int countLine(Board& board, int row, int col, int deltaRow, int deltaCol, CellState state);

    // Evaluates threat level (how close to winning)
    int evaluateThreat(Board& board, CellState state);
};