#pragma once
#include "Board.hpp"
#include "CPU.hpp"
#include <iostream>

class GameManager
{
public:
    enum class Result { none, playerWin, cpuWin, draw };

    void init(int gridSize);   //  called once grid size is confirmed
    void reset();              //  reset for new round
    void fullReset();          //  reset entire match

    bool handlePlayerMove(int row, int col, Board& board); //  returns true if valid
    void handleCPUMove(Board& board, CPU& cpu);            //  CPU picks and places

    //  getters
    bool   getIsPlayerTurn()  const;
    bool   isGameOver()       const;
    bool   isMatchOver()      const;
    int    getPlayerScore()   const;
    int    getCPUScore()      const;
    int    getRoundNumber()   const;
    Result getResult()        const;
    void loadSave(int pScore, int cScore, int round, bool pTurn);

private:
    bool   playerTurn = true;
    int    playerScore = 0;
    int    cpuScore = 0;
    int    roundNumber = 1;
    bool   gameOver = false;
    bool   matchOver = false;
    int    winCondition = 3;
    int    gridSize = 3;
    Result currentResult = Result::none;

    bool checkWin(Board& board, CellState state);  //  checks rows/cols/diags
    bool checkDraw(Board& board);                  //  checks if board full
    void switchTurn();                             //  toggles playerTurn
    bool checkLine(Board& board, CellState state,
        int startRow, int startCol,
        int deltaRow, int deltaCol);    //  checks a single line
};