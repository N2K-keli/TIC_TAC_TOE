#include <iostream>
#include <chrono>
#include <thread>
#include "SceneManager.hpp"
#include <filesystem>
#include <vector>
#include <SFML\Window\Keyboard.hpp>
using namespace std::chrono_literals;
// constructor
SceneManager::SceneManager(sf::RenderWindow& window, IntroScene introscene): introScene(introscene)  
{
}

IntroScene SceneManager::getIntroScene()
{
    return introScene;
}

MenuScene SceneManager::getMenuScene()
{
    return menuScene;
}
