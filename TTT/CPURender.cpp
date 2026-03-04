#include "CPURender.hpp"

void CPURender::init(sf::RenderWindow& window)
{
    float winW = (float)window.getSize().x;
    float winH = (float)window.getSize().y;

    //  right panel starts at 80% of window width
    float panelZoneWidth = winW * 0.20f;
    float panelZoneStartX = winW * 0.80f;

    //  picture is 90% of panel width, 35% of window height
    panelWidth = panelZoneWidth * 0.90f;
    panelHeight = winH * 0.35f;

    //  center picture horizontally in right panel, vertically in window
    picX = panelZoneStartX + (panelZoneWidth - panelWidth) / 2.f;
    picY = (winH / 2.f) - (panelHeight / 2.f) - (winH * 0.05f);

    //  center name under picture
    nameY = picY + panelHeight + (winH * 0.02f);

    std::cout << "CPURender initialized\n";
}

void CPURender::draw(sf::RenderWindow& window, CPU& cpu)
{
    drawPicture(window, cpu);
    drawName(window, cpu);
}

void CPURender::drawPicture(sf::RenderWindow& window, CPU& cpu)
{
    sf::Vector2u texSize = cpu.getPictureTexture().getSize();

    pictureSprite.emplace(cpu.getPictureTexture());
    pictureSprite->setScale({
        panelWidth / texSize.x,
        panelHeight / texSize.y
        });
    pictureSprite->setPosition({ picX, picY });
    window.draw(*pictureSprite);
}

void CPURender::drawName(sf::RenderWindow& window, CPU& cpu)
{
    nameText.getText().setString(cpu.getName());
    nameText.getText().setFillColor(sf::Color::White);

    //  center name horizontally under picture
    sf::FloatRect textBounds = nameText.getText().getLocalBounds();
    float centeredX = picX + (panelWidth - textBounds.size.x) / 2.f;
    nameText.getText().setPosition({ centeredX, nameY });

    nameText.draw(window);
}