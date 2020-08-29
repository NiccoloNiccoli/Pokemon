//
// Created by Niccolò Niccoli on 10/08/2020.
//

#include "StateBattle.h"
StateBattle::StateBattle(Game *gamePtr){
    game = gamePtr;
    game->battle->setUIState(new BattleUI_Init(game->battle));
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
