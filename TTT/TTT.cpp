#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "StateManager.hpp"
#include <filesystem>
#include "SceneManager.hpp"
#include <SFML/Config.hpp>



int main() 
{

	Board chessBoard; // board CehssBoard =  new board () ;
	// StateManager stateMnagerObgject; 
	
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u{800, 600}), "TIC TAC TOE");
	SceneManager sceneManagerObject(window);
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
		sceneManagerObject.LoadIntro(window);
		sceneManagerObject.LoadMenu(window);
		// window.display();
		
		// sceneManagerObject.LoadIntro(window);
		// std::cout << std::filesystem::current_path() << std::endl;
	}

	return 0;
}