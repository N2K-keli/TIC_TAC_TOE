#include "Board.hpp"

Board::Board()
{
    init(3); 
}

void Board::init(int size)
{
    gridSize = size;
    grid.clear();

    
    grid.resize(gridSize, std::vector<CellState>(gridSize, CellState::empty));

    std::cout << "Board initialized: " << gridSize << "x" << gridSize << "\n";
}

void Board::reset()
{
    for (int row = 0; row < gridSize; row++)
    {
        for (int col = 0; col < gridSize; col++)
        {
            grid[row][col] = CellState::empty;
        }
    }
    std::cout << "Board reset\n";
}

int Board::getSize()
{
    return gridSize;
}

CellState Board::getCell(int row, int col)
{
    return grid[row][col];
}

void Board::setCell(int row, int col, CellState state)
{
    grid[row][col] = state;
}