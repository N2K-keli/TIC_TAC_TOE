#include <iostream>
#include <chrono>
#include <thread>
#include "SceneManager.hpp"
#include <filesystem>
#include <vector>

using namespace std::chrono_literals;

// constructor
SceneManager::SceneManager(sf::RenderWindow& window)
{
    if (!logo.loadFromFile("assets/images/logo.png"))
    {
        std::cerr << "Error: Could not load logo\n";
    }
    else
    {
        std::cout << "SUCCESS! Logo loaded!\n";
    }

    logoSprite.emplace(logo);

    // Get the sprite size will return Vector2u
    sf::Vector2u spriteSize = logo.getSize();

    // Set origin to sprite's center (convert to vector2f)
    logoSprite.value().setOrigin({ static_cast<float>(spriteSize.x) / 2.f, static_cast<float>(spriteSize.y) / 2.f });

    // Getting window size will return a Vector2u
    sf::Vector2u windowSize = window.getSize();

    // Scale sprite is to be 1/2 of window width 
    float desiredWidth = static_cast<float>(windowSize.x) / 2.f;
    float scale = desiredWidth / static_cast<float>(spriteSize.x);
    logoSprite.value().setScale({ scale, scale });  // No stretching

    // Position at window center (convert to vector2f)
    logoSprite.value().setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) / 2.f });
}

// methods
void SceneManager::LoadIntro(sf::RenderWindow& window)
{
    int fadingAlphaValue = 0;

    // fading in logic 
    // fading in
    while (fadingAlphaValue < 255)
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                const float width = static_cast<float>(resized->size.x);
                const float height = static_cast<float>(resized->size.y);
                window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { width, height })));

                // Recalculate scale to maintain proportions relative to new window size
                sf::Vector2u spriteSize = logo.getSize();
                float desiredWidth = width / 2.f;  // Keep sprite at 1/2 of window width
                float scale = desiredWidth / static_cast<float>(spriteSize.x);
                logoSprite.value().setScale({ scale, scale });  // No stretching

                // Reposition sprite to new center after resize
                logoSprite.value().setPosition({ width / 2.f, height / 2.f });
            }
        }

        if (!window.isOpen())
            return;

        fadingAlphaValue = fadingAlphaValue + 5;
        logoSprite.value().setColor(sf::Color(255, 255, 255, fadingAlphaValue));
        window.clear();
        window.draw(logoSprite.value());
        window.display();
        std::this_thread::sleep_for(50ms);
    }

    std::this_thread::sleep_for(1500ms); // Hold for 2 seconds

    // fade out 
    while (fadingAlphaValue > 0)
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                const float width = static_cast<float>(resized->size.x);
                const float height = static_cast<float>(resized->size.y);
                window.setView(sf::View(sf::FloatRect({ 0.f, 0.f }, { width, height })));

                // Recalculate scale to maintain proportions relative to new window size
                sf::Vector2u spriteSize = logo.getSize();
                float desiredWidth = width / 2.f;  // Keep sprite at 1/2 of window width
                float scale = desiredWidth / static_cast<float>(spriteSize.x);
                logoSprite.value().setScale({scale, scale});  // No stretching

                // Reposition sprite to new center after resize
                logoSprite.value().setPosition({ width / 2.f, height / 2.f });
            }
        }

        if (!window.isOpen())
            return;

        fadingAlphaValue = fadingAlphaValue - 5;
        logoSprite.value().setColor(sf::Color(255, 255, 255, fadingAlphaValue));
        window.clear();
        window.draw(logoSprite.value());
        window.display();
        std::this_thread::sleep_for(50ms);
    }
    std::this_thread::sleep_for(1500ms); 
}

void SceneManager::LoadMenu(sf::RenderWindow& window)
{

    window.clear();
    sf::Font font;
    if (!font.openFromFile("assets/fonts/GreatsRacingFreeForPersonalItalic-BLLM8.otf"))
    {
        std::cout << "error loading the font";
    }
    else
    {
        std::cout << "Succesfully loaded the files";
    }
    sf::Text text(font, "New Game", 50);

    // Getting window size will return a Vector2u
    sf::Vector2u windowSize = window.getSize();

    // Get the text's local bounds to know its size
    sf::FloatRect textBounds = text.getLocalBounds();

    // Scale text to be 1/2 of window width 
    float desiredWidth = static_cast<float>(windowSize.x) / 4.5f;
    float scale = desiredWidth / textBounds.size.x;
    text.setScale({ scale, scale });

    // Set origin to center of text for proper centering
    text.setOrigin({ textBounds.size.x / 2.f, textBounds.size.y / 2.f });

    // Position 20% below center of screen (0.4 = 50% + 10%)
    text.setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) * 0.4f });
   
    sf::Text continueText(font, "Continue", 50); 
    sf::Text loadGameText(font, "Load Games", 50);
    sf::Text settings(font, "Settings", 50); 
    sf::Text ExitText(font, "Exit", 50); 

    continueText.setScale(text.getScale());
    loadGameText.setScale(text.getScale());
    settings.setScale(text.getScale());
    ExitText.setScale(text.getScale());

    continueText.setOrigin(text.getOrigin());
    loadGameText.setOrigin(text.getOrigin());
    settings.setOrigin(text.getOrigin());
    ExitText.setOrigin(text.getOrigin());

    continueText.setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) * 0.5f });
    loadGameText.setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) * 0.6f });
    settings.setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) * 0.7f });
    ExitText.setPosition({ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) * 0.8f });





    // should have used a for loop above, but i was already too far to restart 
    window.draw(text);
    window.draw(continueText);
    window.draw(loadGameText);
    window.draw(settings);
    window.draw(ExitText);

    window.display();

    std::cout << "this is the menu page\n";
    std::cout << "1- new game " << std::endl;
    std::cout << "2- Continue  " << std::endl;
    std::cout << "3- load game " << std::endl;
    std::cout << "4- settings " << std::endl;
    std::cout << "5- Exit  " << std::endl;

    std::this_thread::sleep_for(2000ms);
}