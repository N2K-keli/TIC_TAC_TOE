#include "Level4GameAudio.hpp"

Level4GameAudio::Level4GameAudio()
{
    if (!music.openFromFile("assets/audio/level4game.mp3"))
    {
        std::cerr << "Error: Could not load level 4 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 4 game audio loaded!\n";
    }
    music.setLooping(true);
}

void Level4GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level4GameAudio::stop()
{
    music.stop();
}