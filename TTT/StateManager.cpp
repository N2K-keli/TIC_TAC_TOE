#include <iostream>
#include <chrono>
#include <thread>
#include "StateManager.hpp"


using namespace std::chrono_literals;

// attributes


// condtructor 

StateManager::StateManager()
{
	this->state  = GameState::intro;
}
//methods
void StateManager::LoadIntro() 
{
	if (this->getState() == GameState::intro)
	{
		std::cout << "the intro is happening" << std::endl;
		std::this_thread::sleep_for(10000ms);
		std::cout << "the intro is over" << std::endl;
		this->setState(GameState::shutdowm);
	}	 
}

void StateManager::setState(GameState state)
{
	this->state = state;
}
GameState StateManager::getState() 
{
	return this->state; 
}
