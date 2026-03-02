#include "Arrow.hpp"
#include<iostream>

Arrow::Arrow(sf::Vector2f position)
{
    if (!arrow.loadFromFile("assets/images/menuarrow.png"))
    {
        std::cerr << "Error: Could not load arrow\n";
    }
    else
    {
        std::cout << "SUCCESS! arrow loaded!\n";
    }

    arrowSprite.emplace(arrow);
    arrowSprite.value().setPosition(position);
    arrowSprite.value().setOrigin({ arrow.getSize().x / 2.f, arrow.getSize().x / 2.f });
    arrowSprite.value().setScale({ 0.8f, 0.8f });
    
}
sf::Sprite& Arrow::getArrowSprite() 
{
    return arrowSprite.value(); 
}