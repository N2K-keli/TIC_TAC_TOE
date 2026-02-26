#pragma once
#include<SFML\Audio.hpp>
#include"IntroAudio.hpp"
#include"MenuAudio.hpp"

class AudioManager
{
public:
	AudioManager(IntroAudio& intro_audio);
	IntroAudio& getIntroAudio();
	MenuAudio& getMenuAudio();
	
	
private:
	IntroAudio& introAudio;
	MenuAudio menuAudio; 
	
};

