#pragma once
#include"AudioManager.hpp"

AudioManager::AudioManager(IntroAudio& intro_audio): introAudio(intro_audio)
{}

IntroAudio& AudioManager::getIntroAudio()
{
	return introAudio;
}