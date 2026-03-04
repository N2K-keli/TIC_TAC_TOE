#include "CPU.hpp"

void CPU::init(const std::string& symbolPath,
    const std::string& picturePath,
    const std::string& cpuName)
{
    name = cpuName;

    if (!symbolTexture.loadFromFile(symbolPath))
    {
        std::cerr << "Error: Could not load CPU symbol: " << symbolPath << "\n";
    }
    else
    {
        std::cout << "SUCCESS! CPU symbol loaded: " << symbolPath << "\n";
    }

    if (!pictureTexture.loadFromFile(picturePath))
    {
        std::cerr << "Error: Could not load CPU picture: " << picturePath << "\n";
    }
    else
    {
        std::cout << "SUCCESS! CPU picture loaded: " << picturePath << "\n";
    }
}

sf::Texture& CPU::getSymbolTexture()
{
    return symbolTexture;
}

sf::Texture& CPU::getPictureTexture()
{
    return pictureTexture;
}

std::string CPU::getName()
{
    return name;
}