#pragma once
#include <SFML/Graphics.hpp>
#include "TextHelper.hpp"
#include "AudioManager.hpp"

class GridSizeInput
{
public:
    void init(sf::RenderWindow& window); //  new — calculates proportional positions
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window);
    void reset();
    bool isConfirmed();
    int  getGridSize();

private:
    int  currentSize = 3;
    int  minSize = 3;
    int  maxSize = 17;
    bool confirmed = false;

    // positions calculated in init()
    float promptX = 0.f;
    float promptY = 0.f;
    float sizeX = 0.f;
    float sizeY = 0.f;
    float hintX = 0.f;
    float hintY = 0.f;

    TextHelper promptText{ "SELECT GRID SIZE",                          {0.f, 0.f}, 50 };
    TextHelper sizeText{ "3",                                         {0.f, 0.f}, 80 };
    TextHelper hintText{ "LEFT / RIGHT TO CHANGE  |  ENTER TO CONFIRM", {0.f, 0.f}, 25 };
};