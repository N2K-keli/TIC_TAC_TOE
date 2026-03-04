#include "GridSizeInput.hpp"
#include <string>

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
    
    sizeText.getText().setString(std::to_string(currentSize));

    promptText.getText().setFillColor(sf::Color::White);
    sizeText.getText().setFillColor(sf::Color::Yellow); 
    hintText.getText().setFillColor(sf::Color::White);

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