#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "StateManager.hpp"
#include <filesystem>
#include "SceneManager.hpp"
#include <SFML/Config.hpp>
#include "IntroScene.hpp"
#include"AudioManager.hpp"
#include "IntroAudio.hpp"
#include "MenuScene.hpp"


int main() 
{
	Board chessBoard; 
	// StateManager stateMnagerObgject; 
	sf::RenderWindow window(sf::VideoMode(sf::Vector2u{800, 600}), "TIC TAC TOE");
	IntroScene introSceneObject(window);
	SceneManager sceneManagerObject(window, introSceneObject);
	StateManager stateManagerObject;
	AudioManager audioManagerObject;
	
	while (window.isOpen())
	{
		
	
		while(std::optional<sf::Event> event = window.pollEvent())
		{
			if( (*event).is<sf::Event::Closed>() )
			{
				window.close();
			}
			if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
			{
				sceneManagerObject.getMenuScene().updateMenuIndex(*event, audioManagerObject);
			}
			
		
		}
		

		if(stateManagerObject.getcurrentSceneState() == SceneState::intro)
		{
			audioManagerObject.getIntroAudio().play();
			sceneManagerObject.getIntroScene().LoadIntro(window);
			window.clear();
			stateManagerObject.setcurrentSceneState(SceneState::menu);
			

		}


		if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
		{
			audioManagerObject.getMenuAudio().play();
			window.clear();
			sceneManagerObject.getMenuScene().drawMenu(window);
			if (sceneManagerObject.getMenuScene().shouldExit) 
			{
				audioManagerObject.getMenuAudio().stop();    
				audioManagerObject.getIntroAudio().stop();
				window.close();
			}
			

		}
		
	}

	return 0;
}