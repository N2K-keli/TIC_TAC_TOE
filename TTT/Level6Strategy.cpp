#include "Level6Strategy.hpp"
#include <algorithm>

std::pair<int, int> Level6Strategy::makeMove(Board& board, CellState me, CellState opponent)
{
    int size = board.getSize();

    //  if board is empty place at center
    bool boardEmpty = true;
    for (int r = 0; r < size && boardEmpty; r++)
        for (int c = 0; c < size && boardEmpty; c++)
            if (board.getCell(r, c) != CellState::empty)
                boardEmpty = false;

    if (boardEmpty)
        return { size / 2, size / 2 };

    //  create root node
    MCTSNode root;
    root.boardState = board;
    root.move = { -1, -1 };
    root.currentPlayer = me;
    root.parent = nullptr;

    int simCount = getSimulationCount(size);

    // run simulations
    for (int i = 0; i < simCount; i++)
    {
        // 1. SELECTION
        auto emptyCells = getEmptyCells(root.boardState);
        MCTSNode* selected = selection(&root, emptyCells);

        // 2. EXPANSION
        MCTSNode* expanded = expansion(selected, me, opponent);

        // 3. SIMULATION
        int result = simulation(expanded->boardState, expanded->currentPlayer, me, opponent);

        // 4. BACKPROPAGATION
        backpropagation(expanded, result);
    }

    //  pick child with most visits — most robust choice
    MCTSNode* bestChild = nullptr;
    int mostVisits = -1;

    for (auto& child : root.children)
    {
        if (child->visits > mostVisits)
        {
            mostVisits = child->visits;
            bestChild = child.get();
        }
    }

    if (bestChild != nullptr)
        return bestChild->move;

    //  fallback — pick random empty cell
    auto empty = getEmptyCells(board);
    if (!empty.empty())
        return empty[std::rand() % empty.size()];

    return { -1, -1 };
}

MCTSNode* Level6Strategy::selection(MCTSNode* node, const std::vector<std::pair<int, int>>& emptyCells)
{
    //  traverse tree picking highest UCB1 until we find unvisited or leaf
    while (!node->children.empty())
    {
        auto nodeEmpty = getEmptyCells(node->boardState);

        if (!node->isFullyExpanded(nodeEmpty))
            return node; //  not fully expanded — expand here

        //  pick child with highest UCB1
        MCTSNode* best = nullptr;
        double bestScore = -1.0;

        for (auto& child : node->children)
        {
            double score = child->ucb1();
            if (score > bestScore)
            {
                bestScore = score;
                best = child.get();
            }
        }

        if (best == nullptr) break;
        node = best;
    }

    return node;
}

MCTSNode* Level6Strategy::expansion(MCTSNode* node, CellState me, CellState opponent)
{
    auto emptyCells = getEmptyCells(node->boardState);

    //  find moves not yet explored
    std::vector<std::pair<int, int>> unexplored;
    for (const auto& cell : emptyCells)
    {
        bool found = false;
        for (const auto& child : node->children)
            if (child->move == cell) { found = true; break; }
        if (!found)
            unexplored.push_back(cell);
    }

    if (unexplored.empty())
        return node; // fully expanded — return node itself

    //  pick random unexplored move
    auto move = unexplored[std::rand() % unexplored.size()];

    //  create new child node
    auto newNode = std::make_unique<MCTSNode>();
    newNode->boardState = node->boardState;
    newNode->boardState.setCell(move.first, move.second, node->currentPlayer);
    newNode->move = move;
    newNode->currentPlayer = (node->currentPlayer == me) ? opponent : me;
    newNode->parent = node;

    MCTSNode* ptr = newNode.get();
    node->children.push_back(std::move(newNode));

    return ptr;
}

int Level6Strategy::simulation(Board board, CellState currentPlayer, CellState me, CellState opponent)
{
    int maxSteps = 30; //  cap simulation length
    int steps = 0;

    while (steps < maxSteps)
    {
        CellState winner = checkWinner(board, me, opponent);
        if (winner == me)       return 1;
        if (winner == opponent) return -1;
        if (isBoardFull(board)) return 0;

        auto empty = getEmptyCells(board);
        if (empty.empty()) return 0;

        //  pick random empty cell
        auto move = empty[std::rand() % empty.size()];
        board.setCell(move.first, move.second, currentPlayer);
        currentPlayer = (currentPlayer == me) ? opponent : me;
        steps++;
    }

    return 0; //  treat timeout as draw
}

void Level6Strategy::backpropagation(MCTSNode* node, int result)
{
    //  walk back up tree updating wins and visits
    while (node != nullptr)
    {
        node->visits++;
        if (result == 1) node->wins++; //  count win
        node = node->parent;
    }
}

std::vector<std::pair<int, int>> Level6Strategy::getEmptyCells( Board& board)
{
    std::vector<std::pair<int, int>> empty;
    int size = board.getSize();
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            if (board.getCell(r, c) == CellState::empty)
                empty.push_back({ r, c });
    return empty;
}

CellState Level6Strategy::checkWinner(Board& board, CellState me, CellState opponent)
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

bool Level6Strategy::isBoardFull(Board& board)
{
    int size = board.getSize();
    for (int r = 0; r < size; r++)
        for (int c = 0; c < size; c++)
            if (board.getCell(r, c) == CellState::empty)
                return false;
    return true;
}

int Level6Strategy::getSimulationCount(int boardSize)
{
    if (boardSize <= 3)  return 1000; 
    if (boardSize <= 5)  return 500;  
    if (boardSize <= 10) return 200;  
    return 100;                       
}