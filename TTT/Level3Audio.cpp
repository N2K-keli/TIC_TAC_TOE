#include "Level3Audio.hpp"

Level3Audio::Level3Audio()
{
    if (!music.openFromFile("assets/audio/level3intro.mp3"))
    {
        std::cerr << "Error: Could not load level 3 audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 3 audio loaded!\n";
    }
    music.setLooping(false);
}

void Level3Audio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level3Audio::stop()
{
    music.stop();
}

bool Level3Audio::isFinished()
{
    return music.getStatus() == sf::Music::Status::Stopped;
}