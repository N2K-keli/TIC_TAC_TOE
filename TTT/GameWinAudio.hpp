#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class GameWinAudio
{
public:
    GameWinAudio();
    void play();
    void stop();

private:
    sf::Music music;
};