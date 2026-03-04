#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class GameDrawAudio
{
public:
    GameDrawAudio();
    void play();
    void stop();

private:
    sf::Music music;
};