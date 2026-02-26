#pragma once
#include<SFML\Audio.hpp>
#include"IntroAudio.hpp"

class AudioManager
{
public:
	AudioManager(IntroAudio& intro_audio);
	IntroAudio& getIntroAudio();
	
private:
	IntroAudio& introAudio;
	
};

