#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level5Audio
{
public:
    Level5Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};