#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.hpp"
#include "BoardRender.hpp"
#include "Player.hpp"
#include "PlayerRender.hpp"
#include "CPU.hpp"
#include "CPURender.hpp"
#include "GridSizeInput.hpp"
#include "AudioManager.hpp"

class Level1Scene
{
public:
    void onEnter(sf::RenderWindow& window);   //  called once when level is entered
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window, AudioManager& audio);

    bool hasEntered = false;

private:
    sf::RenderWindow* window = nullptr;

    //  data classes
    Board  board;
    Player player;
    CPU    cpu;

    //  render classes
    BoardRender  boardRender;
    PlayerRender playerRender;
    CPURender    cpuRender;

    //  grid size input
    GridSizeInput gridSizeInput;

    bool gameStarted = false; //  true after grid size confirmed
};