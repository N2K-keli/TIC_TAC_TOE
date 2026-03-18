#pragma once
#include "CPUStrategy.hpp"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <limits>

// ✅ MCTS tree node
struct MCTSNode
{
    Board               boardState;       // board at this node
    std::pair<int, int>  move;             // move that led to this node
    CellState           currentPlayer;    //  whose turn at this node
    int                 wins = 0;       // wins from simulations through this node
    int                 visits = 0;       //  total simulations through this node

    MCTSNode* parent = nullptr;
    std::vector<std::unique_ptr<MCTSNode>> children;

    //  UCB1 formula — balances exploration vs exploitation
    double ucb1(double explorationConstant = 1.414) const
    {
        if (visits == 0) return std::numeric_limits<double>::max(); //  unvisited = highest priority
        return (double)wins / visits +
            explorationConstant * std::sqrt(std::log(parent->visits) / visits);
    }

    bool isFullyExpanded(const std::vector<std::pair<int, int>>& emptyCells) const
    {
        return children.size() == emptyCells.size();
    }
};

class Level6Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;

private:
    // MCTS phases
    MCTSNode* selection(MCTSNode* node, const std::vector<std::pair<int, int>>& emptyCells);
    MCTSNode* expansion(MCTSNode* node, CellState me, CellState opponent);
    int       simulation(Board board, CellState currentPlayer, CellState me, CellState opponent);
    void      backpropagation(MCTSNode* node, int result);

    //  helpers
    std::vector<std::pair<int, int>> getEmptyCells( Board& board);
    CellState checkWinner(Board& board, CellState me, CellState opponent);
    bool      isBoardFull(Board& board);
    int       getSimulationCount(int boardSize);
};