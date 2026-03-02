#pragma once 
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IntroScene.hpp"
#include "MenuScene.hpp"


class SceneManager
{
public:
	
	SceneManager(sf::RenderWindow& window , IntroScene introscene);

	IntroScene& getIntroScene();
	MenuScene& getMenuScene();

private:
	
	
	IntroScene introScene;
	MenuScene menuScene;
	
};
