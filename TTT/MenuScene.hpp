#pragma once
#include <iostream>
#include <string>
#include "Arrow.hpp"
#include "TextHelper.hpp"

class MenuScene
{
public:
	void drawMenu(sf::RenderWindow& window);
    


private:
    TextHelper newGame{ "NEW GAME",   {300.f, 200.f}, 60 };
    TextHelper continueGame{ "CONTINUE", {300.f, 260.f}, 60 };
    TextHelper options{ "OPTIONS",   {300.f, 320.f}, 60 };
    TextHelper exit{ "EXIT",         {300.f, 380.f}, 60 };
    Arrow arrow{ {250.f, 235.f} };


};

