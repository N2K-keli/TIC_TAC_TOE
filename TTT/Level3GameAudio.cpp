#include "Level3GameAudio.hpp"

Level3GameAudio::Level3GameAudio()
{
    if (!music.openFromFile("assets/audio/level3game.mp3"))
    {
        std::cerr << "Error: Could not load level 3 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 3 game audio loaded!\n";
    }
    music.setLooping(true);
}

void Level3GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level3GameAudio::stop()
{
    music.stop();
}