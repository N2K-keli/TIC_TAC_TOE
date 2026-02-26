#pragma once
#include<SFML\Audio.hpp>
#include"IntroAudio.hpp"
#include"MenuAudio.hpp"

class AudioManager
{
public:
	IntroAudio& getIntroAudio();
	MenuAudio& getMenuAudio();
	
	
private:
	IntroAudio introAudio;
	MenuAudio menuAudio; 
	
};

