#include "MenuScene.hpp"
#include "NavigationHelper.hpp"

void MenuScene::drawMenu(sf::RenderWindow& window)
{
    if (showExitConfirm)
    {
        yesText.getText().setFillColor(sf::Color::White);
        noText.getText().setFillColor(sf::Color::White);

        
        if (confirmIndex == 0) 
        {
            yesText.getText().setFillColor(sf::Color::Yellow);
        }
        else 
        {
            noText.getText().setFillColor(sf::Color::Yellow);
        }

        confirmText.draw(window);
        yesText.draw(window);
        noText.draw(window);

        
        float arrowY = 280.f + (confirmIndex * 60.f) + 35.f;
        arrow.getArrowSprite().setPosition({ 250.f, arrowY });
        window.draw(arrow.getArrowSprite());
    }
    else
    {
        
        newGame.getText().setFillColor(sf::Color::White);
        continueGame.getText().setFillColor(sf::Color::White);
        options.getText().setFillColor(sf::Color::White);
        exit.getText().setFillColor(sf::Color::White);

       
        switch (selectedIndex)
        {
        case 0: newGame.getText().setFillColor(sf::Color::Yellow);      break;
        case 1: continueGame.getText().setFillColor(sf::Color::Yellow); break;
        case 2: options.getText().setFillColor(sf::Color::Yellow);      break;
        case 3: exit.getText().setFillColor(sf::Color::Yellow);         break;
        }

        newGame.draw(window);
        continueGame.draw(window);
        options.draw(window);
        exit.draw(window);

        float arrowY = 200.f + (selectedIndex * 60.f) + 35.f;
        arrow.getArrowSprite().setPosition({ 250.f, arrowY });
        window.draw(arrow.getArrowSprite());
    }

    window.display();
}

void MenuScene::updateMenuIndex(const sf::Event& event, AudioManager& audio)
{
    if (!event.is<sf::Event::KeyPressed>()) return;
    auto* key = event.getIf<sf::Event::KeyPressed>();

    if (showExitConfirm)
    {
        if (key->scancode == sf::Keyboard::Scancode::Up || key->scancode == sf::Keyboard::Scancode::Down)
        {
            confirmIndex = (confirmIndex == 0) ? 1 : 0;
            audio.getMenuAudio().arrowNavigationPlay();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter)
        {
            audio.getMenuAudio().arrowEnterPlay();
            if (confirmIndex == 0) shouldExit = true;  
            else
            {
                showExitConfirm = false; 
                confirmIndex = 0;
            }
        }
    }
    else
    {
        selectedIndex = NavigationHelper::moveUpDown(event, selectedIndex, 4, audio.getMenuAudio());

        if (key->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (selectedIndex == 2) // OPTIONS
            {
                audio.getMenuAudio().arrowEnterPlay();
                goToOptions = true;
            }
            else if (selectedIndex == 3) // EXIT
            {
                audio.getMenuAudio().arrowEnterPlay();
                showExitConfirm = true;
                confirmIndex = 0;
            }
        }
    }
}