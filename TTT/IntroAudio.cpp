


#include <iostream>
#include"IntroAudio.hpp"


IntroAudio::IntroAudio()
{
    if (!music.openFromFile("assets/audio/LogoIntro.mp3"))
    {
        std::cerr << "Error: Could not load intro music\n";
    }
    else
    {
        std::cout << "SUCCESS! Intro music loaded!\n";
    }

    music.setLooping(false);
}

void IntroAudio::play()
{
    if(music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
        
}

void IntroAudio::stop()
{
    music.stop();
}