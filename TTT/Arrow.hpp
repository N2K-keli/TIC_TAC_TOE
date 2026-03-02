#pragma once
#include <SFML/Graphics.hpp>

class Arrow
{
public:
	Arrow(sf::Vector2f position);
	sf::Sprite& getArrowSprite();
	

private:
	sf::Texture arrow;
	std::optional<sf::Sprite> arrowSprite;
	
};

