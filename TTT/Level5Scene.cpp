#include "Level5Scene.hpp"

void Level5Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 5!\n";
        hasEntered = true;
    }
}

void Level5Scene::draw(sf::RenderWindow& window)
{
    onEnter();
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}