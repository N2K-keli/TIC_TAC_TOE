#pragma once
#include <iostream>
#include <string>
#include "Arrow.hpp"
#include "TextHelper.hpp"
#include "AudioManager.hpp"

class MenuScene
{
public:
	void drawMenu(sf::RenderWindow& window);
    void updateMenuIndex(const sf::Event& event , AudioManager& audio);
    int selectedIndex = 0;
    bool shouldExit = false;
    


private:
    bool showExitConfirm = false; 
    int confirmIndex = 0;         


    TextHelper newGame{ "NEW GAME",   {300.f, 200.f}, 60 };
    TextHelper continueGame{ "CONTINUE", {300.f, 260.f}, 60 };
    TextHelper options{ "OPTIONS",   {300.f, 320.f}, 60 };
    TextHelper exit{ "EXIT",         {300.f, 380.f}, 60 };

    TextHelper confirmText{ "ARE YOU SURE YOU WANT TO QUIT?", {100.f, 180.f}, 35 };
    TextHelper yesText{ "YES", {300.f, 280.f}, 60 };
    TextHelper noText{ "NO",  {300.f, 340.f}, 60 };

    Arrow arrow{ {250.f, 235.f} };


};

