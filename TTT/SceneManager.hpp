#pragma once 
#include <iostream>
#include <SFML\Graphics.hpp>


class SceneManager
{
public:
	SceneManager(sf::RenderWindow& window);
	void LoadIntro(sf::RenderWindow& window);
	

private:
	sf::Texture logo;
	std::optional<sf::Sprite> logoSprite;

	
	
};
