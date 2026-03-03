#include "OptionsScene.hpp"
#include <string>

void OptionsScene::drawOptions(sf::RenderWindow& window)
{
    musicVolumeText.getText().setFillColor(sf::Color::White);
    sfxVolumeText.getText().setFillColor(sf::Color::White);
    backText.getText().setFillColor(sf::Color::White);

    switch (selectedIndex)
    {
    case 0: musicVolumeText.getText().setFillColor(sf::Color::Yellow); break;
    case 1: sfxVolumeText.getText().setFillColor(sf::Color::Yellow);   break;
    case 2: backText.getText().setFillColor(sf::Color::Yellow);        break;
    }

    // Update text to show current volume values
    musicVolumeText.getText().setString("MUSIC VOLUME : " + std::to_string((int)musicVolume));
    sfxVolumeText.getText().setString("SFX VOLUME   : " + std::to_string((int)sfxVolume));

    musicVolumeText.draw(window);
    sfxVolumeText.draw(window);
    backText.draw(window);

    float arrowY = 200.f + (selectedIndex * 60.f) + 35.f;
    arrow.getArrowSprite().setPosition({ 250.f, arrowY });
    window.draw(arrow.getArrowSprite());

    window.display();
}

void OptionsScene::updateOptionIndex(const sf::Event& event, AudioManager& audio)
{
    if (!event.is<sf::Event::KeyPressed>()) return;
    auto* key = event.getIf<sf::Event::KeyPressed>();

    if (key->scancode == sf::Keyboard::Scancode::Up)
    {
        selectedIndex = selectedIndex - 1;
        if (selectedIndex < 0) selectedIndex = 2; // wrap to BACK
        audio.getMenuAudio().arrowNavigationPlay();
    }
    else if (key->scancode == sf::Keyboard::Scancode::Down)
    {
        selectedIndex = selectedIndex + 1;
        if (selectedIndex > 2) selectedIndex = 0; // wrap to MUSIC VOLUME
        audio.getMenuAudio().arrowNavigationPlay();
    }
    else if (key->scancode == sf::Keyboard::Scancode::Left)
    {
        // Decrease volume of selected option
        if (selectedIndex == 0)
        {
            musicVolume = std::max(0.f, musicVolume - 10.f);
            audio.getMenuAudio().setMusicVolume(musicVolume); 
        }
        else if (selectedIndex == 1)
        {
            sfxVolume = std::max(0.f, sfxVolume - 10.f);
            audio.getMenuAudio().setSFXVolume(sfxVolume);     
        }
    }
    else if (key->scancode == sf::Keyboard::Scancode::Right)
    {
        // Increase volume of selected option
        if (selectedIndex == 0)
        {
            musicVolume = std::min(100.f, musicVolume + 10.f);
            audio.getMenuAudio().setMusicVolume(musicVolume);
        }
        else if (selectedIndex == 1)
        {
            sfxVolume = std::min(100.f, sfxVolume + 10.f);
            audio.getMenuAudio().setSFXVolume(sfxVolume);
        }
    }
    else if (key->scancode == sf::Keyboard::Scancode::Enter)
    {
        if (selectedIndex == 2) // BACK
        {
            audio.getMenuAudio().arrowEnterPlay();
            goBack = true; //  signal main to return to menu
        }
    }
}