#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level1GameAudio
{
public:
    Level1GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};