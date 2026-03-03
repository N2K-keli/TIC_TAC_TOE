#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level1Audio
{
public:
    Level1Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};