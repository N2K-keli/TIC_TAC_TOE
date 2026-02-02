#include <iostream>
#include <chrono>
#include <thread>
#include "StateManager.hpp"


;

// attributes


// condtructor 

StateManager::StateManager()
{
	this->state  = GameState::intro;
}

//methods
 


void StateManager::setState(GameState state)
{
	this->state = state;
}
GameState StateManager::getState() 
{
	return this->state; 
}
