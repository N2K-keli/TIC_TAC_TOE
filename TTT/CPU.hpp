#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "CPUStrategy.hpp"
#include "Board.hpp"

class CPU
{
public:
    void init(const std::string& symbolPath,
        const std::string& picturePath,
        const std::string& cpuName);

    void setStrategy(CPUStrategy* s); //  assign strategy from level scene
    std::pair<int, int> makeMove(Board& board, CellState me, CellState opponent); // 

    sf::Texture& getSymbolTexture();
    sf::Texture& getPictureTexture();
    std::string  getName();

private:
    sf::Texture    symbolTexture;
    sf::Texture    pictureTexture;
    std::string    name;
    CPUStrategy* strategy = nullptr; //  points to assigned strategy
};