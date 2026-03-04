#pragma once 
#include <iostream>
#include <SFML\Graphics.hpp>
#include "IntroScene.hpp"
#include "MenuScene.hpp"
#include "OptionsScene.hpp" 
#include "Level1Scene.hpp"
#include "Level2Scene.hpp"
#include "Level3Scene.hpp"
#include "Level4Scene.hpp"
#include "Level5Scene.hpp"
#include "Level6Scene.hpp"

class SceneManager
{
public:
	
	SceneManager(sf::RenderWindow& window , IntroScene introscene);

	IntroScene& getIntroScene();
	MenuScene& getMenuScene();
	OptionsScene& getOptionsScene();
	Level1Scene& getLevel1Scene();
	Level2Scene& getLevel2Scene();
	Level3Scene& getLevel3Scene();
	Level4Scene& getLevel4Scene();
	Level5Scene& getLevel5Scene();
	Level6Scene& getLevel6Scene();

	sf::RenderWindow& getWindow();

private:
	
	
	IntroScene introScene;
	MenuScene menuScene;
	OptionsScene optionsScene;
	Level1Scene  level1Scene;
	Level2Scene  level2Scene;
	Level3Scene  level3Scene;
	Level4Scene  level4Scene;
	Level5Scene  level5Scene;
	Level6Scene  level6Scene;
	sf::RenderWindow& window;
	
};
