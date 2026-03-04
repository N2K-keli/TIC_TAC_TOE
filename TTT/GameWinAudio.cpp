#include "GameWinAudio.hpp"

GameWinAudio::GameWinAudio()
{
    if (!music.openFromFile("assets/audio/gamewin.mp3"))
        std::cerr << "Error: Could not load game win audio\n";
    else
        std::cout << "SUCCESS! Game win audio loaded!\n";
    music.setLooping(false);
}

void GameWinAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
        music.play();
}

void GameWinAudio::stop()
{
    music.stop();
}