#include "GameDrawAudio.hpp"

GameDrawAudio::GameDrawAudio()
{
    if (!music.openFromFile("assets/audio/gamedraw.mp3"))
        std::cerr << "Error: Could not load game draw audio\n";
    else
        std::cout << "SUCCESS! Game draw audio loaded!\n";
    music.setLooping(false);
}

void GameDrawAudio::play()
{
    if (music.getStatus() != sf::Music::Status::Playing)
        music.play();
}

void GameDrawAudio::stop()
{
    music.stop();
}