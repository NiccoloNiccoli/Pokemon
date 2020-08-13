//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StateMap.h"

StateMap::StateMap(Game *gamePtr) {
    game = gamePtr;
    stateName = GameState ::STATE_MAP;
}

void StateMap::changeState(State* nextState) {
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;
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



void StateMap::handleInput(sf::Event event) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Enter){
            game->player.fight(game->map.lookForNearestEnemy(game->player));
        }
    }
}

GameState StateMap::getStateName() {
    return stateName;
}
