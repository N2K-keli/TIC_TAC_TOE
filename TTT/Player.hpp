#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Player
{
public:
    void init(const std::string& symbolPath,
        const std::string& picturePath,
        const std::string& playerName);

    sf::Texture& getSymbolTexture();
    sf::Texture& getPictureTexture();
    std::string  getName();

private:
    sf::Texture symbolTexture;
    sf::Texture pictureTexture;
    std::string name;
};