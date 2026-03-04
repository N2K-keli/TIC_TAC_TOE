#include "PlayerRender.hpp"

void PlayerRender::init(sf::RenderWindow& window)
{
    std::cout << "PlayerRender initialized\n";
}

void PlayerRender::draw(sf::RenderWindow& window, Player& player)
{
    drawPicture(window, player);
    drawName(window, player);
}

void PlayerRender::drawPicture(sf::RenderWindow& window, Player& player)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u texSize = player.getPictureTexture().getSize();

    float panelWidth = 180.f;
    float panelHeight = 250.f;

    pictureSprite.emplace(player.getPictureTexture()); //  create sprite with texture
    pictureSprite->setScale({ panelWidth / texSize.x, panelHeight / texSize.y });
    pictureSprite->setPosition({
        (200.f - panelWidth) / 2.f,
        ((float)windowSize.y / 2.f) - (panelHeight / 2.f) - 30.f
        });

    window.draw(*pictureSprite); //  dereference with *
}

void PlayerRender::drawName(sf::RenderWindow& window, Player& player)
{
    nameText.getText().setString(player.getName());
    nameText.getText().setFillColor(sf::Color::White);

    sf::FloatRect textBounds = nameText.getText().getLocalBounds();
    nameText.getText().setPosition({ (200.f - textBounds.size.x) / 2.f, 350.f });
    nameText.draw(window);
}