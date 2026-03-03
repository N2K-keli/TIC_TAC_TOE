#pragma once
#include <SFML/Audio.hpp>

class MenuAudio
{
public:
	MenuAudio();
	void play();
	void stop();
	void arrowNavigationPlay();
	void arrowNavigationStop();
	void arrowEnterPlay();
	void arrowEnterStop();

private:
	sf::Music music;
	sf::Music arrowNavigation;
	sf::Music arrowEnter;
};

