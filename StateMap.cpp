//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <iostream>
#include "StateMap.h"
#include "StatePauseMenu.h"

StateMap::StateMap(Game *gamePtr) {
    game = gamePtr;
    try {
        if(!music.openFromFile("../SoundEffects/Route.wav")){
            throw std::runtime_error("File not found: ../SoundEffects/Route.wav");
        }
        music.setLoop(true);
        music.setVolume(20.f);
        music.play();
    }
    catch (const std::runtime_error &ex) {
        std::cerr << ex.what() << std::endl;
        exit(-1);
    }
    stateName = GameState ::STATE_MAP;
}

void StateMap::changeState(State* nextState) {
    State* tmpState = game->getCurrentState();

    game->setCurrentState(nextState);
        auto tmp = dynamic_cast<StatePauseMenu *>(game->getCurrentState());
        if (tmp != nullptr) {
            tmp->setPreviousState(tmpState);
            music.pause();
        } else{
            music.stop();
            delete tmpState;
        }
}

void StateMap::draw(sf::RenderWindow &window) {
    window.draw(game->map);
    game->player.draw(window,game->player.getState());
    game->map.drawNPC(window);
    game->map.drawUI(window);
}

void StateMap::update() {
    game->player.move();
    game->map.checkCollisions(game->player);
}



void StateMap::handleInput(sf::Event event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Enter){
            game->player.fight(game->map.lookForNearestEnemy(game->player));
        }
        if(event.key.code == sf::Keyboard::Escape){
            changeState(new StatePauseMenu(game));
        }
    }
}

GameState StateMap::getStateName() {
    return stateName;
}

void StateMap::playMusic() {
    music.play();
}
