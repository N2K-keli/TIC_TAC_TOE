#include "GameOverScene.hpp"

void GameOverScene::init(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;
    float winH = (float)window.getSize().y;

    //  result text — 25% from top, centered
    resultY = winH * 0.25f;

    //  score text — 40% from top
    scoreY = winH * 0.40f;

    //  options start at 55% from top
    optionStartY = winH * 0.55f;
    optionSpacing = winH * 0.10f;

    std::cout << "GameOverScene initialized\n";
}

void GameOverScene::setup(GameManager::Result result, int playerScore, int cpuScore, AudioManager& audio)
{
    //  reset flags
    goPlayAgain = false;
    goBackToMenu = false;
    selectedIndex = 0;

    //  set result text and play audio
    if (result == GameManager::Result::playerWin)
    {
        resultText.getText().setString("YOU WIN!");
        resultText.getText().setFillColor(sf::Color::Yellow);
        audio.getGameWinAudio().play();
    }
    else if (result == GameManager::Result::cpuWin)
    {
        resultText.getText().setString("YOU LOSE!");
        resultText.getText().setFillColor(sf::Color::Red);
        audio.getGameLoseAudio().play();
    }
    else
    {
        resultText.getText().setString("DRAW!");
        resultText.getText().setFillColor(sf::Color::White);
        audio.getGameDrawAudio().play();
    }

    //  set score text
    scoreText.getText().setString(
        std::to_string(playerScore) + " - " + std::to_string(cpuScore)
    );
    scoreText.getText().setFillColor(sf::Color::White);

    std::cout << "GameOverScene setup — result displayed\n";
}

void GameOverScene::handleEvent(const sf::Event& event, AudioManager& audio)
{
    if (!event.is<sf::Event::KeyPressed>()) return;
    auto* key = event.getIf<sf::Event::KeyPressed>();

    if (key->scancode == sf::Keyboard::Scancode::Up ||
        key->scancode == sf::Keyboard::Scancode::Down)
    {
        selectedIndex = (selectedIndex == 0) ? 1 : 0; //  toggle
        audio.getMenuAudio().arrowNavigationPlay();
    }
    else if (key->scancode == sf::Keyboard::Scancode::Enter)
    {
        audio.getMenuAudio().arrowEnterPlay();
        if (selectedIndex == 0) goPlayAgain = true; // PLAY AGAIN
        else                    goBackToMenu = true; //  BACK TO MENU
    }
}

void GameOverScene::draw(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;

    // center result text
    sf::FloatRect resultBounds = resultText.getText().getLocalBounds();
    resultText.getText().setPosition({
        (winW - resultBounds.size.x) / 2.f, resultY
        });
    resultText.draw(window);

    //  center score text
    sf::FloatRect scoreBounds = scoreText.getText().getLocalBounds();
    scoreText.getText().setPosition({
        (winW - scoreBounds.size.x) / 2.f, scoreY
        });
    scoreText.draw(window);

    //  reset option colors
    playAgain.getText().setFillColor(sf::Color::White);
    backToMenu.getText().setFillColor(sf::Color::White);

    //  highlight selected yellow
    if (selectedIndex == 0) playAgain.getText().setFillColor(sf::Color::Yellow);
    else                    backToMenu.getText().setFillColor(sf::Color::Yellow);

    //  position options
    float option1Y = optionStartY;
    float option2Y = optionStartY + optionSpacing;

    sf::FloatRect playBounds = playAgain.getText().getLocalBounds();
    playAgain.getText().setPosition({
        (winW - playBounds.size.x) / 2.f, option1Y
        });
    playAgain.draw(window);

    sf::FloatRect backBounds = backToMenu.getText().getLocalBounds();
    backToMenu.getText().setPosition({
        (winW - backBounds.size.x) / 2.f, option2Y
        });
    backToMenu.draw(window);

    //  arrow position
    float arrowY = (selectedIndex == 0) ? option1Y + 15.f : option2Y + 15.f;
    sf::FloatRect playArrowBounds = playAgain.getText().getLocalBounds();
    float arrowX = (winW - playArrowBounds.size.x) / 2.f - 60.f;
    arrow.getArrowSprite().setPosition({ arrowX, arrowY });
    window.draw(arrow.getArrowSprite());

    window.display();
}