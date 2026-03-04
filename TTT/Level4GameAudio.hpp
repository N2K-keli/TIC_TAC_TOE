#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level4GameAudio
{
public:
    Level4GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};