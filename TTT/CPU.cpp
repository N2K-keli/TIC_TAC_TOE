#include "CPU.hpp"

void CPU::init(const std::string& symbolPath,
    const std::string& picturePath,
    const std::string& cpuName)
{
    name = cpuName;

    if (!symbolTexture.loadFromFile(symbolPath))
        std::cerr << "Error: Could not load CPU symbol: " << symbolPath << "\n";
    else
        std::cout << "SUCCESS! CPU symbol loaded: " << symbolPath << "\n";

    if (!pictureTexture.loadFromFile(picturePath))
        std::cerr << "Error: Could not load CPU picture: " << picturePath << "\n";
    else
        std::cout << "SUCCESS! CPU picture loaded: " << picturePath << "\n";
}

void CPU::setStrategy(CPUStrategy* s)
{
    strategy = s; //  assign strategy
}

std::pair<int, int> CPU::makeMove(Board& board, CellState me, CellState opponent)
{
    if (strategy != nullptr)
    {
        return strategy->makeMove(board, me, opponent); //  delegate to strategy
    }

    std::cerr << "Error: No strategy assigned to CPU\n";
    return { -1, -1 }; //  fallback
}

sf::Texture& CPU::getSymbolTexture() { return symbolTexture; }
sf::Texture& CPU::getPictureTexture() { return pictureTexture; }
std::string  CPU::getName() { return name; }