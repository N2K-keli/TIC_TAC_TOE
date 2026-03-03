#include "Level1Scene.hpp"

void Level1Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 1!\n"; 
        hasEntered = true;
    }
}

void Level1Scene::draw(sf::RenderWindow& window)
{
    onEnter(); 
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}