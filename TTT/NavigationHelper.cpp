#include "NavigationHelper.hpp"



AudioManager& NavigationHelper::getAudio() 
{
	return audio;
}

int NavigationHelper::moveUpDown( const sf::Event& event, int currentIndex, int maxIndex , MenuAudio& audio)
{
	if(event.is<sf::Event::KeyPressed>()) 
	{
		
		auto* key = event.getIf<sf::Event::KeyPressed>(); 

		if(key->scancode == sf::Keyboard::Scancode::Up) 
		{
			
			currentIndex = currentIndex - 1;
			
			if(currentIndex < 0 ) 
			{
				currentIndex = 0;
			}
			audio.arrowNavigationPlay();
		}else if (key->scancode  == sf::Keyboard::Scancode::Down) 
		{
			currentIndex = currentIndex + 1; 
			if(currentIndex >= maxIndex) 
			{
				currentIndex = 0; 
			}
			audio.arrowNavigationPlay();
		
		}
		else if (key->scancode == sf::Keyboard::Scancode::Enter) // ? separate block
		{
			audio.arrowEnterPlay(); 
		}
		
	}


	return currentIndex; 
}