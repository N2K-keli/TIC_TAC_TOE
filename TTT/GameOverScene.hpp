#pragma once
#include <SFML/Graphics.hpp>
#include "TextHelper.hpp"
#include "Arrow.hpp"
#include "AudioManager.hpp"
#include "GameManager.hpp"
#include <iostream>

class GameOverScene
{
public:
    void init(sf::RenderWindow& window);
    void setup(GameManager::Result result, int playerScore, int cpuScore, AudioManager& audio); //  called before transitioning here
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window);

    bool goPlayAgain = false; //  signal to TTT.cpp
    bool goBackToMenu = false; //  signal to TTT.cpp

private:
    int selectedIndex = 0; //  0 = PLAY AGAIN, 1 = BACK TO MENU

    //  stored proportional positions
    float resultX = 0.f;
    float resultY = 0.f;
    float scoreX = 0.f;
    float scoreY = 0.f;

    TextHelper resultText{ "",            {0.f, 0.f}, 80 };
    TextHelper scoreText{ "",            {0.f, 0.f}, 50 };
    TextHelper playAgain{ "PLAY AGAIN",  {0.f, 0.f}, 60 };
    TextHelper backToMenu{ "BACK TO MENU",{0.f, 0.f}, 60 };

    Arrow arrow{ {0.f, 0.f} };

    float optionStartY = 0.f;
    float optionSpacing = 0.f;
};