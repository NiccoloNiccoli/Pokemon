//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StateBattle.h"
StateBattle::StateBattle(Game *gamePtr){
    game = gamePtr;
    game->battle->setUIState(new BattleUI_Scene0(game->battle));
    game->battle->setSentenceIndex(0);
    game->battle->changeFeedbackSentence();
    stateName = GameState ::STATE_BATTLE;
}

void StateBattle::changeState(State *nextState) {
    if(nextState->getStateName() != GameState::STATE_MAIN_MENU) {
        State *tmpState = game->getCurrentState();
        game->setCurrentState(nextState);
        delete tmpState;
    }
}

void StateBattle::update() {

}


void StateBattle::draw(sf::RenderWindow &window) {
    game->battle->battleEngine(window, game->player); //FIXME maybe it should go into update() but i need "window"
}

void StateBattle::handleInput(sf::Event event, sf::RenderWindow &window) {
    if(event.type == sf::Event::KeyReleased){
        if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W){
            game->battle->moveUp(game->player);
        }else if(event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S){
            game->battle->moveDown(game->player);
        }else if(event.key.code == sf::Keyboard::Enter){
            game->battle->refreshMenu(game->player);
        }else if(event.key.code == sf::Keyboard::BackSpace){
            game->battle->resetMenu();
        }
    }
}

GameState StateBattle::getStateName() {
        return stateName;
}
