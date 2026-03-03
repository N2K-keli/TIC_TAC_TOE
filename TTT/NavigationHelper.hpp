#pragma once
#include <SFML/Audio.hpp>
#include <SFML\Graphics.hpp>
#include "AudioManager.hpp"
class NavigationHelper
{
public:
	static int moveUpDown(const sf::Event& event , int currentIndex , int maxIndex , MenuAudio& audio);
	AudioManager& getAudio();

private:
	AudioManager audio;

};

