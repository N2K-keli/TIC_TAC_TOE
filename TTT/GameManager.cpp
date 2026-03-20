#include "GameManager.hpp"

void GameManager::init(int size)
{
    gridSize = size;
    winCondition = std::min(gridSize, 5); 
    fullReset();
    std::cout << "GameManager initialized — gridSize: " << gridSize
        << " winCondition: " << winCondition << "\n";
}

void GameManager::reset()
{
    playerTurn = true;
    gameOver = false;
    currentResult = Result::none;
    std::cout << "Round " << roundNumber << " reset\n";
}

void GameManager::fullReset()
{
    playerScore = 0;
    cpuScore = 0;
    roundNumber = 1;
    matchOver = false;
    reset();
}

bool GameManager::handlePlayerMove(int row, int col, Board& board)
{
    //  ignore if not player turn or game over
    if (!playerTurn || gameOver) return false;

    //  ignore if cell is not empty
    if (board.getCell(row, col) != CellState::empty) return false;

    //  place player symbol
    board.setCell(row, col, CellState::player);
    std::cout << "Player placed at (" << row << ", " << col << ")\n";

    // check win
    if (checkWin(board, CellState::player))
    {
        playerScore++;
        gameOver = true;
        currentResult = Result::playerWin;
        std::cout << "Player wins round " << roundNumber << "!\n";

        if (playerScore >= 2)
        {
            matchOver = true;
            std::cout << "Player wins the match!\n";
        }
        else
        {
            roundNumber++;
        }
        return true;
    }

    //  check draw
    if (checkDraw(board))
    {
        gameOver = true;
        currentResult = Result::draw;
        std::cout << "Draw!\n";
        roundNumber++;
        return true;
    }

    //  switch to CPU turn
    switchTurn();
    return true;
}

void GameManager::handleCPUMove(Board& board, CPU& cpu)
{
    //  ignore if not CPU turn or game over
    if (playerTurn || gameOver) return;

    auto [row, col] = cpu.makeMove(board, CellState::cpu, CellState::player);

    if (row == -1 || col == -1) return; //  fallback safety check

    //  place CPU symbol
    board.setCell(row, col, CellState::cpu);
    std::cout << "CPU placed at (" << row << ", " << col << ")\n";

    //  check win
    if (checkWin(board, CellState::cpu))
    {
        cpuScore++;
        gameOver = true;
        currentResult = Result::cpuWin;
        std::cout << "CPU wins round " << roundNumber << "!\n";

        if (cpuScore >= 2)
        {
            matchOver = true;
            std::cout << "CPU wins the match!\n";
        }
        else
        {
            roundNumber++;
        }
        return;
    }

    //  check draw
    if (checkDraw(board))
    {
        gameOver = true;
        currentResult = Result::draw;
        std::cout << "Draw!\n";
        roundNumber++;
        return;
    }

    //  switch back to player turn
    switchTurn();
}

bool GameManager::checkLine(Board& board, CellState state,
    int startRow, int startCol,
    int deltaRow, int deltaCol)
{
    int count = 0;
    int size = board.getSize();

    for (int i = 0; i < size; i++)
    {
        int row = startRow + i * deltaRow;
        int col = startCol + i * deltaCol;

        // bounds check
        if (row < 0 || row >= size || col < 0 || col >= size) break;

        if (board.getCell(row, col) == state)
        {
            count++;
            if (count >= winCondition) return true; //  win found
        }
        else
        {
            count = 0; // reset streak
        }
    }
    return false;
}

bool GameManager::checkWin(Board& board, CellState state)
{
    int size = board.getSize();

    for (int i = 0; i < size; i++)
    {
        //  check each row
        if (checkLine(board, state, i, 0, 0, 1)) return true;

        //  check each column
        if (checkLine(board, state, 0, i, 1, 0)) return true;
    }

    //  check all diagonals (top-left to bottom-right)
    for (int row = 0; row <= size - winCondition; row++)
        for (int col = 0; col <= size - winCondition; col++)
            if (checkLine(board, state, row, col, 1, 1)) return true;

    //  check all diagonals (top-right to bottom-left)
    for (int row = 0; row <= size - winCondition; row++)
        for (int col = winCondition - 1; col < size; col++)
            if (checkLine(board, state, row, col, 1, -1)) return true;

    return false;
}

bool GameManager::checkDraw(Board& board)
{
    int size = board.getSize();
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            if (board.getCell(row, col) == CellState::empty)
                return false; //  still empty cells — not a draw
    return true; //  no empty cells — draw
}

void GameManager::switchTurn()
{
    playerTurn = !playerTurn;
}

//  getters
bool           GameManager::getIsPlayerTurn() const { return playerTurn; }
bool           GameManager::isGameOver()      const { return gameOver; }
bool           GameManager::isMatchOver()     const { return matchOver; }
int            GameManager::getPlayerScore()  const { return playerScore; }
int            GameManager::getCPUScore()     const { return cpuScore; }
int            GameManager::getRoundNumber()  const { return roundNumber; }
GameManager::Result GameManager::getResult()  const { return currentResult; }


void GameManager::loadSave(int pScore, int cScore, int round, bool pTurn)
{
    playerScore = pScore;
    cpuScore = cScore;
    roundNumber = round;
    playerTurn = pTurn;
    gameOver = false;
    matchOver = false;
    currentResult = Result::none;
    std::cout << "GameManager loaded — score: " << pScore << "-" << cScore
        << " round: " << round << "\n";
}
