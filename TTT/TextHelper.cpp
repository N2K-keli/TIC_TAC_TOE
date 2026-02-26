#include"TextHelper.hpp"
#include <iostream>

TextHelper::TextHelper(const std::string& string, sf::Vector2f position, unsigned int size)
    : text(font)
{
    if (!font.openFromFile("assets/fonts/GreatsRacingFreeForPersonalItalic-BLLM8.otf"))
    {
        std::cerr << "Error: Could not load font\n";
    }

    text.setString(string);
    text.setPosition(position);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
}

void TextHelper::draw(sf::RenderWindow& window)
{
    window.draw(text);
}