#include "MenuScene.hpp"
#include "NavigationHelper.hpp"



void MenuScene::drawMenu(sf::RenderWindow& window)
{
    newGame.draw(window);
    continueGame.draw(window);
    options.draw(window);
    exit.draw(window);

    float arrowY = 200.f + (selectedIndex * 60.f) + 35.f;
    arrow.getArrowSprite().setPosition({ 250.f, arrowY });

    window.draw(arrow.getArrowSprite()); 
    window.display();                   
}
void MenuScene::updateMenuIndex(const sf::Event& event, AudioManager& audio)
{
    selectedIndex = NavigationHelper::moveUpDown(event, selectedIndex, 4, audio.getMenuAudio());
    std::cout << "selectedIndex: " << selectedIndex << "\n";

}