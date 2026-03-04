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

int main()
{
    Board chessBoard;
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u{ 800, 600 }), "TIC TAC TOE");
    IntroScene introSceneObject(window);
    SceneManager sceneManagerObject(window, introSceneObject);
    StateManager stateManagerObject;
    AudioManager audioManagerObject;

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            if ((*event).is<sf::Event::Closed>())
            {
                window.close();
            }
            if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
            {
                sceneManagerObject.getMenuScene().updateMenuIndex(*event, audioManagerObject);
            }
            if (stateManagerObject.getcurrentSceneState() == SceneState::options)
            {
                sceneManagerObject.getOptionsScene().updateOptionIndex(*event, audioManagerObject);
            }
            // level 1 event handling — GridSizeInput listens here
            if (stateManagerObject.getcurrentSceneState() == SceneState::level1)
            {
                if (audioManagerObject.getLevel1Audio().isFinished())
                {
                    sceneManagerObject.getLevel1Scene().handleEvent(*event, audioManagerObject);
                }
            }
        }

        // ---- INTRO ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::intro)
        {
            audioManagerObject.getIntroAudio().play();
            sceneManagerObject.getIntroScene().LoadIntro(window);
            window.clear();
            stateManagerObject.setcurrentSceneState(SceneState::menu);
        }

        // ---- MENU ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::menu)
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
        }

        // ---- OPTIONS ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::options)
        {
            window.clear();
            sceneManagerObject.getOptionsScene().drawOptions(window);

            if (sceneManagerObject.getOptionsScene().goBack)
            {
                sceneManagerObject.getOptionsScene().goBack = false;
                stateManagerObject.setcurrentSceneState(SceneState::menu);
            }
        }

        // ---- LEVEL 1 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level1)
        {
            if (audioManagerObject.getLevel1Audio().isFinished())
            {
                window.clear();
                //  pass both window and audioManager
                sceneManagerObject.getLevel1Scene().draw(window, audioManagerObject);
            }
        }

        // ---- LEVEL 2 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level2)
        {
            if (audioManagerObject.getLevel2Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel2Scene().draw(window);
            }
        }

        // ---- LEVEL 3 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level3)
        {
            if (audioManagerObject.getLevel3Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel3Scene().draw(window);
            }
        }

        // ---- LEVEL 4 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level4)
        {
            if (audioManagerObject.getLevel4Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel4Scene().draw(window);
            }
        }

        // ---- LEVEL 5 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level5)
        {
            if (audioManagerObject.getLevel5Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel5Scene().draw(window);
            }
        }

        // ---- LEVEL 6 ----
        if (stateManagerObject.getcurrentSceneState() == SceneState::level6)
        {
            if (audioManagerObject.getLevel6Audio().isFinished())
            {
                window.clear();
                sceneManagerObject.getLevel6Scene().draw(window);
            }
        }
    }

    return 0;
}