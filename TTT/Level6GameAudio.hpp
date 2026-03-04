#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level6GameAudio
{
public:
    Level6GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};