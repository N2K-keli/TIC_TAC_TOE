#pragma once
#include <SFML\Graphics.hpp>

class IntroScene
{
public:
	IntroScene(sf::RenderWindow& window);
	void LoadIntro(sf::RenderWindow& window);

private:
	sf::Texture logo;
	std::optional<sf::Sprite> logoSprite;

};
