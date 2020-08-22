//
// Created by Niccolò Niccoli on 11/08/2020.
//

#include <iostream>
#include <fstream>
#include "StateMainMenu.h"

StateMainMenu::StateMainMenu(Game *gamePtr){
    game = gamePtr;
    stateName = GameState::STATE_MAIN_MENU;
    if(!texture.loadFromFile("../Textures/titleScreen.png")){
        //TODO EXCEPTION
    }
    sprite = AnimatedSprite(texture,1280,720,4);
    sprite.setScale(0.34f,0.34f);
    newGameBox.setFillColor(sf::Color::White);
    continueGameBox.setFillColor(sf::Color::White);
    continueGameBox.setPosition(sf::Vector2f(38.f,20.f));
    if(!font.loadFromFile("../pkmnem.ttf")){
        //TODO handle error
    }
    newGame.setFont(font);

    newGame.setFillColor(sf::Color::Blue);
    newGame.setString("NEW GAME");
    continueGame.setFont(font);
    continueGame.setPosition(sf::Vector2f(50.f,30.f));
    continueGame.setFillColor(sf::Color::Blue);
    continueGame.setString("CONTINUE");
    playersName.setPosition(sf::Vector2f(70.f, 80.f));
    playersName.setFont(font);
    playersName.setFillColor(sf::Color::Blue);
    playersName.setScale(0.75f, 0.75f);
    playTime.setFont(font);
    playTime.setPosition(sf::Vector2f(70.f, 110.f));
    playTime.setFillColor(sf::Color::Blue);
    playTime.setScale(0.5f,0.5f);
    insertName.setFont(font);
    insertName.setPosition(sf::Vector2f(50.f,30.f));
    insertName.setFillColor(sf::Color::Blue);
    insertName.setString("INSERT YOUR NAME");

}

void StateMainMenu::changeState(State *nextState) {
    if(nextState->getStateName() == GameState::STATE_MAP)
        game->map.restartTimer();
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;
}

void StateMainMenu::draw(sf::RenderWindow &window) {
    switch(menuPageIndex){
        case 0:
            sprite.draw(window,4);
            break;
        case 1:
            window.clear(sf::Color::Blue);
            window.draw(newGameBox);
            window.draw(newGame);
            break;
        case 2:
            window.clear(sf::Color::Blue);
            window.draw(newGameBox);
            window.draw(newGame);
            window.draw(continueGameBox);
            window.draw(continueGame);
            window.draw(playersName);
            window.draw(playTime);
            break;
        case 3:
            window.clear(sf::Color::Blue);
            window.draw(continueGameBox);
            window.draw(insertName);
            window.draw(playersName);
            break;
    }

}

void StateMainMenu::update() {

//TODO
}

void StateMainMenu::handleInput(sf::Event event) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Enter){
           switch(menuPageIndex){
               case 0:
                   if(Game::getInstance()->doesSaveFileExists()){
                       continueGame.setFillColor(sf::Color::Red);
                       playersName.setFillColor(sf::Color::Red);
                       playTime.setFillColor(sf::Color::Red);
                       loadInfo();
                       newGameBox.setPosition(sf::Vector2f(38.f,160.f));
                       newGame.setPosition(sf::Vector2f(50.f,170.f));
                       menuPageIndex = 2;
                   }
                   else{
                       newGame.setFillColor(sf::Color::Red);
                       newGameBox.setPosition(sf::Vector2f(38.f,20.f));
                       newGame.setPosition(sf::Vector2f(50.f,30.f));
                       menuPageIndex = 1;
                   }
                   break;
               case 1:
                    menuPageIndex = 3;
                    playerInput = "";
                    playersName.setString(playerInput);
                   break;
               case 2:
                   if(selectedItemIndex){
                       remove("../Saves/saves.txt");
                       playerInput = "";
                       playersName.setString(playerInput);
                       menuPageIndex = 3;
                   }else{
                       Game::getInstance()->load();
                       Game::getInstance()->changeState(GameState::STATE_MAP);
                   }
                   break;
               case 3:
                   Game::getInstance()->player.setName(playersName.getString().toAnsiString());
                   initializeNPCList();
                   Game::getInstance()->changeState(GameState::STATE_MAP);
                   break;
           }
        }
        if(event.key.code == sf::Keyboard::BackSpace){
            continueGame.setFillColor(sf::Color::Blue);
            playersName.setFillColor(sf::Color::Blue);
            playTime.setFillColor(sf::Color::Blue);
            newGame.setFillColor(sf::Color::Blue);
            selectedItemIndex = 0;
            menuPageIndex=0;
        }
        if(menuPageIndex == 2){
            if(event.key.code == sf::Keyboard::Down){
                continueGame.setFillColor(sf::Color::Blue);
                playersName.setFillColor(sf::Color::Blue);
                playTime.setFillColor(sf::Color::Blue);
                newGame.setFillColor(sf::Color::Red);
                selectedItemIndex = 1;
            }

            if(event.key.code == sf::Keyboard::Up){
                newGame.setFillColor(sf::Color::Blue);
                continueGame.setFillColor(sf::Color::Red);
                playersName.setFillColor(sf::Color::Red);
                playTime.setFillColor(sf::Color::Red);
                selectedItemIndex = 0;
            }

        }
    }
    if(menuPageIndex == 3){
        if(event.type == sf::Event::TextEntered){
            if(((event.text.unicode >= 33 && event.text.unicode <= 126) || (event.text.unicode >=192 && event.text.unicode <=255)) &&
                playerInput.getSize() < 16)
                playerInput += event.text.unicode;
        }
        if(event.key.code == sf::Keyboard::Escape){
            playerInput = "";
        }
        playersName.setString(playerInput);

    }
}

void StateMainMenu::loadInfo() {
        std::ifstream saveFile("../Saves/saves.txt");
        if (saveFile.is_open()) {
            std::string _playersName, pokemonsName, mapName;
            int money, teamSize, hpCurrent, lvl, xpos, ypos;
            float time;
            saveFile >> _playersName >> xpos >> ypos >> money >> teamSize;
            for (int i = 0; i < teamSize; i++)
                saveFile >> pokemonsName >> hpCurrent >> lvl;
            saveFile >> mapName >> time;
            playersName.setString(_playersName);
            int hours = time/3600;
            int minutes = (time - hours)/60;
            playTime.setString(std::to_string(hours) + ":" + std::to_string(minutes));
    }
}

GameState StateMainMenu::getStateName() {
    return stateName;
}

void StateMainMenu::initializeNPCList() {
    std::ofstream npclist("../Maps/ROUTE_01/npclist.txt", std::ios::trunc);
    if(npclist.is_open()){
        //id - x - y - isFightable
        npclist << 1 <<" " << 390 << " " << 140 << " true\n";
        npclist << 2 <<" " << 144 << " " << 30 << " true\n";
        npclist << 3 <<" " << 200 << " " << 150 << " true\n";
    }
}
