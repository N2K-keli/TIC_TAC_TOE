#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Leve61Audio
{
public:
    Level6Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};