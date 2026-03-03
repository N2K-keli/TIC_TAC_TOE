#pragma once 
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IntroScene.hpp"
#include "MenuScene.hpp"
#include "OptionsScene.hpp" 

class SceneManager
{
public:
	
	SceneManager(sf::RenderWindow& window , IntroScene introscene);

	IntroScene& getIntroScene();
	MenuScene& getMenuScene();
	OptionsScene& getOptionsScene();

private:
	
	
	IntroScene introScene;
	MenuScene menuScene;
	OptionsScene optionsScene;
	
};
