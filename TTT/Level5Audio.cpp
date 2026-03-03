#include "Level5Audio.hpp"

Level5Audio::Level5Audio()
{
    if (!music.openFromFile("assets/audio/level5intro.mp3"))
    {
        std::cerr << "Error: Could not load level 5 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 5 audio loaded!\n";
    }
    music.setLooping(false);
}

void Level5Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level5Audio::stop()
{
    music.stop();
}

bool Level5Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped;
}