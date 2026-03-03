#include "Level2Audio.hpp"

Level2Audio::Level2Audio()
{
    if (!music.openFromFile("assets/audio/level2intro.mp3"))
    {
        std::cerr << "Error: Could not load level 2 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 2 audio loaded!\n";
    }
    music.setLooping(false); 
}

void Level2Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level2Audio::stop()
{
    music.stop();
}

bool Level2Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped; 
}