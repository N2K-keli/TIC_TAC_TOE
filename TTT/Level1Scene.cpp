#include "Level1Scene.hpp"
#include "Level1Strategy.hpp"

void Level1Scene::onEnter(sf::RenderWindow& win)
{
    if (!hasEntered)
    {
        window = &win;

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

        cpu.setStrategy(new Level1Strategy());

        playerRender.init(win);
        cpuRender.init(win);
        gridSizeInput.init(win);
        gridSizeInput.reset();

        hasEntered = true;
        gameStarted = false;
    }
}

void Level1Scene::handleEvent(const sf::Event& event, AudioManager& audio)
{
    if (event.is<sf::Event::Resized>())
    {
        gridSizeInput.init(*window);
        if (gameStarted)
        {
            boardRender.init(board.getSize(), *window, "assets/images/game_background2.jpg");
            playerRender.init(*window);
            cpuRender.init(*window);
        }
        return;
    }

    if (!gameStarted)
    {
        gridSizeInput.handleEvent(event, audio);
        if (gridSizeInput.isConfirmed())
        {
            int size = gridSizeInput.getGridSize();
            board.init(size);
            boardRender.init(size, *window, "assets/images/game_background2.jpg");
            gameManager.init(size); //  initialize game manager with grid size
            audio.getLevel1GameAudio().play();
            gameStarted = true;
            cursorRow = 0;
            cursorCol = 0;
            std::cout << "Level 1 started with grid size: " << size << "\n";
        }
    }
    else
    {
        if (!event.is<sf::Event::KeyPressed>()) return;
        auto* key = event.getIf<sf::Event::KeyPressed>();

        //  only allow input if game is not over
        if (!gameManager.isGameOver())
        {
            if (key->scancode == sf::Keyboard::Scancode::Up)
            {
                if (cursorRow > 0) cursorRow--;
                audio.getMenuAudio().arrowNavigationPlay();
            }
            else if (key->scancode == sf::Keyboard::Scancode::Down)
            {
                if (cursorRow < board.getSize() - 1) cursorRow++;
                audio.getMenuAudio().arrowNavigationPlay();
            }
            else if (key->scancode == sf::Keyboard::Scancode::Left)
            {
                if (cursorCol > 0) cursorCol--;
                audio.getMenuAudio().arrowNavigationPlay();
            }
            else if (key->scancode == sf::Keyboard::Scancode::Right)
            {
                if (cursorCol < board.getSize() - 1) cursorCol++;
                audio.getMenuAudio().arrowNavigationPlay();
            }
            else if (key->scancode == sf::Keyboard::Scancode::Enter)
            {
                //  player places symbol
                bool valid = gameManager.handlePlayerMove(cursorRow, cursorCol, board);

                if (valid && !gameManager.isGameOver())
                {
                    //  CPU takes its turn immediately after player
                    gameManager.handleCPUMove(board, cpu);
                }
            }
        }
    }
}

void Level1Scene::draw(sf::RenderWindow& window, AudioManager& audio)
{
    onEnter(window);

    if (!gameStarted)
    {
        gridSizeInput.draw(window);
    }
    else
    {
        boardRender.draw(window, board, player, cpu, cursorRow, cursorCol);
        playerRender.draw(window, player);
        cpuRender.draw(window, cpu);
        window.display();
    }
}