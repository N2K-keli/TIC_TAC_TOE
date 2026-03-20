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
    void resetFlags();
    int selectedIndex = 0;
    bool shouldExit = false;
    bool goToOptions = false;

    bool goToLevel1 = false;
    bool goToLevel2 = false;
    bool goToLevel3 = false;
    bool goToLevel4 = false;
    bool goToLevel5 = false;
    bool goToLevel6 = false;
    bool goToContinue = false; 
    


private:
    bool showExitConfirm = false; 
    int confirmIndex = 0;       

    bool showLevelSelect = false; 
    int  levelSelectIndex = 0;


    TextHelper newGame{ "NEW GAME",   {300.f, 200.f}, 60 };
    TextHelper continueGame{ "CONTINUE", {300.f, 260.f}, 60 };
    TextHelper options{ "OPTIONS",   {300.f, 320.f}, 60 };
    TextHelper exit{ "EXIT",         {300.f, 380.f}, 60 };

    TextHelper confirmText{ "ARE YOU SURE YOU WANT TO QUIT?", {100.f, 180.f}, 35 };
    TextHelper yesText{ "YES", {300.f, 280.f}, 60 };
    TextHelper noText{ "NO",  {300.f, 340.f}, 60 };

    TextHelper level1Text{ "LEVEL 1", {300.f, 100.f}, 50 };
    TextHelper level2Text{ "LEVEL 2", {300.f, 155.f}, 50 };
    TextHelper level3Text{ "LEVEL 3", {300.f, 210.f}, 50 };
    TextHelper level4Text{ "LEVEL 4", {300.f, 265.f}, 50 };
    TextHelper level5Text{ "LEVEL 5", {300.f, 320.f}, 50 };
    TextHelper level6Text{ "LEVEL 6", {300.f, 375.f}, 50 };
    TextHelper backLevel{ "BACK",    {300.f, 430.f}, 50 };


    Arrow arrow{ {250.f, 235.f} };


};

