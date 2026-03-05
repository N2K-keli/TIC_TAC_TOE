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
		SceneState returnLevel = SceneState::level1;
		


	public:
		StateManager(); 
		void setcurrentSceneState(SceneState state);
		SceneState getcurrentSceneState();
		void setReturnLevel(SceneState state);
		SceneState getReturnLevel() const;
		
	
};


