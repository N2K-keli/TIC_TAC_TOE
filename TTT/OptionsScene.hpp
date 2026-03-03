#pragma once
#include <iostream>
#include <string>
#include "Arrow.hpp"
#include "TextHelper.hpp"
#include "AudioManager.hpp"

class OptionsScene
{
public:
    void drawOptions(sf::RenderWindow& window);
    void updateOptionIndex(const sf::Event& event, AudioManager& audio);
    bool goBack = false;

private:
    int selectedIndex = 0; // 0=Music Volume, 1=SFX Volume, 2=Back
    float musicVolume = 50.f;  // 0 to 100
    float sfxVolume = 50.f;  // 0 to 100

    TextHelper musicVolumeText{ "MUSIC VOLUME",  {300.f, 200.f}, 60 };
    TextHelper sfxVolumeText{ "SFX VOLUME",    {300.f, 260.f}, 60 };
    TextHelper backText{ "BACK",           {300.f, 320.f}, 60 };

    Arrow arrow{ {250.f, 235.f} };
};