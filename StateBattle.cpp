//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <iostream>
#include "StateBattle.h"
StateBattle::StateBattle(Game *gamePtr){
    game = gamePtr;
    try{
        if(!music.openFromFile("../SoundEffects/Battle.wav")){
            throw std::runtime_error("File not found: ../SoundEffects/Battle.wav");
        }
       music.setLoop(true);
        music.setVolume(15.f);
        music.play();
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
    game->battle->setUIState(new BattleUI_Init(game->battle));
    game->battle->setSentenceIndex(0);
    game->battle->changeFeedbackSentence();
    stateName = GameState ::STATE_BATTLE;
}

void StateBattle::changeState(State *nextState) {
    if(nextState->getStateName() != GameState::STATE_MAIN_MENU) {
        State *tmpState = game->getCurrentState();
        game->setCurrentState(nextState);
        music.stop();
        delete tmpState;
    }
}

void StateBattle::update() {
}


void StateBattle::draw(sf::RenderWindow &window) {
    game->battle->draw(window);
}

void StateBattle::handleInput(sf::Event event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
            game->battle->moveUp();
        }else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S){
            game->battle->moveDown();
        }else if(event.key.code == sf::Keyboard::Enter){
            game->battle->goOn();
        }else if(event.key.code == sf::Keyboard::BackSpace){
            game->battle->goBack();
        }
    }
}

GameState StateBattle::getStateName() {
        return stateName;
}

void StateBattle::playMusic() {
    music.play();
}
