#include "Player.hpp"

void Player::init(const std::string& symbolPath,
    const std::string& picturePath,
    const std::string& playerName)
{
    name = playerName;

    if (!symbolTexture.loadFromFile(symbolPath))
    {
        std::cerr << "Error: Could not load player symbol: " << symbolPath << "\n";
    }
    else
    {
        std::cout << "SUCCESS! Player symbol loaded: " << symbolPath << "\n";
    }

    if (!pictureTexture.loadFromFile(picturePath))
    {
        std::cerr << "Error: Could not load player picture: " << picturePath << "\n";
    }
    else
    {
        std::cout << "SUCCESS! Player picture loaded: " << picturePath << "\n";
    }
}

sf::Texture& Player::getSymbolTexture()
{
    return symbolTexture;
}

sf::Texture& Player::getPictureTexture()
{
    return pictureTexture;
}

std::string Player::getName()
{
    return name;
}