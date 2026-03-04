#include "GridSizeInput.hpp"
#include <string>

void GridSizeInput::init(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;
    float winH = (float)window.getSize().y;

    //  prompt text — 30% from top, centered horizontally
    sf::FloatRect promptBounds = promptText.getText().getLocalBounds();
    promptX = (winW - promptBounds.size.x) / 2.f;
    promptY = winH * 0.30f;

    //  size number — centered, below prompt
    sf::FloatRect sizeBounds = sizeText.getText().getLocalBounds();
    sizeX = (winW - sizeBounds.size.x) / 2.f;
    sizeY = winH * 0.45f;

    //  hint text — 75% from top, centered horizontally
    sf::FloatRect hintBounds = hintText.getText().getLocalBounds();
    hintX = (winW - hintBounds.size.x) / 2.f;
    hintY = winH * 0.75f;
}

void GridSizeInput::handleEvent(const sf::Event& event, AudioManager& audio)
{
    if (!event.is<sf::Event::KeyPressed>()) return;
    auto* key = event.getIf<sf::Event::KeyPressed>();

    if (key->scancode == sf::Keyboard::Scancode::Left)
    {
        if (currentSize > minSize)
        {
            currentSize--;
            audio.getMenuAudio().arrowNavigationPlay();
        }
    }
    else if (key->scancode == sf::Keyboard::Scancode::Right)
    {
        if (currentSize < maxSize)
        {
            currentSize++;
            audio.getMenuAudio().arrowNavigationPlay();
        }
    }
    else if (key->scancode == sf::Keyboard::Scancode::Enter)
    {
        confirmed = true;
        audio.getMenuAudio().arrowEnterPlay();
    }
}

void GridSizeInput::draw(sf::RenderWindow& window)
{
    // update size text then reposition since string length can change
    sizeText.getText().setString(std::to_string(currentSize));
    sf::FloatRect sizeBounds = sizeText.getText().getLocalBounds();
    sizeX = ((float)window.getSize().x - sizeBounds.size.x) / 2.f; // recenters for 1 or 2 digits

    promptText.getText().setFillColor(sf::Color::White);
    sizeText.getText().setFillColor(sf::Color::Yellow);
    hintText.getText().setFillColor(sf::Color::White);

    promptText.getText().setPosition({ promptX, promptY });
    sizeText.getText().setPosition({ sizeX, sizeY });
    hintText.getText().setPosition({ hintX, hintY });

    promptText.draw(window);
    sizeText.draw(window);
    hintText.draw(window);

    window.display();
}

void GridSizeInput::reset()
{
    currentSize = minSize;
    confirmed = false;
}

bool GridSizeInput::isConfirmed()
{
    return confirmed;
}

int GridSizeInput::getGridSize()
{
    return currentSize;
}