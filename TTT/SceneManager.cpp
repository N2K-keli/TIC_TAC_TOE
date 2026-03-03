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

IntroScene& SceneManager::getIntroScene()
{
    return introScene;
}

MenuScene& SceneManager::getMenuScene()
{
    return menuScene;
}
OptionsScene& SceneManager::getOptionsScene()
{
    return optionsScene;
}
Level1Scene& SceneManager::getLevel1Scene() { return level1Scene; }
Level2Scene& SceneManager::getLevel2Scene() { return level2Scene; }
Level3Scene& SceneManager::getLevel3Scene() { return level3Scene; }
Level4Scene& SceneManager::getLevel4Scene() { return level4Scene; }
Level5Scene& SceneManager::getLevel5Scene() { return level5Scene; }
Level6Scene& SceneManager::getLevel6Scene() { return level6Scene; }