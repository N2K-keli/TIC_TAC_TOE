#include "Level6GameAudio.hpp"

Level6GameAudio::Level6GameAudio()
{
    if (!music.openFromFile("assets/audio/level6game.mp3"))
    {
        std::cerr << "Error: Could not load level 6 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 6 game audio loaded!\n";
    }
    music.setLooping(true);
}

void Level6GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level6GameAudio::stop()
{
    music.stop();
}