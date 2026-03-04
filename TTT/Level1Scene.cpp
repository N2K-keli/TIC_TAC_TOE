#include "Level1Scene.hpp"

void Level1Scene::onEnter(sf::RenderWindow& win)
{
    if (!hasEntered)
    {
        std::cout << "Entering Level 1\n";

        window = &win; //  store window pointer for later use

        player.init(
            "assets/images/level1_player_symbol.png",
            "assets/images/level1_player_picture.png",
            "PLAYER"
        );
        cpu.init(
            "assets/images/level1_cpu_symbol.png",
            "assets/images/level1_cpu_picture.png",
            "CPU"
        );

        playerRender.init(win);
        cpuRender.init(win);
        gridSizeInput.reset();

        hasEntered = true;
        gameStarted = false;
    }
}

void Level1Scene::handleEvent(const sf::Event& event, AudioManager& audio)
{
    if (!gameStarted)
    {
        gridSizeInput.handleEvent(event, audio);

        if (gridSizeInput.isConfirmed())
        {
            int size = gridSizeInput.getGridSize();

            board.init(size);
            boardRender.init(size, *window, //  use stored window pointer
                "assets/images/game_background2.jpg");

            audio.getLevel1GameAudio().play(); // start game audio on confirm
            gameStarted = true;

            std::cout << "Level 1 started with grid size: " << size << "\n";
        }
    }
}

void Level1Scene::draw(sf::RenderWindow& window, AudioManager& audio)
{
    onEnter(window); //  fires once on first draw

    if (!gameStarted)
    {
        //  show grid size input — game audio not started yet, silence here
        gridSizeInput.draw(window);
    }
    else
    {
        // game audio already looping from handleEvent
        //  draw full game scene
        boardRender.draw(window, board, player, cpu);
        playerRender.draw(window, player);
        cpuRender.draw(window, cpu);
        window.display();
    }
}