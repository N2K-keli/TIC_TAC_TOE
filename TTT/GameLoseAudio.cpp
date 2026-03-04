#include "GameLoseAudio.hpp"

GameLoseAudio::GameLoseAudio()
{
    if (!music.openFromFile("assets/audio/gamelose.mp3"))
        std::cerr << "Error: Could not load game lose audio\n";
    else
        std::cout << "SUCCESS! Game lose audio loaded!\n";
    music.setLooping(false);
}

void GameLoseAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
        music.play();
}

void GameLoseAudio::stop()
{
    music.stop();
}