#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextHelper
{
public:
    TextHelper(const std::string& string, sf::Vector2f position, unsigned int size);
    void draw(sf::RenderWindow& window);
    sf::Text& getText(); 
private:
    sf::Font font;
    sf::Text text;
};