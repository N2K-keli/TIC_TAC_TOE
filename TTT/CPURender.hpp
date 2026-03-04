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
    std::optional<sf::Sprite> pictureSprite;
    TextHelper nameText{ "", {0.f, 0.f}, 30 };

    //  stored proportional values calculated in init()
    float panelWidth = 0.f;
    float panelHeight = 0.f;
    float picX = 0.f;
    float picY = 0.f;
    float nameX = 0.f;
    float nameY = 0.f;

    void drawPicture(sf::RenderWindow& window, CPU& cpu);
    void drawName(sf::RenderWindow& window, CPU& cpu);
};