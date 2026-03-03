#include "MenuScene.hpp"
#include "NavigationHelper.hpp"

void MenuScene::drawMenu(sf::RenderWindow& window)
{
    if (showExitConfirm)
    {
        yesText.getText().setFillColor(sf::Color::White);
        noText.getText().setFillColor(sf::Color::White);

        if (confirmIndex == 0) yesText.getText().setFillColor(sf::Color::Yellow);
        else                   noText.getText().setFillColor(sf::Color::Yellow);

        confirmText.draw(window);
        yesText.draw(window);
        noText.draw(window);

        float arrowY = 280.f + (confirmIndex * 60.f) + 35.f;
        arrow.getArrowSprite().setPosition({ 250.f, arrowY });
        window.draw(arrow.getArrowSprite());
    }
    else if (showLevelSelect) //  level select sub-screen
    {
        // reset all to white
        level1Text.getText().setFillColor(sf::Color::White);
        level2Text.getText().setFillColor(sf::Color::White);
        level3Text.getText().setFillColor(sf::Color::White);
        level4Text.getText().setFillColor(sf::Color::White);
        level5Text.getText().setFillColor(sf::Color::White);
        level6Text.getText().setFillColor(sf::Color::White);
        backLevel.getText().setFillColor(sf::Color::White);

        // highlight selected yellow
        switch (levelSelectIndex)
        {
        case 0: level1Text.getText().setFillColor(sf::Color::Yellow); break;
        case 1: level2Text.getText().setFillColor(sf::Color::Yellow); break;
        case 2: level3Text.getText().setFillColor(sf::Color::Yellow); break;
        case 3: level4Text.getText().setFillColor(sf::Color::Yellow); break;
        case 4: level5Text.getText().setFillColor(sf::Color::Yellow); break;
        case 5: level6Text.getText().setFillColor(sf::Color::Yellow); break;
        case 6: backLevel.getText().setFillColor(sf::Color::Yellow);  break;
        }

        level1Text.draw(window);
        level2Text.draw(window);
        level3Text.draw(window);
        level4Text.draw(window);
        level5Text.draw(window);
        level6Text.draw(window);
        backLevel.draw(window);

        // arrow spacing matches TextHelper positions (55.f per item from 100.f base)
        float arrowY = 100.f + (levelSelectIndex * 55.f) + 25.f;
        arrow.getArrowSprite().setPosition({ 250.f, arrowY });
        window.draw(arrow.getArrowSprite());
    }
    else // main menu
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
        if (key->scancode == sf::Keyboard::Scancode::Up ||
            key->scancode == sf::Keyboard::Scancode::Down)
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
    else if (showLevelSelect) //  level select input
    {
        if (key->scancode == sf::Keyboard::Scancode::Up)
        {
            levelSelectIndex = levelSelectIndex - 1;
            if (levelSelectIndex < 0) levelSelectIndex = 6; // wrap to BACK
            audio.getMenuAudio().arrowNavigationPlay();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Down)
        {
            levelSelectIndex = levelSelectIndex + 1;
            if (levelSelectIndex > 6) levelSelectIndex = 0; // wrap to LEVEL 1
            audio.getMenuAudio().arrowNavigationPlay();
        }
        else if (key->scancode == sf::Keyboard::Scancode::Enter)
        {
            audio.getMenuAudio().arrowEnterPlay();
            switch (levelSelectIndex)
            {
            case 0: goToLevel1 = true; break;
            case 1: goToLevel2 = true; break;
            case 2: goToLevel3 = true; break;
            case 3: goToLevel4 = true; break;
            case 4: goToLevel5 = true; break;
            case 5: goToLevel6 = true; break;
            case 6: // BACK
                showLevelSelect = false;
                levelSelectIndex = 0;
                break;
            }
        }
    }
    else // main menu input
    {
        selectedIndex = NavigationHelper::moveUpDown(event, selectedIndex, 4, audio.getMenuAudio());

        if (key->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (selectedIndex == 0) // NEW GAME
            {
                audio.getMenuAudio().arrowEnterPlay();
                showLevelSelect = true; //
                levelSelectIndex = 0;
            }
            else if (selectedIndex == 2) // OPTIONS
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