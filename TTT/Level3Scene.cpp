#include "Level3Scene.hpp"

void Level3Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 3!\n";
        hasEntered = true;
    }
}

void Level3Scene::draw(sf::RenderWindow& window)
{
    onEnter();
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}