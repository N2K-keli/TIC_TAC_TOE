#pragma once
#include "CPUStrategy.hpp"
#include <limits>
#include <vector>

class Level5Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    static constexpr int WIN_SCORE = 100000;
    static constexpr int LOSE_SCORE = -100000;
    std::vector<std::pair<int, int>> getCandidateMoves(Board& board, CellState currentPlayer);

    // Pattern scores for heuristic evaluation
    static constexpr int FOUR_OPEN = 10000;    // Four in a row with both ends open
    static constexpr int FOUR_HALF = 5000;     // Four in a row with one end open
    static constexpr int THREE_OPEN = 1000;    // Three in a row with both ends open (fork potential)
    static constexpr int THREE_HALF = 500;     // Three in a row with one end open
    static constexpr int TWO_OPEN = 100;       // Two in a row with both ends open
    static constexpr int TWO_HALF = 50;        // Two in a row with one end open

    // Full minimax with alpha-beta pruning (searches to terminal states)
    int minimax(Board& board, int depth, bool isMaximizing, CellState me, CellState opponent,
        int alpha, int beta);

    // Sophisticated evaluation function
    int evaluateBoard(Board& board, CellState me, CellState opponent);

    // Pattern detection and scoring
    int evaluatePosition(Board& board, CellState state);

    // Analyzes a specific line and returns its score
    int scoreLine(const std::vector<CellState>& line, CellState state);

    // Extracts a line in a given direction
    std::vector<CellState> extractLine(Board& board, int startRow, int startCol,
        int deltaRow, int deltaCol, int length);

    // Detects fork opportunities (multiple winning threats)
    int detectForks(Board& board, CellState state);

    // Checks if there's a winner on the board
    CellState checkWinner(Board& board);

    // Checks if the board is full
    bool isBoardFull(Board& board);

    // Counts consecutive symbols in a direction
    int countConsecutive(Board& board, int row, int col, int deltaRow, int deltaCol,
        CellState state, bool& startOpen, bool& endOpen);

    // Prioritizes move ordering for better pruning
    std::vector<std::pair<int, int>> orderMoves(Board& board, CellState currentPlayer);

    // Quick move evaluation for ordering
    int quickEvaluateMove(Board& board, int row, int col, CellState state);
};