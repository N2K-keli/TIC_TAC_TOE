#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "TextHelper.hpp"
#include <iostream>

class RoundOverScreen
{
public:
    void init(sf::RenderWindow& window);
    void show(int roundNumber, const std::string& winnerText); //  called when round ends
    void update();                                              //  called every frame
    void draw(sf::RenderWindow& window);
    void reset();

    bool isFinished() const; //  true when 3-5 seconds have passed

private:
    bool active = false;
    bool finished = false;
    float duration = 4.f;  //  seconds to display
    float elapsed = 0.f;  //  time elapsed

    sf::Clock clock; //  tracks time

    //  dark overlay
    sf::RectangleShape overlay;

    //  text
    TextHelper roundText{ "", {0.f, 0.f}, 50 };
    TextHelper winnerText{ "", {0.f, 0.f}, 70 };

    float winnerX = 0.f;
    float winnerY = 0.f;
    float roundX = 0.f;
    float roundY = 0.f;
};