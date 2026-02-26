#pragma once
#include <SFML/Audio.hpp>

class MenuAudio
{
public:
	MenuAudio();
	void play();
	void stop();

private:
	sf::Music music;
};

