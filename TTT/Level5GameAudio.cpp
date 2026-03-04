#include "Level5GameAudio.hpp"

Level5GameAudio::Level5GameAudio()
{
    if (!music.openFromFile("assets/audio/level5game.mp3"))
    {
        std::cerr << "Error: Could not load level 5 game audio\n";
    }
    else
    {
        std::cout << "SUCCESS! Level 5 game audio loaded!\n";
    }
    music.setLooping(true);
}

void Level5GameAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
    {
        music.play();
    }
}

void Level5GameAudio::stop()
{
    music.stop();
}