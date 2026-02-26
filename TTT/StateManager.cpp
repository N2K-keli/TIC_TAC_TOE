#include <iostream>
#include <chrono>
#include <thread>
#include "StateManager.hpp"


;

// attributes


// condtructor 

StateManager::StateManager()
{
	this->currentSceneState  = SceneState::intro;
}

//methods
 


void StateManager::setcurrentSceneState(SceneState state)
{
	this->currentSceneState = state;
}
SceneState StateManager::getcurrentSceneState()
{
	return this->currentSceneState; 
}
