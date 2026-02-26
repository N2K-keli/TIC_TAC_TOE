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