#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "StateManager.hpp"


int main() 
{
	Board chessBoard; // board CehssBoard =  new board () ;
	StateManager stateMnagerObgject; 
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
		
		// chessBoard.worrkingBoard();
		
		
		window.clear();
		window.display();
	    stateMnagerObgject.LoadIntro();
		

	}
		std::cout << "the state is : " << stateMnagerObgject.getState();

	return 0;
}