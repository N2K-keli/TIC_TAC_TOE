#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>

int main() 
{
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u{800, 600}), "TIC TAC TOE");
	
	while (window.isOpen())
	{
	
		while( std::optional<sf::Event> event = window.pollEvent()) 
		{
			if( (*event).is<sf::Event::Closed>() )
			{
				window.close();
			}
		}
		
		window.clear();
		window.display();
	}
	

	return 0;
}