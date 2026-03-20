#include <iostream>
#include <SFML\Graphics.hpp>
#include <optional>
#include "Board.hpp"
#include "StateManager.hpp"
#include <filesystem>
#include "SceneManager.hpp"
#include <SFML/Config.hpp>
#include "IntroScene.hpp"
#include "AudioManager.hpp"
#include "IntroAudio.hpp"
#include "MenuScene.hpp"
#include <cstdlib>
#include <ctime>
#include "SaveManager.hpp"

int main()
{
    Board chessBoard;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u{ 800, 600 }), "TIC TAC TOE");
    IntroScene introSceneObject(window);
    SceneManager sceneManagerObject(window, introSceneObject);
    StateManager stateManagerObject;
    AudioManager audioManagerObject;

    std::srand(std::time(nullptr));

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            if ((*event).is<sf::Event::Closed>())
            {
                window.close();
            }

            if (event->is<sf::Event::Resized>())
            {
                sf::FloatRect visibleArea({ 0.f, 0.f }, {
                    (float)window.getSize().x,
                    (float)window.getSize().y
                    });
                window.setView(sf::View(visibleArea));
            }

            if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
                sceneManagerObject.getMenuScene().updateMenuIndex(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::options)
                sceneManagerObject.getOptionsScene().updateOptionIndex(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level1)
                if (audioManagerObject.getLevel1Audio().isFinished())
                    sceneManagerObject.getLevel1Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level2) 
                if (audioManagerObject.getLevel2Audio().isFinished())
                    sceneManagerObject.getLevel2Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level3)
                if (audioManagerObject.getLevel3Audio().isFinished())
                    sceneManagerObject.getLevel3Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level4)
                if (audioManagerObject.getLevel4Audio().isFinished())
                    sceneManagerObject.getLevel4Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level5)
                if (audioManagerObject.getLevel5Audio().isFinished())
                    sceneManagerObject.getLevel5Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::level6)
                if (audioManagerObject.getLevel6Audio().isFinished())
                    sceneManagerObject.getLevel6Scene().handleEvent(*event, audioManagerObject);

            if (stateManagerObject.getcurrentSceneState() == SceneState::gameOver)
                sceneManagerObject.getGameOverScene().handleEvent(*event, audioManagerObject);
        }

        // ---- INTRO ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::intro)
        {
            audioManagerObject.getIntroAudio().play();
            sceneManagerObject.getIntroScene().LoadIntro(window);
            window.clear();
            sceneManagerObject.getMenuScene().resetFlags();
            stateManagerObject.setcurrentSceneState(SceneState::menu);
        }

        // ---- MENU ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
        {
            audioManagerObject.getMenuAudio().play();
            window.clear();
            sceneManagerObject.getMenuScene().drawMenu(window);

            if (sceneManagerObject.getMenuScene().goToOptions)
            {
                sceneManagerObject.getMenuScene().goToOptions = false;
                stateManagerObject.setcurrentSceneState(SceneState::options);
            }
            if (sceneManagerObject.getMenuScene().shouldExit)
            {
                audioManagerObject.getMenuAudio().stop();
                audioManagerObject.getIntroAudio().stop();
                window.close();
            }

            auto& menu = sceneManagerObject.getMenuScene();
            if (menu.goToLevel1) { menu.goToLevel1 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel1Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level1); }
            if (menu.goToLevel2) { menu.goToLevel2 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel2Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level2); }
            if (menu.goToLevel3) { menu.goToLevel3 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel3Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level3); }
            if (menu.goToLevel4) { menu.goToLevel4 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel4Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level4); }
            if (menu.goToLevel5) { menu.goToLevel5 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel5Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level5); }
            if (menu.goToLevel6) { menu.goToLevel6 = false; audioManagerObject.getMenuAudio().stop(); audioManagerObject.getLevel6Audio().play(); stateManagerObject.setcurrentSceneState(SceneState::level6); }

            
            if (menu.goToContinue)
            {
                menu.goToContinue = false;

                if (SaveManager::saveExists())
                {
                    SaveData data = SaveManager::load();
                    audioManagerObject.getMenuAudio().stop();

                    if (data.level == 1)
                    {
                        sceneManagerObject.getLevel1Scene().fullReset();
                        sceneManagerObject.getLevel1Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel1Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level1);
                    }
                   
                    else if (data.level == 2)
                    {
                        sceneManagerObject.getLevel2Scene().fullReset();
                        sceneManagerObject.getLevel2Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel2Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level2);
                    }
                    
                    else if (data.level == 3)
                    {
                        sceneManagerObject.getLevel3Scene().fullReset();
                        sceneManagerObject.getLevel3Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel3Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level3);
                    }
                    else if (data.level == 4)
                    {
                        sceneManagerObject.getLevel4Scene().fullReset();
                        sceneManagerObject.getLevel4Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel4Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level4);
                    }
                    else if (data.level == 5)
                    {
                        sceneManagerObject.getLevel5Scene().fullReset();
                        sceneManagerObject.getLevel5Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel5Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level5);
                    }
                    else if (data.level == 6)
                    {
                        sceneManagerObject.getLevel6Scene().fullReset();
                        sceneManagerObject.getLevel6Scene().loadSave(data, window, audioManagerObject);
                        audioManagerObject.getLevel6Audio().stop();
                        stateManagerObject.setcurrentSceneState(SceneState::level6);
                    }
                    
                }
            }
        }

        // ---- OPTIONS ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::options)
        {
            window.clear();
            sceneManagerObject.getOptionsScene().drawOptions(window);

            if (sceneManagerObject.getOptionsScene().goBack)
            {
                sceneManagerObject.getOptionsScene().goBack = false;
                sceneManagerObject.getMenuScene().resetFlags();
                stateManagerObject.setcurrentSceneState(SceneState::menu);
            }
        }

        // ---- LEVEL 1 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level1)
        {
            if (audioManagerObject.getLevel1Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel1Scene().draw(window, audioManagerObject);

                

                if (sceneManagerObject.getLevel1Scene().goToMenu)
                {
                    sceneManagerObject.getLevel1Scene().goToMenu = false;
                    sceneManagerObject.getLevel1Scene().fullReset();
                    audioManagerObject.getLevel1GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel1Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel1Scene().goToGameOver = false;
                    audioManagerObject.getLevel1GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level1); 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel1Scene().getResult(),
                        sceneManagerObject.getLevel1Scene().getPlayerScore(),
                        sceneManagerObject.getLevel1Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }

        // ---- LEVEL 2 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level2)
        {
            if (audioManagerObject.getLevel2Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel2Scene().draw(window, audioManagerObject);

                if (sceneManagerObject.getLevel2Scene().goToMenu)
                {
                    sceneManagerObject.getLevel2Scene().goToMenu = false;
                    sceneManagerObject.getLevel2Scene().fullReset();
                    audioManagerObject.getLevel2GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel2Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel2Scene().goToGameOver = false;
                    audioManagerObject.getLevel2GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level2); // 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel2Scene().getResult(),
                        sceneManagerObject.getLevel2Scene().getPlayerScore(),
                        sceneManagerObject.getLevel2Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }

        // ---- LEVEL 3 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level3)
        {
            if (audioManagerObject.getLevel3Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel3Scene().draw(window, audioManagerObject);

                if (sceneManagerObject.getLevel3Scene().goToMenu)
                {
                    sceneManagerObject.getLevel3Scene().goToMenu = false;
                    sceneManagerObject.getLevel3Scene().fullReset();
                    audioManagerObject.getLevel3GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel3Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel3Scene().goToGameOver = false;
                    audioManagerObject.getLevel3GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level3); // 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel3Scene().getResult(),
                        sceneManagerObject.getLevel3Scene().getPlayerScore(),
                        sceneManagerObject.getLevel3Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }

        // ---- LEVEL 4 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level4)
        {
            if (audioManagerObject.getLevel4Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel4Scene().draw(window, audioManagerObject);

                if (sceneManagerObject.getLevel4Scene().goToMenu)
                {
                    sceneManagerObject.getLevel4Scene().goToMenu = false;
                    sceneManagerObject.getLevel4Scene().fullReset();
                    audioManagerObject.getLevel4GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel4Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel4Scene().goToGameOver = false;
                    audioManagerObject.getLevel4GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level4); // 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel4Scene().getResult(),
                        sceneManagerObject.getLevel4Scene().getPlayerScore(),
                        sceneManagerObject.getLevel4Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }

        // ---- LEVEL 5 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level5)
        {
            if (audioManagerObject.getLevel5Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel5Scene().draw(window, audioManagerObject);

                if (sceneManagerObject.getLevel5Scene().goToMenu)
                {
                    sceneManagerObject.getLevel5Scene().goToMenu = false;
                    sceneManagerObject.getLevel5Scene().fullReset();
                    audioManagerObject.getLevel5GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel5Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel5Scene().goToGameOver = false;
                    audioManagerObject.getLevel5GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level5); 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel5Scene().getResult(),
                        sceneManagerObject.getLevel5Scene().getPlayerScore(),
                        sceneManagerObject.getLevel5Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }
        // ---- LEVEL 6 ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::level6)
        {
            if (audioManagerObject.getLevel6Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel6Scene().draw(window, audioManagerObject);
                
                if (sceneManagerObject.getLevel6Scene().goToMenu)
                {
                    sceneManagerObject.getLevel6Scene().goToMenu = false;
                    sceneManagerObject.getLevel6Scene().fullReset();
                    audioManagerObject.getLevel6GameAudio().stop();
                    audioManagerObject.getMenuAudio().play();
                    sceneManagerObject.getMenuScene().resetFlags();
                    stateManagerObject.setcurrentSceneState(SceneState::menu);
                }

                if (sceneManagerObject.getLevel6Scene().goToGameOver)
                {
                    sceneManagerObject.getLevel6Scene().goToGameOver = false;
                    audioManagerObject.getLevel6GameAudio().stop();
                    stateManagerObject.setReturnLevel(SceneState::level6); // 
                    sceneManagerObject.getGameOverScene().init(window);
                    sceneManagerObject.getGameOverScene().setup(
                        sceneManagerObject.getLevel6Scene().getResult(),
                        sceneManagerObject.getLevel6Scene().getPlayerScore(),
                        sceneManagerObject.getLevel6Scene().getCPUScore(),
                        audioManagerObject
                    );
                    stateManagerObject.setcurrentSceneState(SceneState::gameOver);
                }
            }
        }

        // ---- GAME OVER ----
        else if (stateManagerObject.getcurrentSceneState() == SceneState::gameOver)
        {
            window.clear();
            sceneManagerObject.getGameOverScene().draw(window);

            if (sceneManagerObject.getGameOverScene().goPlayAgain)
            {
                sceneManagerObject.getGameOverScene().goPlayAgain = false;
                audioManagerObject.getGameWinAudio().stop();
                audioManagerObject.getGameLoseAudio().stop();
                audioManagerObject.getGameDrawAudio().stop();

                SceneState lvl = stateManagerObject.getReturnLevel(); // 

                if (lvl == SceneState::level1) { sceneManagerObject.getLevel1Scene().fullReset(); audioManagerObject.getLevel1Audio().play(); }
                else if (lvl == SceneState::level2) { sceneManagerObject.getLevel2Scene().fullReset(); audioManagerObject.getLevel2Audio().play(); }
                else if (lvl == SceneState::level3) { sceneManagerObject.getLevel3Scene().fullReset(); audioManagerObject.getLevel3Audio().play(); }
                else if (lvl == SceneState::level4) { sceneManagerObject.getLevel4Scene().fullReset(); audioManagerObject.getLevel4Audio().play(); }
                else if (lvl == SceneState::level5) { sceneManagerObject.getLevel5Scene().fullReset(); audioManagerObject.getLevel5Audio().play(); }
                else if (lvl == SceneState::level6) { sceneManagerObject.getLevel6Scene().fullReset(); audioManagerObject.getLevel6Audio().play(); }

                stateManagerObject.setcurrentSceneState(lvl); //  go back to correct level
            }

            if (sceneManagerObject.getGameOverScene().goBackToMenu)
            {
                sceneManagerObject.getGameOverScene().goBackToMenu = false;
                audioManagerObject.getGameWinAudio().stop();
                audioManagerObject.getGameLoseAudio().stop();
                audioManagerObject.getGameDrawAudio().stop();

                //  reset ALL levels
                sceneManagerObject.getLevel1Scene().fullReset();
                sceneManagerObject.getLevel2Scene().fullReset();
                sceneManagerObject.getLevel3Scene().fullReset();
                sceneManagerObject.getLevel4Scene().fullReset();
                sceneManagerObject.getLevel5Scene().fullReset();
                sceneManagerObject.getLevel6Scene().fullReset();

                audioManagerObject.getMenuAudio().play();
                sceneManagerObject.getMenuScene().resetFlags();
                stateManagerObject.setcurrentSceneState(SceneState::menu);
            }
        }
    }

    return 0;
}