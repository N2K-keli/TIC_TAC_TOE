#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level5GameAudio
{
public:
    Level5GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};