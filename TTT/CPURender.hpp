#pragma once
#include <SFML/Graphics.hpp>
#include "CPU.hpp"
#include "TextHelper.hpp"
#include <iostream>

class CPURender
{
public:
    void init(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, CPU& cpu);

private:
    std::optional<sf::Sprite> pictureSprite; //  was sf::Sprite
    TextHelper nameText{ "", {620.f, 350.f}, 30 };

    void drawPicture(sf::RenderWindow& window, CPU& cpu);
    void drawName(sf::RenderWindow& window, CPU& cpu);
};