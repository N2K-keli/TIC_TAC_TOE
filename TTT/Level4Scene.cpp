#include "Level4Scene.hpp"

void Level4Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 4!\n";
        hasEntered = true;
    }
}

void Level4Scene::draw(sf::RenderWindow& window)
{
    onEnter();
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}