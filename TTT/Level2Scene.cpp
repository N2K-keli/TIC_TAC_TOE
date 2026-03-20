#include "Level2Scene.hpp"
#include "SaveManager.hpp"
void Level2Scene::onEnter(sf::RenderWindow& win)
{
    if (!hasEntered)
    {
        window = &win;

        player.init(
            "assets/images/level1_player_symbol.png", // 
            "assets/images/level1_player_picture.png", // 
            "PLAYER"
        );
        cpu.init(
            "assets/images/level2_cpu_symbol.png", // 
            "assets/images/level2_player_picture.jpg", // 
            "CPU"
        );

        cpu.setStrategy(new Level2Strategy()); //  only strategy change

        playerRender.init(win);
        cpuRender.init(win);
        gridSizeInput.init(win);
        roundOverScreen.init(win);
        gridSizeInput.reset();

        hasEntered = true;
        gameStarted = false;
    }
}

void Level2Scene::handleEvent(const sf::Event& event, AudioManager& audio)
{
    if (event.is<sf::Event::Resized>())
    {
        gridSizeInput.init(*window);
        roundOverScreen.init(*window);
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
            gameManager.init(size);
            audio.getLevel2GameAudio().play(); // 
            gameStarted = true;
            cursorRow = 0;
            cursorCol = 0;
            std::cout << "Level 2 started with grid size: " << size << "\n";
        }
    }
    else
    {
        if (roundOverActive) return;

        if (!event.is<sf::Event::KeyPressed>()) return;
        auto* key = event.getIf<sf::Event::KeyPressed>();
        if (key->scancode == sf::Keyboard::Scancode::Q || key->scancode == sf::Keyboard::Scancode::Escape)
        {
            goToMenu = true;
            return;
        }

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
                bool valid = gameManager.handlePlayerMove(cursorRow, cursorCol, board);

                if (valid && !gameManager.isGameOver())
                {
                    gameManager.handleCPUMove(board, cpu);
                }
                if (valid)
                {
                    SaveData data;
                    data.level = 1; //  change per level
                    data.gridSize = board.getSize();
                    data.playerScore = gameManager.getPlayerScore();
                    data.cpuScore = gameManager.getCPUScore();
                    data.roundNumber = gameManager.getRoundNumber();
                    data.playerTurn = gameManager.getIsPlayerTurn();

                    //  copy board state
                    data.boardData.resize(board.getSize(), std::vector<int>(board.getSize(), 0));
                    for (int r = 0; r < board.getSize(); r++)
                        for (int c = 0; c < board.getSize(); c++)
                        {
                            CellState cell = board.getCell(r, c);
                            data.boardData[r][c] = (cell == CellState::empty) ? 0 :
                                (cell == CellState::player) ? 1 : 2;
                        }

                    SaveManager::save(data);
                }


                if (gameManager.isGameOver())
                {
                    std::string winnerMsg;
                    if (gameManager.getResult() == GameManager::Result::playerWin)
                        winnerMsg = "PLAYER WINS!";
                    else if (gameManager.getResult() == GameManager::Result::cpuWin)
                        winnerMsg = "CPU WINS!";
                    else
                        winnerMsg = "DRAW!";

                    roundOverScreen.show(gameManager.getRoundNumber() - 1, winnerMsg);
                    roundOverActive = true;
                }
            }
        }
    }
}

void Level2Scene::draw(sf::RenderWindow& window, AudioManager& audio)
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

        sf::Vector2u size = window.getSize();
        quitHint.getText().setPosition(sf::Vector2f(10.f, static_cast<float>(size.y) - 35.f));
        quitHint.draw(window);

        if (roundOverActive)
        {
            roundOverScreen.update();
            roundOverScreen.draw(window);

            if (roundOverScreen.isFinished())
            {
                roundOverActive = false;
                roundOverScreen.reset();

                if (!gameManager.isMatchOver())
                {
                    board.init(board.getSize());
                    gameManager.reset();
                    cursorRow = 0;
                    cursorCol = 0;
                }
                else
                {
                    goToGameOver = true;
                }
            }
        }

        window.display();
    }
}

void Level2Scene::fullReset()
{
    board.reset();
    gameManager.fullReset();
    gridSizeInput.reset();
    gameStarted = false;
    roundOverActive = false;
    goToGameOver = false;
    hasEntered = false;
    cursorRow = 0;
    cursorCol = 0;
    std::cout << "Level2Scene fully reset\n";
}