#include "Level4Audio.hpp"

Level4Audio::Level4Audio()
{
    if (!music.openFromFile("assets/audio/level4intro.mp3"))
    {
        std::cerr << "Error: Could not load level 4 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 4 audio loaded!\n";
    }
    music.setLooping(false);
}

void Level4Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level4Audio::stop()
{
    music.stop();
}

bool Level4Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped;
}