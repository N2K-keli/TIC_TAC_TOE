#pragma once
#include <SFML/Graphics.hpp>
#include "TextHelper.hpp"
#include "AudioManager.hpp"

class GridSizeInput
{
public:
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window);
    void reset();
    bool isConfirmed();
    int getGridSize();

private:
    int currentSize = 3;   
    int minSize = 3;   
    int maxSize = 17;  
    bool confirmed = false;

    TextHelper promptText{ "SELECT GRID SIZE",  {250.f, 180.f}, 50 };
    TextHelper sizeText{ "3",                 {370.f, 280.f}, 80 };
    TextHelper hintText{ "LEFT / RIGHT TO CHANGE  |  ENTER TO CONFIRM", {100.f, 420.f}, 25 };
};