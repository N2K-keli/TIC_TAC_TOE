#pragma once 
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IntroScene.hpp"


class SceneManager
{
public:
	
	SceneManager(sf::RenderWindow& window , IntroScene introscene);

	IntroScene getIntroScene();

private:
	
	
	IntroScene introScene;
	
};
