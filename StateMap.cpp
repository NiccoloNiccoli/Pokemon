//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StateMap.h"
#include "StatePauseMenu.h"

StateMap::StateMap(Game *gamePtr) {
    game = gamePtr;
    stateName = GameState ::STATE_MAP;
}

void StateMap::changeState(State* nextState) {
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    if(nextState->getStateName() == GameState::STATE_PAUSE_MENU){
        auto tmp = dynamic_cast<StatePauseMenu *>(game->getCurrentState()); //TODO converrebbe farlo con unique ptr(?)/shared????
        if (tmp != 0) {
            tmp->setPreviousState(tmpState);
        } else{
            delete tmpState;
        }
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
