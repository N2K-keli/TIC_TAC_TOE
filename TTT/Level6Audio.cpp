#include "Level6Audio.hpp"

Level6Audio::Level6Audio()
{
    if (!music.openFromFile("assets/audio/level6intro.mp3"))
    {
        std::cerr << "Error: Could not load level 6 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 6 audio loaded!\n";
    }
    music.setLooping(false);
}

void Level6Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level6Audio::stop()
{
    music.stop();
}

bool Level6Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped;
}