#pragma once
#include <SFML/Audio.hpp>

class IntroAudio
{
public:
    IntroAudio();
    void play();
    void stop();
private:
    sf::Music music;
};