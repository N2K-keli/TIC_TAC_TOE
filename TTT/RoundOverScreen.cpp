#include "RoundOverScreen.hpp"
#include <string>

void RoundOverScreen::init(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;
    float winH = (float)window.getSize().y;

    //  dark semi-transparent overlay covers entire screen
    overlay.setSize({ winW, winH });
    overlay.setFillColor(sf::Color(0, 0, 0, 200)); //  black with 200/255 opacity
    overlay.setPosition({ 0.f, 0.f });

    //  round text — 35% from top
    roundY = winH * 0.35f;
    roundX = winW * 0.5f; //  will be centered properly in draw()

    //  winner text — 50% from top
    winnerY = winH * 0.50f;
    winnerX = winW * 0.5f;
}

void RoundOverScreen::show(int roundNumber, const std::string& winner)
{
    roundText.getText().setString("ROUND " + std::to_string(roundNumber) + " OVER");
    winnerText.getText().setString(winner);

    elapsed = 0.f;
    finished = false;
    active = true;

    clock.restart(); //  start timer
    std::cout << "RoundOverScreen showing: Round " << roundNumber << " — " << winner << "\n";
}

void RoundOverScreen::update()
{
    if (!active) return;

    elapsed = clock.getElapsedTime().asSeconds();

    if (elapsed >= duration)
    {
        active = false;
        finished = true;
        std::cout << "RoundOverScreen finished\n";
    }
}

void RoundOverScreen::draw(sf::RenderWindow& window)
{
    if (!active) return;

    float winW = (float)window.getSize().x;

    // draw dark overlay
    window.draw(overlay);

    //  center round text
    roundText.getText().setFillColor(sf::Color::White);
    sf::FloatRect roundBounds = roundText.getText().getLocalBounds();
    roundText.getText().setPosition({
        (winW - roundBounds.size.x) / 2.f,
        roundY
        });
    roundText.draw(window);

    //  center winner text in yellow
    winnerText.getText().setFillColor(sf::Color::Yellow);
    sf::FloatRect winnerBounds = winnerText.getText().getLocalBounds();
    winnerText.getText().setPosition({
        (winW - winnerBounds.size.x) / 2.f,
        winnerY
        });
    winnerText.draw(window);
}

void RoundOverScreen::reset()
{
    active = false;
    finished = false;
    elapsed = 0.f;
}

bool RoundOverScreen::isFinished() const
{
    return finished;
}