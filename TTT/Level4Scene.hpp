#pragma once
#include <SFML/Graphics.hpp>
#include "TextHelper.hpp"
#include <iostream>

class Level4Scene
{
public:
    void draw(sf::RenderWindow& window);
    void onEnter();

    bool hasEntered = false;

private:
    TextHelper levelText{ "LEVEL 4", {300.f, 250.f}, 80 };
};