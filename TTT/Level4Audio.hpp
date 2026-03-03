#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level4Audio
{
public:
    Level4Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};