#pragma once
#include<SFML\Audio.hpp>
#include"IntroAudio.hpp"
#include"MenuAudio.hpp"
#include "Level1Audio.hpp"
#include "Level2Audio.hpp"
#include "Level3Audio.hpp"
#include "Level4Audio.hpp"
#include "Level5Audio.hpp"
#include "Level6Audio.hpp"

class AudioManager
{
public:
	IntroAudio& getIntroAudio();
	MenuAudio& getMenuAudio();
	Level1Audio& getLevel1Audio();
	Level2Audio& getLevel2Audio();
	Level3Audio& getLevel3Audio();
	Level4Audio& getLevel4Audio();
	Level5Audio& getLevel5Audio();
	Level6Audio& getLevel6Audio();

	
	
private:
	IntroAudio introAudio;
	MenuAudio menuAudio; 
	Level1Audio level1Audio;
	Level2Audio level2Audio;
	Level3Audio level3Audio;
	Level4Audio level4Audio;
	Level5Audio level5Audio;
	Level6Audio level6Audio;
	
};

