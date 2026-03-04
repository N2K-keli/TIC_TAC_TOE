#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class GameLoseAudio
{
public:
    GameLoseAudio();
    void play();
    void stop();

private:
    sf::Music music;
};