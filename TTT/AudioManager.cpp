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