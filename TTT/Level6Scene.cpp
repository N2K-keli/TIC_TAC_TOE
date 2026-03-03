#include "Level6Scene.hpp"

void Level6Scene::onEnter()
{
    if (!hasEntered)
    {
        std::cout << "Welcome to Level 6!\n";
        hasEntered = true;
    }
}

void Level6Scene::draw(sf::RenderWindow& window)
{
    onEnter();
    levelText.getText().setFillColor(sf::Color::White);
    levelText.draw(window);
    window.display();
}