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
#include "Level1GameAudio.hpp"
#include "Level2GameAudio.hpp"
#include "Level3GameAudio.hpp"
#include "Level4GameAudio.hpp"
#include "Level5GameAudio.hpp"
#include "Level6GameAudio.hpp"

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
	Level1GameAudio& getLevel1GameAudio();
	Level2GameAudio& getLevel2GameAudio();
	Level3GameAudio& getLevel3GameAudio();
	Level4GameAudio& getLevel4GameAudio();
	Level5GameAudio& getLevel5GameAudio();
	Level6GameAudio& getLevel6GameAudio();

	
	
private:
	IntroAudio introAudio;
	MenuAudio menuAudio; 
	Level1Audio level1Audio;
	Level2Audio level2Audio;
	Level3Audio level3Audio;
	Level4Audio level4Audio;
	Level5Audio level5Audio;
	Level6Audio level6Audio;
	Level1GameAudio level1GameAudio;
	Level2GameAudio level2GameAudio;
	Level3GameAudio level3GameAudio;
	Level4GameAudio level4GameAudio;
	Level5GameAudio level5GameAudio;
	Level6GameAudio level6GameAudio;
	
};

