#pragma once
#include "CPUStrategy.hpp"
#include <limits>
#include <vector>

class Level4Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    static constexpr int MAX_DEPTH = 3;       
    static constexpr int WIN_SCORE = 100000;
    static constexpr int LOSE_SCORE = -100000;

    int       minimax(Board& board, int depth, bool isMaximizing,
        CellState me, CellState opponent, int alpha, int beta);
    int       evaluateBoard(Board& board, CellState me, CellState opponent);
    int       evaluateThreat(Board& board, CellState state);
    int       countLine(Board& board, int row, int col,
        int deltaRow, int deltaCol, CellState state);
    CellState checkWinner(Board& board);
    bool      isBoardFull(Board& board);

    std::vector<std::pair<int, int>> getCandidateMoves(Board& board, CellState currentPlayer); // ✅
};