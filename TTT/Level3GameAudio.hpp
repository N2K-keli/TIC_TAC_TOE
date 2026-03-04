#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Level3GameAudio
{
public:
    Level3GameAudio();
    void play();
    void stop();

private:
    sf::Music music;
};