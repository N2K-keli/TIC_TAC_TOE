#pragma once 
#include <SFML\Graphics.hpp>
#include <string>


enum SceneState 
{
	intro,
	menu,
	gameOver,
	options,
	level1,
	level2,
	level3,
	level4,
	level5,
	level6,

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


