#pragma once 
#include <SFML\Graphics.hpp>
#include <string>

enum GameState
{
	
	intro,
	shutdowm

};

class StateManager
{


	private:
		GameState state; 
		


	public:
		StateManager(); 
		void setState(GameState state);
		GameState getState();
		
		
};


