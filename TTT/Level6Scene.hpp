#pragma once
#include <SFML/Graphics.hpp>
#include "TextHelper.hpp"
#include <iostream>

class Level6Scene
{
public:
    void draw(sf::RenderWindow& window);
    void onEnter();

    bool hasEntered = false;
    void fullReset()
    {
        hasEntered = false;
        std::cout << "LevelXScene fully reset\n";
    }

private:
    TextHelper levelText{ "LEVEL 6", {300.f, 250.f}, 80 };
};