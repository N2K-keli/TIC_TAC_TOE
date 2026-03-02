#include "MenuScene.hpp"

void MenuScene::drawMenu(sf::RenderWindow& window)
{
    newGame.draw(window);
    continueGame.draw(window);
    options.draw(window);
    exit.draw(window);

    window.display();
    
    window.draw(arrow.getArrowSprite());

}
