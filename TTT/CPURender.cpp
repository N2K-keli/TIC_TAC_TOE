#include "CPURender.hpp"

void CPURender::init(sf::RenderWindow& window)
{
    std::cout << "CPURender initialized\n";
}

void CPURender::draw(sf::RenderWindow& window, CPU& cpu)
{
    drawPicture(window, cpu);
    drawName(window, cpu);
}

void CPURender::drawPicture(sf::RenderWindow& window, CPU& cpu)
{
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u texSize = cpu.getPictureTexture().getSize();

    float panelWidth = 180.f;
    float panelHeight = 250.f;

    pictureSprite.emplace(cpu.getPictureTexture()); // create sprite with texture
    pictureSprite->setScale({ panelWidth / texSize.x, panelHeight / texSize.y });
    pictureSprite->setPosition({
        600.f + (200.f - panelWidth) / 2.f,
        ((float)windowSize.y / 2.f) - (panelHeight / 2.f) - 30.f
        });

    window.draw(*pictureSprite); // dereference with *
}

void CPURender::drawName(sf::RenderWindow& window, CPU& cpu)
{
    nameText.getText().setString(cpu.getName());
    nameText.getText().setFillColor(sf::Color::White);

    sf::FloatRect textBounds = nameText.getText().getLocalBounds();
    nameText.getText().setPosition({ 600.f + (200.f - textBounds.size.x) / 2.f, 350.f });
    nameText.draw(window);
}