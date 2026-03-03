#include "Level1Audio.hpp"

Level1Audio::Level1Audio()
{
    if (!music.openFromFile("assets/audio/level1intro.mp3"))
    {
        std::cerr << "Error: Could not load level 1 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 1 audio loaded!\n";
    }
    music.setLooping(false); 
}

void Level1Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level1Audio::stop()
{
    music.stop();
}

bool Level1Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped; 
}