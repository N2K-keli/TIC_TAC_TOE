#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level2GameAudio
{
public:
    Level2GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};