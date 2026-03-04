#pragma once
#include"AudioManager.hpp"


IntroAudio& AudioManager::getIntroAudio()
{
	return introAudio;
}
MenuAudio& AudioManager::getMenuAudio() 
{
	return menuAudio;
}
Level1Audio& AudioManager::getLevel1Audio() { return level1Audio; }
Level2Audio& AudioManager::getLevel2Audio() { return level2Audio; }
Level3Audio& AudioManager::getLevel3Audio() { return level3Audio; }
Level4Audio& AudioManager::getLevel4Audio() { return level4Audio; }
Level5Audio& AudioManager::getLevel5Audio() { return level5Audio; }
Level6Audio& AudioManager::getLevel6Audio() { return level6Audio; }
Level1GameAudio& AudioManager::getLevel1GameAudio() { return level1GameAudio; }
Level2GameAudio& AudioManager::getLevel2GameAudio() { return level2GameAudio; }
Level3GameAudio& AudioManager::getLevel3GameAudio() { return level3GameAudio; }
Level4GameAudio& AudioManager::getLevel4GameAudio() { return level4GameAudio; }
Level5GameAudio& AudioManager::getLevel5GameAudio() { return level5GameAudio; }
Level6GameAudio& AudioManager::getLevel6GameAudio() { return level6GameAudio; }
GameWinAudio& AudioManager::getGameWinAudio() { return gameWinAudio; }
GameLoseAudio& AudioManager::getGameLoseAudio() { return gameLoseAudio; }
GameDrawAudio& AudioManager::getGameDrawAudio() { return gameDrawAudio; }