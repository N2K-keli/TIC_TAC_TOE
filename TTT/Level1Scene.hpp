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
#include "Level1Strategy.hpp"
#include "GameManager.hpp" 
#include "RoundOverScreen.hpp"

class Level1Scene
{
public:
    void onEnter(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window, AudioManager& audio);
    bool goToGameOver = false;
    void fullReset(); 

    bool hasEntered = false;
    GameManager::Result getResult()     const { return gameManager.getResult(); }
    int                 getPlayerScore() const { return gameManager.getPlayerScore(); }
    int                 getCPUScore()    const { return gameManager.getCPUScore(); }

private:
    sf::RenderWindow* window = nullptr;
    
    int cursorRow = 0;
    int cursorCol = 0;

    Board  board;
    Player player;
    CPU    cpu;

    BoardRender  boardRender;
    PlayerRender playerRender;
    CPURender    cpuRender;

    GridSizeInput gridSizeInput;
    GameManager   gameManager; 

    RoundOverScreen roundOverScreen; 
    bool roundOverActive = false;

    bool gameStarted = false;
};