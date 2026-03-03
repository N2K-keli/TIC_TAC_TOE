#include <iostream>
#include "MenuAudio.hpp"

MenuAudio::MenuAudio()
{
    if (!music.openFromFile("assets/audio/menu.mp3"))
    {
        std::cerr << "Error: Could not menu intro music\n";
    }
    else
    {
        std::cout << "SUCCESS! Menu music loaded!\n";
    }

    music.setLooping(true);

    if (!arrowNavigation.openFromFile("assets/audio/arrowNavigation.mp3"))
    {
        std::cerr << "Error: Could not load arrowNavigation intro music\n";
    }
    else
    {
        std::cout << "SUCCESS! arrowNavigation music loaded!\n";
    }

    arrowNavigation.setLooping(false);

    if (!arrowEnter.openFromFile("assets/audio/arrowEnter.mp3"))
        {
            std::cerr << "Error: Could not load arrowEnter music\n";
        }
    else
        {
            std::cout << "SUCCESS! arrowEnter music loaded!\n";
        }

        arrowEnter.setLooping(false);
    }

void MenuAudio::play() 
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
       
}
void MenuAudio::stop()
{
    music.stop();
    
}

void MenuAudio::arrowEnterPlay()
{
    arrowEnter.play(); 
}

void MenuAudio::arrowEnterStop()
{
    arrowEnter.stop();
}

void MenuAudio::arrowNavigationPlay()
{
    arrowNavigation.play();
}

void MenuAudio::arrowNavigationStop()
{
    arrowNavigation.stop();
}

void MenuAudio::setMusicVolume(float volume)
{
    music.setVolume(volume);
}
void MenuAudio::setSFXVolume(float volume)
{
    arrowNavigation.setVolume(volume);
    arrowEnter.setVolume(volume);
}
