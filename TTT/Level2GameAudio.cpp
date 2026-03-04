#include "Level2GameAudio.hpp"

Level2GameAudio::Level2GameAudio()
{
    if (!music.openFromFile("assets/audio/level2game.mp3"))
    {
        std::cerr << "Error: Could not load level 2 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 2 game audio loaded!\n";
    }
    music.setLooping(true);
}

void Level2GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level2GameAudio::stop()
{
    music.stop();
}