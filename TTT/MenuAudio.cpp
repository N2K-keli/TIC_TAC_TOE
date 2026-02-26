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