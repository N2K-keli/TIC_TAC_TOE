#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "TextHelper.hpp"
#include <iostream>

class PlayerRender
{
public:
    void init(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, Player& player);

private:
    std::optional<sf::Sprite> pictureSprite; //  was sf::Sprite
    TextHelper nameText{ "", {20.f, 350.f}, 30 };

    void drawPicture(sf::RenderWindow& window, Player& player);
    void drawName(sf::RenderWindow& window, Player& player);
};