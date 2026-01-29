#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }),
        "SFML 3 - Visual Studio"
    );

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
