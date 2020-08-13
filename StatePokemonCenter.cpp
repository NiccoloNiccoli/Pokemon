//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StatePokemonCenter.h"

StatePokemonCenter::StatePokemonCenter(Game *gamePtr){
    game = gamePtr;
    stateName = GameState ::STATE_POKEMON_CENTER;
}
void StatePokemonCenter::changeState(State *nextState) {
    //TODO impedire di iniziare le battaglie
    State* tmpState = game->getCurrentState();
    game->setCurrentState(nextState);
    delete tmpState;
}

void StatePokemonCenter::draw(sf::RenderWindow &window) {

}

void StatePokemonCenter::update() {

}

void StatePokemonCenter::handleInput(sf::Event event) {

}

GameState StatePokemonCenter::getStateName() {
    return stateName;
}


