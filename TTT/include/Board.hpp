#pragma once
#include <vector>
#include <iostream>

enum class CellState
{
    empty,
    player,
    cpu
};

class Board
{
public:
    Board();                         
    void init(int size);             
    void reset();                     
    int getSize();                    
    CellState getCell(int row, int col);         
    void setCell(int row, int col, CellState state);

private:
    int gridSize = 3;
    std::vector<std::vector<CellState>> grid;
};