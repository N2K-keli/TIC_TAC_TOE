#include <iostream>
#include <chrono>
#include <thread>
#include "SceneManager.hpp"
#include <filesystem>

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

    std::this_thread::sleep_for(2000ms); // Hold for 2 seconds

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
}