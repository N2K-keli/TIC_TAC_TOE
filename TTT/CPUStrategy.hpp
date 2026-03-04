#pragma once
#include "Board.hpp"
#include <utility> 

class CPUStrategy
{
public:
    virtual std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) = 0;
    virtual ~CPUStrategy() = default; //  virtual destructor — important for inheritance
};