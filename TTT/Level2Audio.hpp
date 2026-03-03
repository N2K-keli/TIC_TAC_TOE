#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level2Audio
{
public:
    Level2Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};