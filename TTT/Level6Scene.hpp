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
#include "Level6Strategy.hpp" 
#include "GameManager.hpp"
#include "RoundOverScreen.hpp"

class Level6Scene
{
public:
    void onEnter(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, AudioManager& audio);
    void draw(sf::RenderWindow& window, AudioManager& audio);
    void fullReset();

    bool hasEntered = false;
    bool goToGameOver = false;
    bool goToMenu = false; 

    GameManager::Result getResult()      const { return gameManager.getResult(); }
    int                 getPlayerScore() const { return gameManager.getPlayerScore(); }
    int                 getCPUScore()    const { return gameManager.getCPUScore(); }

private:
    sf::RenderWindow* window = nullptr;
    int cursorRow = 0;
    int cursorCol = 0;

    Board  board;
    Player player;
    CPU    cpu;

    BoardRender     boardRender;
    PlayerRender    playerRender;
    CPURender       cpuRender;
    GridSizeInput   gridSizeInput;
    GameManager     gameManager;
    RoundOverScreen roundOverScreen;

    bool gameStarted = false;
    bool roundOverActive = false;
};