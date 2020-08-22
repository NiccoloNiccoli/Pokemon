//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include <iostream>
#include "StatePokemonCenter.h"

StatePokemonCenter::StatePokemonCenter(Game *gamePtr){
    game = gamePtr;
    outsideMap = game->map;
    if(game->player.isAnyPokemonAlive())
        game->player.setPosition(200,170);
    else {
        game->player.setPosition(206, 81);
        game->player.healTeam();
    }
    game->map = Map("tileset2.png",27,15,"POKEMON_CENTER");
    stateName = GameState ::STATE_POKEMON_CENTER;
}
void StatePokemonCenter::changeState(State *nextState) {
    if(nextState->getStateName() != GameState::STATE_BATTLE){
        game->map = outsideMap;
        game->player.setPosition(game->map.findPokemonCenterDoor().x,game->map.findPokemonCenterDoor().y);
        State* tmpState = game->getCurrentState();
        game->setCurrentState(nextState);
        delete tmpState;

    }

}

void StatePokemonCenter::draw(sf::RenderWindow &window) {
    window.draw(game->map);
    game->player.draw(window,game->player.getState());
    game->map.drawNPC(window);
}

void StatePokemonCenter::update() {
    game->player.move();
    game->map.checkCollisions(game->player);
}

void StatePokemonCenter::handleInput(sf::Event event) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Enter){
            if(game->map.lookForNearestEnemy(game->player) != nullptr){
                game->player.healTeam();
            }
        }
        if(event.key.code == sf::Keyboard::Escape){
            game->save();
        }
    }
}

GameState StatePokemonCenter::getStateName() {
    return stateName;
}


