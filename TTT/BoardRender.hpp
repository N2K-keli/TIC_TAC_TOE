#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Board.hpp"
#include "Player.hpp"
#include "CPU.hpp"

class BoardRender
{
public:
    void init(int gridSize, sf::RenderWindow& window, const std::string& backgroundPath);
    void draw(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu);

private:
    sf::Texture backgroundTexture;
    std::optional<sf::Sprite> backgroundSprite; // 

    float cellSize = 0.f;
    float boardStartX = 0.f;
    float boardStartY = 0.f;
    int   gridSize = 3;

    sf::Color cellColor{ 139, 90, 43 };
    sf::Color borderColor{ 80,  40, 10 };

    void drawBackground(sf::RenderWindow& window);
    void drawGrid(sf::RenderWindow& window, Board& board, Player& player, CPU& cpu);
    void drawSymbol(sf::RenderWindow& window, sf::Texture& texture, int row, int col);
};