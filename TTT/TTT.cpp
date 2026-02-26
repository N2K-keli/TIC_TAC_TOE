#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "StateManager.hpp"
#include <filesystem>
#include "SceneManager.hpp"
#include <SFML/Config.hpp>
#include "IntroScene.hpp"



int main() 
{
	Board chessBoard; 
	// StateManager stateMnagerObgject; 
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u{800, 600}), "TIC TAC TOE");
	IntroScene introSceneObject(window);
	SceneManager sceneManagerObject(window, introSceneObject);
	StateManager stateManagerObject;

	while (window.isOpen())
	{
		
	
		while(std::optional<sf::Event> event = window.pollEvent())
		{
			if( (*event).is<sf::Event::Closed>() )
			{
				window.close();
			}
			
		
		}
		

		if(stateManagerObject.getcurrentSceneState() == SceneState::intro)
		{
			sceneManagerObject.getIntroScene().LoadIntro(window);

		}
		
	}

	return 0;
}