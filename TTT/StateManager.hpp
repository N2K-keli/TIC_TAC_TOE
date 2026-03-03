#pragma once 
#include <SFML\Graphics.hpp>
#include <string>


enum SceneState 
{
	intro, 
	menu , 
	options,

};

class StateManager
{


	private:
		SceneState currentSceneState; 
		


	public:
		StateManager(); 
		void setcurrentSceneState(SceneState state);
		SceneState getcurrentSceneState();
		
	
};


