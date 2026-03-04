#pragma once
#include "CPUStrategy.hpp"
#include <vector>
#include <cstdlib> 
#include <ctime>    

class Level1Strategy : public CPUStrategy
{
public:
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent) override;
};