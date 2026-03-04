#include "PlayerRender.hpp"

void PlayerRender::init(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;
    float winH = (float)window.getSize().y;

    //  panel is 20% of window width
    float panelZoneWidth = winW * 0.20f;

    //  picture is 90% of panel width, 35% of window height
    panelWidth = panelZoneWidth * 0.90f;
    panelHeight = winH * 0.35f;

    //  center picture horizontally in left panel, vertically in window
    picX = (panelZoneWidth - panelWidth) / 2.f;
    picY = (winH / 2.f) - (panelHeight / 2.f) - (winH * 0.05f);

    //  center name under picture
    nameX = panelZoneWidth / 2.f; // will be adjusted for text width in draw
    nameY = picY + panelHeight + (winH * 0.02f);

    std::cout << "PlayerRender initialized\n";
}

void PlayerRender::draw(sf::RenderWindow& window, Player& player)
{
    drawPicture(window, player);
    drawName(window, player);
}

void PlayerRender::drawPicture(sf::RenderWindow& window, Player& player)
{
    sf::Vector2u texSize = player.getPictureTexture().getSize();

    pictureSprite.emplace(player.getPictureTexture());
    pictureSprite->setScale({
        panelWidth / texSize.x,
        panelHeight / texSize.y
        });
    pictureSprite->setPosition({ picX, picY });
    window.draw(*pictureSprite);
}

void PlayerRender::drawName(sf::RenderWindow& window, Player& player)
{
    nameText.getText().setString(player.getName());
    nameText.getText().setFillColor(sf::Color::White);

    // center name horizontally under picture
    sf::FloatRect textBounds = nameText.getText().getLocalBounds();
    float centeredX = picX + (panelWidth - textBounds.size.x) / 2.f;
    nameText.getText().setPosition({ centeredX, nameY });

    nameText.draw(window);
}