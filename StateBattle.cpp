//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StateBattle.h"
StateBattle::StateBattle(Game *gamePtr){
    game = gamePtr;
    stateName = GameState ::STATE_BATTLE;
}

void StateBattle::changeState(State *nextState) {
    //TODO impedire di passare dalla battaglia al menù
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;
}

void StateBattle::update() {

}


void StateBattle::draw(sf::RenderWindow &window) {
    game->battle.battleEngine(window, game->player); //FIXME maybe it should go into update() but i need "window"
}

void StateBattle::handleInput(sf::Event event) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Up){
            game->battle.moveUp(game->player);
        }else if(event.key.code == sf::Keyboard::Down){
            game->battle.moveDown(game->player);
        }else if(event.key.code == sf::Keyboard::Enter){
            game->battle.refreshMenu(game->player);
        }else if(event.key.code == sf::Keyboard::BackSpace){
            game->battle.resetMenu();
        }
    }
}

GameState StateBattle::getStateName() {
        return stateName;
}
