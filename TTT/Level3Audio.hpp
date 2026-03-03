#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level3Audio
{
public:
    Level3Audio();
    void play();
    void stop();
    bool isFinished();

private:
    sf::Music music;
};