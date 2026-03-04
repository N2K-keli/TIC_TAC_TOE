#include "Level1GameAudio.hpp"

Level1GameAudio::Level1GameAudio()
{
    if (!music.openFromFile("assets/audio/level1game.mp3"))
    {
        std::cerr << "Error: Could not load level 1 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 1 game audio loaded!\n";
    }
    music.setLooping(true); 
}

void Level1GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level1GameAudio::stop()
{
    music.stop();
}