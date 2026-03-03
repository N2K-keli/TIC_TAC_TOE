#include "Level2Scene.hpp"

void Level2Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 2!\n";
        hasEntered = true;
    }
}

void Level2Scene::draw(sf::RenderWindow& window)
{
    onEnter();
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}